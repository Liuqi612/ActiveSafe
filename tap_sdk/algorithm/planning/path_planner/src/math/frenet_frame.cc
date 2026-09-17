

#include "math/frenet_frame.h"

#include <algorithm>
#include <boost/geometry/index/predicates.hpp>
#include <cmath>
#include <limits>
#include <absl/status/status.h>
#include <absl/strings/str_cat.h>

#include "path_planner/src/common/throw_check.h"
#include "path_planner/src/common/timer.h"
#include "path_planner/src/math/util.h"
#include "path_planner/src/math/vec.h"
#include "path_planner/src/common/log.h"
#include "math/rtree/bvh_common.hpp"

namespace pnc_x {

namespace {
constexpr double kMinSegmentLength = 0.1;
constexpr double kMinSampleDistanceSqr = Sqr(kMinSegmentLength);
constexpr double kMinKdTreeSampleDistanceSqr = 1e-12;

absl::Status CheckAndBuildFrenetInput(const absl::Span<const Vec2d> &raw_points,
                                      bool down_sample_raw_points,
                                      FrenetFrameType type,
                                      std::vector<Vec2d> *points,
                                      std::vector<double> *s_knots,
                                      std::vector<double> *segment_len_inv,
                                      std::vector<Vec2d> *tangents,
                                      std::vector<int> *raw_indices,
                                      std::vector<Segment2d> *segments) {
    if (raw_points.size() < 2) {
        return absl::InvalidArgumentError(
            absl::StrCat("The number of input points is less than 2 at "));
    }

    if (!XCHECK_NOTNULL(points) || !XCHECK_NOTNULL(s_knots) ||
        !XCHECK_NOTNULL(segment_len_inv) || !XCHECK_NOTNULL(raw_indices) ||
        !XCHECK_NOTNULL(segments)) {
        return absl::InvalidArgumentError("input error");
    }

    XCHECK([raw_points]() {
        for (const auto &p : raw_points) {
            if (std::isnan(p.x()) || std::isnan(p.y())) return false;
        }
        return true;
    }());

    points->reserve(raw_points.size());
    points->push_back(raw_points.front());
    raw_indices->reserve(raw_points.size());
    raw_indices->push_back(0);

    for (int i = 1; i < raw_points.size(); ++i) {
        const std::size_t ui = static_cast<std::size_t>(i);
        const double distance_sqr =
            raw_points[ui].DistanceSquareTo(points->back());
        if ((down_sample_raw_points &&
             (distance_sqr < kMinSampleDistanceSqr)) ||
            (((type == FrenetFrameType::kKdTree) ||
              (type == FrenetFrameType::kQtfmKdTree) ||
              (type == FrenetFrameType::kBvh) ||
              (type == FrenetFrameType::kRTree)) &&
             (distance_sqr < kMinKdTreeSampleDistanceSqr))) {
            continue;
        }
        points->push_back(raw_points[ui]);
        raw_indices->push_back(i);
    }
    if (points->size() < 2) {
        return absl::FailedPreconditionError(absl::StrCat(
            " raw points size ", raw_points.size(), " raw point front (",
            raw_points.front().x(), ", ", raw_points.front().y(),
            ") raw point back (", raw_points.back().x(), ", ",
            raw_points.back().y(), ") at "));
    }

    s_knots->reserve(points->size());
    s_knots->push_back(0.0);
    segment_len_inv->reserve(points->size() - 1);
    segments->reserve(points->size() - 1);
    tangents->reserve(points->size());
    for (int i = 1; i < points->size(); ++i) {
        const std::size_t ui = static_cast<std::size_t>(i);
        const std::size_t ui_prev = static_cast<std::size_t>(i - 1);
        const Vec2d segment = (*points)[ui] - (*points)[ui_prev];
        segments->emplace_back((*points)[ui_prev], (*points)[ui]);
        const double segment_len = segment.norm();
        const double seg_len_inv = 1.0 / segment_len;
        s_knots->push_back(s_knots->back() + segment_len);
        segment_len_inv->push_back(seg_len_inv);
        tangents->push_back(segment * seg_len_inv);
    }
    tangents->push_back(tangents->back());
    return absl::OkStatus();
}

FrenetBox FindBoundingFrenetBox(const std::vector<FrenetCoordinate> &coords) {
    XCHECK_GT(coords.size(), 0);

    FrenetBox frenet_box{
        .s_max = -std::numeric_limits<double>::infinity(),
        .s_min = std::numeric_limits<double>::infinity(),
        .l_max = -std::numeric_limits<double>::infinity(),
        .l_min = std::numeric_limits<double>::infinity(),
    };
    for (const auto &coord : coords) {
        frenet_box.s_max = std::max(frenet_box.s_max, coord.s);
        frenet_box.s_min = std::min(frenet_box.s_min, coord.s);
        frenet_box.l_max = std::max(frenet_box.l_max, coord.l);
        frenet_box.l_min = std::min(frenet_box.l_min, coord.l);
    }

    constexpr double kMinFrenetBoxLength = 1e-3;
    frenet_box.s_max =
        std::max(frenet_box.s_max, frenet_box.s_min + kMinFrenetBoxLength);
    frenet_box.l_max =
        std::max(frenet_box.l_max, frenet_box.l_min + kMinFrenetBoxLength);

    return frenet_box;
}

}  // namespace

void FrenetFrame::XYToSLBatch(absl::Span<const Vec2d> xys,
                              std::vector<FrenetCoordinate> *sls,
                              std::vector<Vec2d> *normals,
                              std::vector<int> *indices,
                              std::vector<double> *alphas) const {
    if (!XCHECK_NOTNULL(sls) || !XCHECK_NOTNULL(normals) ||
        !XCHECK_NOTNULL(indices) || !XCHECK_NOTNULL(alphas)) {
        return;
    }
    sls->resize(xys.size());
    normals->resize(xys.size());
    indices->resize(xys.size());
    alphas->resize(xys.size());

    XYToSLBatchImplement(xys, absl::MakeSpan(*sls), absl::MakeSpan(*normals),
                         absl::MakeSpan(*indices), absl::MakeSpan(*alphas));
}

Vec2d FrenetFrame::InterpolateTangentByS(double s) const {
    const auto it = std::lower_bound(s_knots_.begin(), s_knots_.end(), s);
    if (it == s_knots_.begin()) {
        return tangents_.front();
    }
    if ((it == s_knots_.end()) || (it == (s_knots_.end() - 1))) {
        return tangents_.back();
    }
    if (std::fabs(s - *it) < 1e-3) {
        double t = (s - *(it - 1)) / (*(it + 1) - *(it - 1));
        const std::size_t idx_prev = static_cast<std::size_t>(it - 1 - s_knots_.begin());
        const std::size_t idx_cur = static_cast<std::size_t>(it - s_knots_.begin());
        return Vec2d::FastUnitFromAngle(
            LerpAngle(tangents_[idx_prev].Angle(),
                      tangents_[idx_cur].Angle(), t));
    }
    return tangents_[static_cast<std::size_t>(it - 1 - s_knots_.begin())];
}

Vec2d FrenetFrame::InterpolateTangentByXY(const Vec2d &xy) const {
    FrenetCoordinate sl;
    Vec2d normal;
    int index;
    double alpha = 0.0;
    XYToSL(xy, &sl, &normal, &index, &alpha);
    alpha = boost::algorithm::clamp(alpha - 1.0, 0.0, 1.0);
    const std::size_t uidx = static_cast<std::size_t>(index);
    const std::size_t uidx_next = static_cast<std::size_t>(index + 1);
    return Vec2d::FastUnitFromAngle(LerpAngle(
        tangents_[uidx].Angle(), tangents_[uidx_next].Angle(), alpha));
}

Vec2d FrenetFrame::SLToXY(const FrenetCoordinate &sl) const {
    Vec2d prev_pt;
    Vec2d succ_pt;
    double interp_t;
    std::tie(prev_pt, succ_pt, interp_t) = GetInterpolationRange(sl.s);
    const Vec2d heading_vec = (succ_pt - prev_pt).normalized();
    const Vec2d normal_vec = heading_vec.Perp();

    return Lerp(prev_pt, succ_pt, interp_t) + normal_vec * sl.l;
}

FrenetCoordinate FrenetFrame::XYToSL(const Vec2d &xy) const {
    FrenetCoordinate sl;
    Vec2d normal;
    XYToSL(xy, &sl, &normal);
    return sl;
}

void FrenetFrame::XYToSL(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal) const {
    int index;
    double alpha = 0.0;
    XYToSL(xy, sl, normal, &index, &alpha);
}

absl::StatusOr<FrenetCoordinate> FrenetFrame::XYToSLWithHeadingDiffLimit(
    const Vec2d &xy, double heading, double max_heading_diff) const {
    return XYToSLWithHeadingDiffLimitImplement(xy, heading, max_heading_diff);
}

void FrenetFrame::XYToSL(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const {
    XCHECK(std::isfinite(xy.x()) && std::isfinite(xy.y()));
    return XYToSLImplement(xy, sl, normal, index, alpha);
}

void FrenetFrame::XYToSL(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         std::pair<int, int> *raw_index_pair,
                         double *alpha) const {
    if (!XCHECK_NOTNULL(sl) || !XCHECK_NOTNULL(normal) ||
        !XCHECK_NOTNULL(raw_index_pair) || !XCHECK_NOTNULL(alpha)) {
        return;
    }

    int index = 0;
    XYToSL(xy, sl, normal, &index, alpha);
    const std::size_t uidx = static_cast<std::size_t>(index);
    const std::size_t uidx_next = static_cast<std::size_t>(index + 1);
    raw_index_pair->first = raw_indices_[uidx];
    raw_index_pair->second = raw_indices_[uidx_next];
}

std::tuple<Vec2d, Vec2d, double> FrenetFrame::GetInterpolationRange(
    double s) const {
    const auto it = std::lower_bound(s_knots_.begin(), s_knots_.end(), s);

    if (it == s_knots_.begin()) {
        return {points_[0], points_[1], (s - *it) / (*(it + 1) - *it)};
    }

    if (it == s_knots_.end()) {
        return {points_[points_.size() - 2], points_.back(),
                (s - *(it - 2)) / (*(it - 1) - *(it - 2))};
    }

    const std::size_t interp_prev = static_cast<std::size_t>(it - 1 - s_knots_.begin());
    const std::size_t interp_cur = static_cast<std::size_t>(it - s_knots_.begin());
    return {points_[interp_prev], points_[interp_cur],
            (s - *(it - 1)) / (*it - *(it - 1))};
}

Vec2d FrenetFrame::FindAABBNearestPoint(const Polygon2d &polygon,
                                        bool use_max_s) const {
    double smax = -std::numeric_limits<double>::infinity();
    double smin = std::numeric_limits<double>::infinity();
    double lmax = -std::numeric_limits<double>::infinity();
    double lmin = std::numeric_limits<double>::infinity();

    for (const auto &pt : polygon.points()) {
        FrenetCoordinate sl = XYToSL(pt);
        smax = std::max(smax, sl.s);
        smin = std::min(smin, sl.s);
        lmax = std::max(lmax, sl.l);
        lmin = std::min(lmin, sl.l);
    }

    double near_l;
    if ((lmax * lmin) < 0.0) {
        near_l = 0.0;
    } else {
        near_l = std::abs(lmax) > std::abs(lmin) ? lmin : lmax;
    }

    return Vec2d(use_max_s ? smax : smin, near_l);
}

absl::StatusOr<FrenetBox> FrenetFrame::QueryFrenetBoxWithHeading(
    const Box2d &box, double max_heading_diff) const {
    return QueryFrenetBoxAtPointsWithHeading(box.GetCornersCounterClockwise(),
                                             box.heading(), max_heading_diff);
}

absl::StatusOr<FrenetBox> FrenetFrame::QueryFrenetBoxAtPointsWithHeading(
    absl::Span<const Vec2d> points,
    double heading,
    double max_heading_diff) const {
    std::vector<FrenetCoordinate> coords;
    coords.reserve(points.size());
    for (const auto &pt : points) {
        auto p = XYToSLWithHeadingDiffLimit(pt, heading, max_heading_diff);
        if (p.ok()) {
            coords.emplace_back(p.value());
        }
    }
    if (coords.empty()) {
        return absl::NotFoundError("No frenet conversion is found.");
    }
    return FindBoundingFrenetBox(coords);
}

absl::StatusOr<FrenetBox> FrenetFrame::QueryFrenetBoxAt(
    const Box2d &box) const {
    return QueryFrenetBoxAtPoints(box.GetCornersCounterClockwise());
}

absl::StatusOr<FrenetBox> FrenetFrame::QueryFrenetBoxAtContour(
    const Polygon2d &contour) const {
    return QueryFrenetBoxAtPoints(contour.points());
}

absl::StatusOr<FrenetBox> FrenetFrame::QueryFrenetBoxAtPoints(
    absl::Span<const Vec2d> points) const {
    std::vector<FrenetCoordinate> coords;
    coords.reserve(points.size());
    for (const auto &pt : points) {
        coords.push_back(XYToSL(pt));
    }
    if (coords.empty()) {
        return absl::NotFoundError("No frenet conversion is found.");
    }
    return FindBoundingFrenetBox(coords);
}

absl::StatusOr<FrenetCoordinate>
KdTreeFrenetFrame::XYToSLWithHeadingDiffLimitImplement(
    const Vec2d &xy, double heading, double max_heading_diff) const {
    constexpr double kMinSearchRadiusWithHeadingLimit = 3.0;

    int nearest_index;
    if (!segment_matcher_->GetNearestSegmentIndex(xy.x(), xy.y(),
                                                  &nearest_index)) {
        return absl::NotFoundError(
            "Cannot find nearest segment index. (KdTree)");
    }

    const auto &nearest_seg_by_kdtree = segments_[static_cast<std::size_t>(nearest_index)];
    const double d = nearest_seg_by_kdtree.DistanceTo(xy);
    const auto max_radius = std::max(2.0 * d, kMinSearchRadiusWithHeadingLimit);
    int nearest_index_h_diff;
    if (!segment_matcher_->GetNearestSegmentIndexWithHeading(
            xy.x(), xy.y(), heading, max_radius, max_heading_diff,
            &nearest_index_h_diff)) {
        return absl::NotFoundError("Cannot find segment with correct heading.");
    }

    const std::size_t nidx = static_cast<std::size_t>(nearest_index_h_diff);
    const std::size_t nidx_next = static_cast<std::size_t>(nearest_index_h_diff + 1);
    const auto &seg = segments_[nidx];
    const double prod = seg.ProductOntoUnit(xy);
    const double proj = seg.ProjectOntoUnit(xy);
    const double alpha = proj * segment_len_inv_[nidx];
    const auto &seg_p0 = points_[nidx];
    double s;
    double l;
    if ((alpha < 0.0) && (nearest_index_h_diff > 0)) {
        s = s_knots_[nidx];
        l = std::copysign(seg_p0.DistanceTo(xy), prod);
    } else if ((alpha > 1.0) && ((nearest_index_h_diff + 2) < points_.size())) {
        s = s_knots_[nidx_next];
        const auto &seg_p1 = points_[nidx_next];
        l = std::copysign(seg_p1.DistanceTo(xy), prod);
    } else {
        s = s_knots_[nidx] + proj;
        l = prod;
    }
    return FrenetCoordinate{s, l};
}

absl::StatusOr<FrenetCoordinate>
FrenetFrame::XYToSLWithHeadingDiffLimitImplement(
    const Vec2d &xy, double heading, double max_heading_diff) const {
    FrenetCoordinate sl;
    Vec2d normal;

    double min_d = std::numeric_limits<double>::infinity();
    for (int i = 1; i < points_.size(); ++i) {
        const std::size_t ui = static_cast<std::size_t>(i);
        const std::size_t ui_prev = static_cast<std::size_t>(i - 1);
        const Vec2d p0 = points_[ui_prev];
        const Vec2d p1 = points_[ui];
        const Vec2d heading_vec = tangents_[ui_prev];
        const Vec2d query_segment = xy - p0;
        const double projection =
            query_segment.dot(heading_vec) * segment_len_inv_[ui_prev];
        const double production = heading_vec.CrossProd(query_segment);
        double l = std::numeric_limits<double>::infinity();
        double s = 0.0;
        if ((projection < 0.0) && (i > 1)) {
            const double sign = (production < 0.0) ? -1.0 : 1.0;
            l = p0.DistanceTo(xy) * sign;
            s = s_knots_[ui_prev];
        } else if ((projection > 1.0) && ((i + 1) < points_.size())) {
            const double sign = (production < 0.0) ? -1.0 : 1.0;
            l = p1.DistanceTo(xy) * sign;
            s = s_knots_[ui];
        } else {
            l = production;
            s = Lerp(s_knots_[ui_prev], s_knots_[ui], projection);
        }

        if (std::fabs(NormalizeAngle(heading - heading_vec.FastAngle())) >
            max_heading_diff) {
            continue;
        }

        if (std::fabs(l) < min_d) {
            min_d = std::fabs(l);
            sl = {s, l};
            normal = heading_vec.Perp();
        }
    }
    if (min_d < std::numeric_limits<double>::infinity()) {
        return sl;
    }
    return absl::NotFoundError("No viable frenet projection! (Brute force)");
}

void KdTreeFrenetFrame::XYToSLImplement(const Vec2d &xy,
                                        FrenetCoordinate *sl,
                                        Vec2d *normal,
                                        int *index,
                                        double *alpha) const {
    if (!XCHECK_NOTNULL(sl) || !XCHECK_NOTNULL(normal) ||
        !XCHECK_NOTNULL(index) || !XCHECK_NOTNULL(alpha)) {
        return;
    }

    XCHECK(segment_matcher_->GetNearestSegmentIndex(xy.x(), xy.y(), index));

    const std::size_t uidx = static_cast<std::size_t>(*index);
    const std::size_t uidx_next = static_cast<std::size_t>(*index + 1);
    const auto &nearest_seg = segments_[uidx];
    const double prod = nearest_seg.ProductOntoUnit(xy);
    const double proj = nearest_seg.ProjectOntoUnit(xy);
    *alpha = proj * segment_len_inv_[uidx];
    *normal = tangents_[uidx].Perp();
    const auto &p0 = points_[uidx];

    if ((*alpha < 0.0) && (*index > 0)) {
        sl->s = s_knots_[uidx];
        sl->l = std::copysign(p0.DistanceTo(xy), prod);
    } else if ((*alpha > 1.0) && (((*index) + 2) < points_.size())) {
        sl->s = s_knots_[uidx_next];
        const auto &p1 = points_[uidx_next];
        sl->l = std::copysign(p1.DistanceTo(xy), prod);
    } else {
        sl->s = s_knots_[uidx] + proj;
        sl->l = prod;
    }
}

void BruteForceFrenetFrame::XYToSLImplement(const Vec2d &xy,
                                            FrenetCoordinate *sl,
                                            Vec2d *normal,
                                            int *index,
                                            double *alpha) const {
    double min_d = std::numeric_limits<double>::infinity();
    for (int i = 1; i < points_.size(); ++i) {
        const std::size_t ui = static_cast<std::size_t>(i);
        const std::size_t ui_prev = static_cast<std::size_t>(i - 1);
        const Vec2d p0 = points_[ui_prev];
        const Vec2d p1 = points_[ui];
        const Vec2d heading_vec = tangents_[ui_prev];
        const Vec2d query_segment = xy - p0;
        const double projection =
            query_segment.dot(heading_vec) * segment_len_inv_[ui_prev];
        const double production = heading_vec.CrossProd(query_segment);
        double l = 0.0;
        double s = 0.0;
        if ((projection < 0.0) && (i > 1)) {
            const double sign = (production < 0.0) ? -1.0 : 1.0;
            l = p0.DistanceTo(xy) * sign;
            s = s_knots_[ui_prev];
        } else if ((projection > 1.0) && ((i + 1) < points_.size())) {
            const double sign = (production < 0.0) ? -1.0 : 1.0;
            l = p1.DistanceTo(xy) * sign;
            s = s_knots_[ui];
        } else {
            l = production;
            s = Lerp(s_knots_[ui_prev], s_knots_[ui], projection);
        }

        if (std::fabs(l) < min_d) {
            min_d = std::fabs(l);
            *sl = {s, l};
            *normal = heading_vec.Perp();
            *index = i - 1;
            *alpha = projection;
        }
    }
}

void QtfmEnhancedKdTreeFrenetFrame::XYToSLImplement(const Vec2d &xy,
                                                    FrenetCoordinate *sl,
                                                    Vec2d *normal,
                                                    int *index,
                                                    double *alpha) const {
    if (!XCHECK_NOTNULL(sl) || !XCHECK_NOTNULL(normal) ||
        !XCHECK_NOTNULL(index) || !XCHECK_NOTNULL(alpha) ||
        !XCHECK_NOTNULL(qtfm_segment_matcher_)) {
        return;
    }
    const bool found_by_qtfm =
        qtfm_segment_matcher_->GetNearestSegmentIndex(xy.x(), xy.y(), index);
    if (!found_by_qtfm ||
        (segments_[static_cast<std::size_t>(*index)].DistanceSquareTo(xy) >
         Sqr(qtfm_segment_matcher_->config().cutoff_distance))) {
        XCHECK(segment_matcher_->GetNearestSegmentIndex(xy.x(), xy.y(), index));
    }

    const std::size_t uidx = static_cast<std::size_t>(*index);
    const std::size_t uidx_next = static_cast<std::size_t>(*index + 1);
    const auto &nearest_seg = segments_[uidx];
    const double prod = nearest_seg.ProductOntoUnit(xy);
    const double proj = nearest_seg.ProjectOntoUnit(xy);
    *alpha = proj * segment_len_inv_[uidx];
    *normal = tangents_[uidx].Perp();
    const auto &p0 = points_[uidx];

    if ((*alpha < 0.0) && (*index > 0)) {
        sl->s = s_knots_[uidx];
        sl->l = std::copysign(p0.DistanceTo(xy), prod);
    } else if ((*alpha > 1.0) && (((*index) + 2) < points_.size())) {
        sl->s = s_knots_[uidx_next];
        const auto &p1 = points_[uidx_next];
        sl->l = std::copysign(p1.DistanceTo(xy), prod);
    } else {
        sl->s = s_knots_[uidx] + proj;
        sl->l = prod;
    }
}

RTreeFrenetFrame::RTreeFrenetFrame(std::vector<Vec2d> points,
                                   std::vector<double> s_knots,
                                   std::vector<double> segment_len_inv,
                                   std::vector<Vec2d> tangents,
                                   std::vector<int> raw_indices,
                                   std::vector<Segment2d> segments)
    : FrenetFrame(std::move(points),
                  std::move(s_knots),
                  std::move(segment_len_inv),
                  std::move(tangents),
                  std::move(raw_indices)),
      segments_(std::move(segments)) {
    std::vector<value> rtree_values;
    rtree_values.reserve(segments_.size());
    for (int i = 0; i < segments_.size(); ++i) {
        auto &raw_seg = segments_[static_cast<std::size_t>(i)];
        segment seg{bg::make<point>(raw_seg.start().x(), raw_seg.start().y()),
                    bg::make<point>(raw_seg.end().x(), raw_seg.end().y())};
        rtree_values.emplace_back(seg, i);
    }
    rtree_ = std::make_shared<rtree>(rtree_values.begin(), rtree_values.end());
}

void RTreeFrenetFrame::XYToSLImplement(const Vec2d &xy,
                                       FrenetCoordinate *sl,
                                       Vec2d *normal,
                                       int *index,
                                       double *alpha) const {
    if (!XCHECK_NOTNULL(sl) || !XCHECK_NOTNULL(normal) ||
        !XCHECK_NOTNULL(index) || !XCHECK_NOTNULL(alpha) ||
        !XCHECK_NOTNULL(rtree_)) {
        return;
    }
    point query_point(bg::make<point>(xy.x(), xy.y()));
    std::vector<value> result;
    rtree_->query(bgi::nearest(query_point, 1), std::back_inserter(result));
    if (result.empty()) {
        return;
    }
    *index = static_cast<int>(result.front().second);
    const std::size_t uidx = static_cast<std::size_t>(*index);
    const std::size_t uidx_next = static_cast<std::size_t>(*index + 1);
    const auto &nearest_seg = segments_[uidx];
    const double prod = nearest_seg.ProductOntoUnit(xy);
    const double proj = nearest_seg.ProjectOntoUnit(xy);
    *alpha = proj * segment_len_inv_[uidx];
    *normal = tangents_[uidx].Perp();
    const auto &p0 = points_[uidx];
    if ((*alpha < 0.0) && (*index > 0)) {
        sl->s = s_knots_[uidx];
        sl->l = std::copysign(p0.DistanceTo(xy), prod);
    } else if ((*alpha > 1.0) && (((*index) + 2) < points_.size())) {
        sl->s = s_knots_[uidx_next];
        const auto &p1 = points_[uidx_next];
        sl->l = std::copysign(p1.DistanceTo(xy), prod);
    } else {
        sl->s = s_knots_[uidx] + proj;
        sl->l = prod;
    }
}

BVHFrenetFrame::BVHFrenetFrame(std::vector<Vec2d> points,
                               std::vector<double> s_knots,
                               std::vector<double> segment_len_inv,
                               std::vector<Vec2d> tangents,
                               std::vector<int> raw_indices,
                               std::vector<Segment2d> segments)
    : FrenetFrame(std::move(points),
                  std::move(s_knots),
                  std::move(segment_len_inv),
                  std::move(tangents),
                  std::move(raw_indices)),
      segments_(std::move(segments)) {
    bvh_segments_.clear();
    bvh_segments_.reserve(segments_.size());
    for (const auto &segment : segments_) {
        senseAD::planning_pilot::Segment seg;
        seg.a = {static_cast<float>(segment.start().x()),
                 static_cast<float>(segment.start().y())};
        seg.b = {static_cast<float>(segment.end().x()),
                 static_cast<float>(segment.end().y())};
        bvh_segments_.push_back(seg);
    }
    if (!bvh_segments_.empty()) {
        bvh_.build(bvh_segments_);
    }
}

void BVHFrenetFrame::XYToSLImplement(const Vec2d &xy,
                                     FrenetCoordinate *sl,
                                     Vec2d *normal,
                                     int *index,
                                     double *alpha) const {
    if (!XCHECK_NOTNULL(sl) || !XCHECK_NOTNULL(normal) ||
        !XCHECK_NOTNULL(index) || !XCHECK_NOTNULL(alpha)) {
        return;
    }
    if (bvh_segments_.empty() || bvh_.minx.empty()) {
        return;
    }
    senseAD::planning_pilot::Vec2f query{static_cast<float>(xy.x()),
                                         static_cast<float>(xy.y())};
    float best_dist2 = std::numeric_limits<float>::infinity();
    int best_poly = -1;
    int best_seg = -1;
    int best_global = -1;
    // Successive single-point projections on a planning thread are normally
    // spatially coherent (notably A* successor expansion).  Seed the exact
    // BVH traversal with the previous hit so it has a useful pruning bound
    // from the root; query_iter still performs the full global search.
    static thread_local const BVHFrenetFrame* last_frame = nullptr;
    static thread_local int last_best_global = -1;
    if (last_frame == this && last_best_global >= 0 &&
        last_best_global < static_cast<int>(bvh_segments_.size())) {
        best_global = last_best_global;
        best_poly = bvh_.soa.poly_idx[static_cast<std::size_t>(best_global)];
        best_seg = bvh_.soa.seg_idx[static_cast<std::size_t>(best_global)];
        best_dist2 = std::nextafter(
            senseAD::planning_pilot::dist2_point_segment_soa_scalar(
                query, bvh_.soa, best_global),
            std::numeric_limits<float>::infinity());
    }
    if (!bvh_.query_iter(query, best_dist2, best_poly, best_seg, best_global)) {
        return;
    }
    last_frame = this;
    last_best_global = best_global;
    *index = best_global;
    const std::size_t uidx = static_cast<std::size_t>(*index);
    const std::size_t uidx_next = static_cast<std::size_t>(*index + 1);
    const auto &nearest_seg = segments_[uidx];
    const double prod = nearest_seg.ProductOntoUnit(xy);
    const double proj = nearest_seg.ProjectOntoUnit(xy);
    *alpha = proj * segment_len_inv_[uidx];
    *normal = tangents_[uidx].Perp();
    const auto &p0 = points_[uidx];
    if ((*alpha < 0.0) && (*index > 0)) {
        sl->s = s_knots_[uidx];
        sl->l = std::copysign(p0.DistanceTo(xy), prod);
    } else if ((*alpha > 1.0) && (((*index) + 2) < points_.size())) {
        sl->s = s_knots_[uidx_next];
        const auto &p1 = points_[uidx_next];
        sl->l = std::copysign(p1.DistanceTo(xy), prod);
    } else {
        sl->s = s_knots_[uidx] + proj;
        sl->l = prod;
    }
}

void BVHFrenetFrame::XYToSLBatchImplement(absl::Span<const Vec2d> xys,
                                          absl::Span<FrenetCoordinate> sls,
                                          absl::Span<Vec2d> normals,
                                          absl::Span<int> indices,
                                          absl::Span<double> alphas) const {
    if (bvh_segments_.empty() || bvh_.minx.empty()) {
        for (int i = 0; i < xys.size(); ++i) {
            const std::size_t ui = static_cast<std::size_t>(i);
            indices[ui] = -1;
            sls[ui] = FrenetCoordinate{0.0, 0.0};
            normals[ui] = Vec2d(0.0, 0.0);
            alphas[ui] = 0.0;
        }
        return;
    }

    std::vector<senseAD::planning_pilot::Vec2f> queries;
    queries.reserve(xys.size());
    for (const auto &pt : xys) {
        queries.push_back(
            {static_cast<float>(pt.x()), static_cast<float>(pt.y())});
    }
    bvh_.query_batch(queries.data(), static_cast<int>(queries.size()), nullptr,
                     nullptr, nullptr, indices.data(), nullptr,
                     /*force_scalar=*/false);

    for (int i = 0; i < static_cast<int>(xys.size()); ++i) {
        const std::size_t ui = static_cast<std::size_t>(i);
        const int seg_index = indices[ui];
        indices[ui] = seg_index;
        if ((seg_index < 0) || (seg_index >= static_cast<int>(segments_.size()))) {
            sls[ui] = FrenetCoordinate{0.0, 0.0};
            normals[ui] = Vec2d(0.0, 0.0);
            alphas[ui] = 0.0;
            continue;
        }
        const std::size_t sidx = static_cast<std::size_t>(seg_index);
        const std::size_t sidx_next = static_cast<std::size_t>(seg_index + 1);
        const auto &nearest_seg = segments_[sidx];
        const double prod = nearest_seg.ProductOntoUnit(xys[ui]);
        const double proj = nearest_seg.ProjectOntoUnit(xys[ui]);
        alphas[ui] = proj * segment_len_inv_[sidx];
        normals[ui] = tangents_[sidx].Perp();
        const auto &p0 = points_[sidx];
        if ((alphas[ui] < 0.0) && (seg_index > 0)) {
            sls[ui].s = s_knots_[sidx];
            sls[ui].l = std::copysign(p0.DistanceTo(xys[ui]), prod);
        } else if ((alphas[ui] > 1.0) && ((seg_index + 2) < static_cast<int>(points_.size()))) {
            sls[ui].s = s_knots_[sidx_next];
            const auto &p1 = points_[sidx_next];
            sls[ui].l = std::copysign(p1.DistanceTo(xys[ui]), prod);
        } else {
            sls[ui].s = s_knots_[sidx] + proj;
            sls[ui].l = prod;
        }
    }
}

absl::StatusOr<BruteForceFrenetFrame> BuildBruteForceFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points) {
    std::vector<Vec2d> points;
    std::vector<double> s_knots;
    std::vector<double> segment_len_inv;
    std::vector<Vec2d> tangents;
    std::vector<int> raw_indices;
    std::vector<Segment2d> segments;

    auto status = CheckAndBuildFrenetInput(raw_points, down_sample_raw_points,
                                           FrenetFrameType::kBruteFroce,
                                           &points, &s_knots, &segment_len_inv,
                                           &tangents, &raw_indices, &segments);
    if (!status.ok()) {
        return status;
    }

    return BruteForceFrenetFrame(std::move(points), std::move(s_knots),
                                 std::move(segment_len_inv),
                                 std::move(tangents), std::move(raw_indices));
}

absl::StatusOr<KdTreeFrenetFrame> BuildKdTreeFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points) {
    std::vector<Vec2d> points;
    std::vector<double> s_knots;
    std::vector<double> segment_len_inv;
    std::vector<Vec2d> tangents;
    std::vector<int> raw_indices;
    std::vector<Segment2d> segments;
    std::shared_ptr<SegmentMatcherKdtree> segment_matcher;

    auto status = CheckAndBuildFrenetInput(
        raw_points, down_sample_raw_points, FrenetFrameType::kKdTree, &points,
        &s_knots, &segment_len_inv, &tangents, &raw_indices, &segments);
    if (!status.ok()) {
        return status;
    }

    segment_matcher = std::make_unique<SegmentMatcherKdtree>(segments);
    return KdTreeFrenetFrame(std::move(points), std::move(s_knots),
                             std::move(segment_len_inv), std::move(tangents),
                             std::move(raw_indices), std::move(segments),
                             std::move(segment_matcher));
}

absl::StatusOr<QtfmEnhancedKdTreeFrenetFrame>
BuildQtfmEnhancedKdTreeFrenetFrame(absl::Span<const Vec2d> raw_points,
                                   bool down_sample_raw_points) {
    using planning::QtfmSegmentMatcherV2;
    std::vector<Vec2d> points;
    std::vector<double> s_knots;
    std::vector<double> segment_len_inv;
    std::vector<Vec2d> tangents;
    std::vector<int> raw_indices;
    std::vector<Segment2d> segments;
    std::shared_ptr<SegmentMatcherKdtree> segment_matcher;
    std::shared_ptr<QtfmSegmentMatcherV2> qtfm_segment_matcher;

    auto status = CheckAndBuildFrenetInput(raw_points, down_sample_raw_points,
                                           FrenetFrameType::kQtfmKdTree,
                                           &points, &s_knots, &segment_len_inv,
                                           &tangents, &raw_indices, &segments);
    if (!status.ok()) {
        return status;
    }

    XCHECK_GE(kMinSegmentLength, QtfmSegmentMatcherV2::kMinSegmentLength);

    segment_matcher = std::make_shared<SegmentMatcherKdtree>(segments);

    constexpr double kCutoffDistance = 8.0;
    constexpr double kResolution = 0.5;
    constexpr int kDepth = 5;
    constexpr int kCutoffNumRange = 1;
    constexpr int kCutoffNumCandidate = 32;
    double x_min = +std::numeric_limits<double>::infinity();
    double y_min = +std::numeric_limits<double>::infinity();
    double x_max = -std::numeric_limits<double>::infinity();
    double y_max = -std::numeric_limits<double>::infinity();

    for (const auto &segment : segments) {
        x_max = std::max(segment.max_x(), x_max);
        x_min = std::min(segment.min_x(), x_min);
        y_max = std::max(segment.max_y(), y_max);
        y_min = std::min(segment.min_y(), y_min);
    }
    XCHECK_GE(x_max, x_min);
    XCHECK_GE(y_max, y_min);

    QtfmSegmentMatcherV2::Config config{
        .x_min = x_min - kCutoffDistance,
        .x_max = x_max + kCutoffDistance,
        .y_min = y_min - kCutoffDistance,
        .y_max = y_max + kCutoffDistance,
        .resolution = kResolution,
        .qtfm_depth = kDepth,
        .cutoff_num_range = kCutoffNumRange,
        .cutoff_max_num_candidate = kCutoffNumCandidate,
        .cutoff_distance = kCutoffDistance};
    std::vector<std::pair<int, int>> segment_connection_status;
    segment_connection_status.reserve(segments.size());

    for (int i = 0; i < static_cast<int>(segments.size()); ++i) {
        segment_connection_status.emplace_back(
            i - 1, ((i + 1) < static_cast<int>(segments.size())) ? (i + 1) : (-1));
    }

    qtfm_segment_matcher = std::make_shared<QtfmSegmentMatcherV2>(
        config, segments, std::vector<int>{0});

    return QtfmEnhancedKdTreeFrenetFrame(
        std::move(points), std::move(s_knots), std::move(segment_len_inv),
        std::move(tangents), std::move(raw_indices), std::move(segments),
        std::move(segment_matcher), std::move(qtfm_segment_matcher));
}

absl::StatusOr<RTreeFrenetFrame> BuildRTreeFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points) {
    std::vector<Vec2d> points;
    std::vector<double> s_knots;
    std::vector<double> segment_len_inv;
    std::vector<Vec2d> tangents;
    std::vector<int> raw_indices;
    std::vector<Segment2d> segments;
    std::shared_ptr<SegmentMatcherKdtree> segment_matcher;

    auto status = CheckAndBuildFrenetInput(
        raw_points, down_sample_raw_points, FrenetFrameType::kRTree, &points,
        &s_knots, &segment_len_inv, &tangents, &raw_indices, &segments);
    if (!status.ok()) {
        return status;
    }

    return RTreeFrenetFrame(std::move(points), std::move(s_knots),
                            std::move(segment_len_inv), std::move(tangents),
                            std::move(raw_indices), std::move(segments));
}

absl::StatusOr<std::unique_ptr<BVHFrenetFrame>> BuildBVHFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points) {
    std::vector<Vec2d> points;
    std::vector<double> s_knots;
    std::vector<double> segment_len_inv;
    std::vector<Vec2d> tangents;
    std::vector<int> raw_indices;
    std::vector<Segment2d> segments;
    std::shared_ptr<SegmentMatcherKdtree> segment_matcher;

    auto status = CheckAndBuildFrenetInput(
        raw_points, down_sample_raw_points, FrenetFrameType::kBvh, &points,
        &s_knots, &segment_len_inv, &tangents, &raw_indices, &segments);
    if (!status.ok()) {
        return status;
    }

    return std::make_unique<BVHFrenetFrame>(
        std::move(points), std::move(s_knots), std::move(segment_len_inv),
        std::move(tangents), std::move(raw_indices), std::move(segments));
}

}  // namespace pnc_x
