

#include "util/min_segment_distance_problem.h"
#include "math/util.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

double MinSegmentDistanceProblem::kEpsilon = 1e-10;

inline senseAD::planning_pilot::Polyline make_polyline(const std::vector<senseAD::planning_pilot::Segment> &segs) {
    senseAD::planning_pilot::Polyline pl;
    pl.min.x = std::numeric_limits<float>::infinity();
    pl.min.y = std::numeric_limits<float>::infinity();
    pl.max.x = -std::numeric_limits<float>::infinity();
    pl.max.y = -std::numeric_limits<float>::infinity();
    pl.segs.reserve(segs.size());
    for (size_t i = 0; i < segs.size(); i++) {
        pl.segs.push_back({segs[i]});
        pl.min.x = std::min(pl.min.x, segs[i].a.x);
        pl.min.y = std::min(pl.min.y, segs[i].a.y);
        pl.max.x = std::max(pl.max.x, segs[i].a.x);
        pl.max.y = std::max(pl.max.y, segs[i].a.y);
        pl.min.x = std::min(pl.min.x, segs[i].b.x);
        pl.min.y = std::min(pl.min.y, segs[i].b.y);
        pl.max.x = std::max(pl.max.x, segs[i].b.x);
        pl.max.y = std::max(pl.max.y, segs[i].b.y);
    }
    return pl;
}

inline void make_polylines(
    const std::vector<std::pair<std::string, Segment2d>> &named_segments,
    std::vector<senseAD::planning_pilot::Segment> &all_segs,
    std::vector<senseAD::planning_pilot::Polyline> &polylines) {
    if (named_segments.empty()) {
        return;
    }

    all_segs.reserve(named_segments.size());
    std::map<std::string, std::vector<senseAD::planning_pilot::Segment>> groups;

    for (const auto &named_segment : named_segments) {
        const Segment2d &segment = named_segment.second;
        senseAD::planning_pilot::Segment seg;
        seg.a = {static_cast<float>(segment.start().x()),
                 static_cast<float>(segment.start().y())};
        seg.b = {static_cast<float>(segment.end().x()),
                 static_cast<float>(segment.end().y())};
        all_segs.push_back(seg);
        groups[named_segment.first].push_back(seg);
    }

    polylines.reserve(groups.size());
    for (const auto &group : groups) {
        polylines.push_back(make_polyline(group.second));
    }
}

MinSegmentDistanceProblem::MinSegmentDistanceProblem(
    std::vector<std::pair<std::string, Segment2d>> named_segments,
    double cutoff_distance,
    const std::vector<int> &optional_start_segment_ids)
    : named_segments_(std::move(named_segments)),
      cutoff_distance_(cutoff_distance) {
    XCHECK_GT(cutoff_distance_, 0);
    XCHECK(!named_segments_.empty());
    constexpr double kMaxCutoffDistance = 100.0;
    XCHECK_LE(cutoff_distance_, kMaxCutoffDistance);
    bvh_segments_.clear();
    bvh_polylines_.clear();
    make_polylines(named_segments_, bvh_segments_, bvh_polylines_);
    if (!bvh_segments_.empty()) {
        bvh_.build(bvh_segments_, bvh_polylines_);
    }
}

MinSegmentDistanceProblem::MinSegmentDistanceProblem(
    const MinSegmentDistanceProblem &other)
    : named_segments_(other.named_segments_),
      bvh_segments_(other.bvh_segments_),
      bvh_polylines_(other.bvh_polylines_),
      bvh_(other.bvh_),
      cutoff_distance_(other.cutoff_distance_) {
    XCHECK_GT(cutoff_distance_, 0);
    XCHECK(!named_segments_.empty());
}

double MinSegmentDistanceProblem::cutoff_distance() const {
    return cutoff_distance_;
}

const std::vector<std::pair<std::string, Segment2d>>
    &MinSegmentDistanceProblem::named_segments() const {
    return named_segments_;
}

double MinSegmentDistanceProblem::Evaluate(const Vec2d &point) const {
    const Segment2d *segment = GetNearestSegment(point);
    if (segment == nullptr) {
        return cutoff_distance_;
    }
    return segment->DistanceTo(point);
}

double MinSegmentDistanceProblem::EvaluateWithNearestSegmentId(
    const Vec2d &point, std::string *segment_id) const {
    if (!XCHECK_NOTNULL(segment_id)) {
        return 0.0;
    }
    const int index = GetNearestSegmentIndex(point);
    if (index < 0) {
        *segment_id = "";
        return cutoff_distance_;
    }
    *segment_id = named_segments_[static_cast<size_t>(index)].first;
    return named_segments_[static_cast<size_t>(index)].second.DistanceTo(point);
}

const Segment2d *MinSegmentDistanceProblem::GetNearestSegment(
    const Vec2d &point) const {
    const int index = GetNearestSegmentIndex(point);
    if (index < 0) {
        return nullptr;
    }
    return &named_segments_[static_cast<size_t>(index)].second;
}

double MinSegmentDistanceProblem::EvaluateWithSecondOrderDerivatives(
    const Vec2d &point, SecondOrderDerivativeType *derivative) const {
    if (!XCHECK_NOTNULL(derivative)) {
        return 0.0;
    }
    const Segment2d *segment = GetNearestSegment(point);
    if (segment == nullptr) {
        *derivative = SecondOrderDerivativeType{};
        return cutoff_distance_;
    }

    const double projection = segment->ProjectOntoUnit(point);
    if ((projection <= 0.0) || (segment->length() <= kEpsilon)) {
        return DistanceToCenterWithDerivative(point, segment->start(),
                                              derivative);
    }
    if (projection >= segment->length()) {
        return DistanceToCenterWithDerivative(point, segment->end(),
                                              derivative);
    }
    return DistanceToLineWithDerivative(point, *segment, derivative);
}

int MinSegmentDistanceProblem::GetNearestSegmentIndex(
    const Vec2d &point) const {
    if (!HasBVH()) {
        return -1;
    }
    senseAD::planning_pilot::Vec2f query{
        static_cast<float>(point.x()), static_cast<float>(point.y())};
    float best_dist2 = std::numeric_limits<float>::infinity();
    int best_poly = -1;
    int best_seg = -1;
    int best_global = -1;
    if (!bvh_.query_iter(query, best_dist2, best_poly, best_seg, best_global)) {
        return -1;
    }
    return best_global;
}

bool MinSegmentDistanceProblem::HasBVH() const {
    return !bvh_segments_.empty() && !bvh_.minx.empty();
}

void MinSegmentDistanceProblem::QueryNearestSegmentIndicesBatch(
    const std::vector<Vec2d> &points,
    std::vector<int> *out_indices) const {
    BatchQueryWorkspace workspace;
    QueryNearestSegmentIndicesBatch(points, out_indices, &workspace);
}

void MinSegmentDistanceProblem::QueryNearestSegmentIndicesBatch(
    const std::vector<Vec2d> &points,
    std::vector<int> *out_indices,
    BatchQueryWorkspace *workspace) const {
    if (!XCHECK_NOTNULL(out_indices)) {
        return;
    }
    if (points.empty() || !HasBVH()) {
        out_indices->assign(points.size(), -1);
        return;
    }

    BatchQueryWorkspace local_workspace;
    if (workspace == nullptr) {
        workspace = &local_workspace;
    }

    // Reuse the caller-owned buffers.  clear()/assign() retain capacity after
    // the first state, which removes two heap allocations from every query.
    auto &queries = workspace->queries;
    queries.clear();
    queries.reserve(points.size());
    for (const auto &point : points) {
        queries.push_back(
            {static_cast<float>(point.x()), static_cast<float>(point.y())});
    }

    size_t original_size = queries.size();

    // Pad to multiple of 4 for SIMD efficiency
    if (original_size % 4 != 0) {
        size_t padded_size = ((original_size + 3) / 4) * 4;
        queries.resize(padded_size, {1e30F, 1e30F});
    }
    
    auto &padded_results = workspace->padded_results;
    padded_results.assign(queries.size(), -1);
    
    bvh_.query_batch(queries.data(), static_cast<int>(queries.size()), nullptr,
                     nullptr, nullptr, padded_results.data(), nullptr,
                     /*force_scalar=*/false);

    // Copy back only the original size results
    out_indices->assign(padded_results.begin(),
                        padded_results.begin() + static_cast<ptrdiff_t>(original_size));
}

double MinSegmentDistanceProblem::DistanceToCenterWithDerivative(
    const Vec2d &point,
    const Vec2d &center,
    SecondOrderDerivativeType *derivative) const {
    if (!XCHECK_NOTNULL(derivative)) {
        return 0.0;
    }
    const double x = point.x();
    const double y = point.y();
    const double x0 = center.x();
    const double y0 = center.y();
    const double dx = x - x0;
    const double dy = y - y0;
    const double dist = Hypot(dx, dy);

    if (dist < kEpsilon) {
        derivative->df_dx = 1.0;
        derivative->df_dy = 0.0;
        derivative->d2f_dy_dy = 0.0;
        derivative->d2f_dx_dx = 0.0;
        derivative->d2f_dx_dy = 0.0;
        return 0.0;
    } else {
        const double dist_inv = 1. / dist;
        const double dist_inv_cubic = dist_inv * dist_inv * dist_inv;
        derivative->df_dx = dx * dist_inv;
        derivative->df_dy = dy * dist_inv;
        derivative->d2f_dx_dx = (-(dx * dx) * dist_inv_cubic) + dist_inv;
        derivative->d2f_dy_dy = (-(dy * dy) * dist_inv_cubic) + dist_inv;
        derivative->d2f_dx_dy = -(dx * dy) * dist_inv_cubic;
        return dist;
    }
}

double MinSegmentDistanceProblem::DistanceToLineWithDerivative(
    const Vec2d &point,
    const Segment2d &segment_on_line,
    SecondOrderDerivativeType *derivative) const {
    if (!XCHECK_NOTNULL(derivative) ||
        !XCHECK_GE(segment_on_line.length(), kEpsilon)) {
        return 0.0;
    }
    const Vec2d start_to_point = point - segment_on_line.start();
    const Vec2d norm = segment_on_line.unit_direction().Perp();
    const double signed_dist = norm.Dot(start_to_point);

    derivative->d2f_dx_dx = 0.0;
    derivative->d2f_dy_dy = 0.0;
    derivative->d2f_dx_dy = 0.0;
    if (signed_dist > 0.0) {
        derivative->df_dx = norm.x();
        derivative->df_dy = norm.y();
        return signed_dist;
    } else {
        derivative->df_dx = -norm.x();
        derivative->df_dy = -norm.y();
        return -signed_dist;
    }
}

MsdProblemWithBuffer::MsdProblemWithBuffer(
    std::vector<MsdProblemWithBuffer::SegmentType> named_segments_with_buffer,
    double cutoff_distance,
    const std::vector<int> &optional_start_segment_ids)
    : MinSegmentDistanceProblem(
          ExtractNamedSegments(named_segments_with_buffer),
          cutoff_distance,
          optional_start_segment_ids),
      named_segments_with_buffer_(std::move(named_segments_with_buffer)) {}

const MsdProblemWithBuffer::SegmentType *
MsdProblemWithBuffer::GetNearestSegmentWithBuffer(const Vec2d &point) const {
    const int index = GetNearestSegmentIndex(point);
    if (index < 0) {
        return nullptr;
    }
    return &named_segments_with_buffer_[static_cast<size_t>(index)];
}

void MsdProblemWithBuffer::GetNearestSegmentsWithBuffer(
    const std::vector<Vec2d> &points,
    std::vector<const SegmentType *> *out_segments) const {
    BatchQueryWorkspace workspace;
    GetNearestSegmentsWithBuffer(points, out_segments, &workspace);
}

void MsdProblemWithBuffer::GetNearestSegmentsWithBuffer(
    const std::vector<Vec2d> &points,
    std::vector<const SegmentType *> *out_segments,
    BatchQueryWorkspace *workspace) const {
    if (!XCHECK_NOTNULL(out_segments)) {
        return;
    }
    out_segments->assign(points.size(), nullptr);
    if (points.empty()) {
        return;
    }
    BatchQueryWorkspace local_workspace;
    if (workspace == nullptr) {
        workspace = &local_workspace;
    }
    auto &best_globals = workspace->indices;
    QueryNearestSegmentIndicesBatch(points, &best_globals, workspace);
    for (size_t i = 0; i < best_globals.size(); ++i) {
        const int index = best_globals[i];
        if (index >= 0) {
            (*out_segments)[i] = &named_segments_with_buffer_[static_cast<size_t>(index)];
        }
    }
}

std::vector<std::pair<std::string, Segment2d>>
MsdProblemWithBuffer::ExtractNamedSegments(
    const std::vector<MsdProblemWithBuffer::SegmentType>
        &named_segments_with_buffer) {
    std::vector<std::pair<std::string, Segment2d>> named_segments;
    named_segments.reserve(named_segments_with_buffer.size());
    for (const auto &seg : named_segments_with_buffer) {
        named_segments.emplace_back(seg.id, seg.segment);
    }
    return named_segments;
}

}  // namespace planning
}  // namespace pnc_x
