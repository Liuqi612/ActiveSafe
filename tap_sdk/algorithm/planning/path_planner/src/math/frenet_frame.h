
#pragma once

#include <algorithm>
#include <boost/geometry.hpp>
#include <boost/geometry/geometries/segment.hpp>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>
#include <absl/status/statusor.h>
#include <absl/types/span.h>

#include "math/rtree/bvh_common.hpp"
#include "path_planner/src/math/frenet_common.h"
#include "path_planner/src/math/geometry/box2d.h"
#include "path_planner/src/math/geometry/polygon2d.h"
#include "path_planner/src/math/geometry/segment2d.h"
#include "path_planner/src/math/segment_matcher/segment_matcher_kdtree.h"
#include "path_planner/src/math/vec.h"
#include "path_planner/src/util/qtfm_segment_matcher_v2.h"

namespace pnc_x {

enum class FrenetFrameType {
    kBruteFroce = 0,
    kKdTree = 1,
    kQtfmKdTree = 2,
    kRTree = 3,
    kBvh = 4,
};

class FrenetFrame {
 public:
    const std::vector<Vec2d> &points() const { return points_; }

    const std::vector<Vec2d> &tangents() const { return tangents_; }

    const std::vector<int> &raw_indices() const { return raw_indices_; }

    const std::vector<double> &s_knots() const { return s_knots_; }

    double start_s() const { return s_knots_.front(); }

    double end_s() const { return s_knots_.back(); }

    double length() const { return s_knots_.back() - s_knots_.front(); }

    Vec2d InterpolateTangentByS(double s) const;

    Vec2d InterpolateTangentByXY(const Vec2d &xy) const;

    Vec2d SLToXY(const FrenetCoordinate &sl) const;

    FrenetCoordinate XYToSL(const Vec2d &xy) const;

    absl::StatusOr<FrenetCoordinate> XYToSLWithHeadingDiffLimit(
        const Vec2d &xy, double heading, double max_heading_diff) const;

    void XYToSL(const Vec2d &xy, FrenetCoordinate *sl, Vec2d *normal) const;

    void XYToSL(const Vec2d &xy,
                FrenetCoordinate *sl,
                Vec2d *normal,
                int *index,
                double *alpha) const;

    void XYToSL(const Vec2d &xy,
                FrenetCoordinate *sl,
                Vec2d *normal,
                std::pair<int, int> *raw_index_pair,
                double *alpha) const;

    void XYToSLBatch(absl::Span<const Vec2d> xys,
                     std::vector<FrenetCoordinate> *sls,
                     std::vector<Vec2d> *normals,
                     std::vector<int> *indices,
                     std::vector<double> *alphas) const;
    Vec2d FindAABBNearestPoint(const Polygon2d &polygon,
                               bool get_max_s = false) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxWithHeading(
        const Box2d &box, double max_heading_diff = M_PI_2) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxAt(const Box2d &box) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxAtContour(
        const Polygon2d &contour) const;

    absl::StatusOr<FrenetBox> QueryFrenetBoxAtPoints(
        absl::Span<const Vec2d> points) const;

    virtual ~FrenetFrame() = default;

    FrenetFrame(std::vector<Vec2d> points,
                std::vector<double> s_knots,
                std::vector<double> segment_len_inv,
                std::vector<Vec2d> tangents,
                std::vector<int> raw_indices)
        : points_(std::move(points)),
          s_knots_(std::move(s_knots)),
          segment_len_inv_(std::move(segment_len_inv)),
          tangents_(std::move(tangents)),
          raw_indices_(std::move(raw_indices)) {}

 protected:
    virtual absl::StatusOr<FrenetCoordinate>
    XYToSLWithHeadingDiffLimitImplement(const Vec2d &xy,
                                        double heading,
                                        double max_heading_diff) const;

    virtual void XYToSLImplement(const Vec2d &xy,
                                 FrenetCoordinate *sl,
                                 Vec2d *normal,
                                 int *index,
                                 double *alpha) const = 0;

    virtual void XYToSLBatchImplement(absl::Span<const Vec2d> xys,
                                      absl::Span<FrenetCoordinate> sls,
                                      absl::Span<Vec2d> normals,
                                      absl::Span<int> indices,
                                      absl::Span<double> alphas) const {};

    absl::StatusOr<FrenetBox> QueryFrenetBoxAtPointsWithHeading(
        absl::Span<const Vec2d> points,
        double heading,
        double max_heading_diff) const;

    std::tuple<Vec2d, Vec2d, double> GetInterpolationRange(double s) const;

 protected:
    std::vector<Vec2d> points_;
    std::vector<double> s_knots_;
    std::vector<double> segment_len_inv_;
    std::vector<Vec2d> tangents_;
    std::vector<int> raw_indices_;
};

class BruteForceFrenetFrame : public FrenetFrame {
 public:
    BruteForceFrenetFrame(std::vector<Vec2d> points,
                          std::vector<double> s_knots,
                          std::vector<double> segment_len_inv,
                          std::vector<Vec2d> tangents,
                          std::vector<int> raw_indices)
        : FrenetFrame(std::move(points),
                      std::move(s_knots),
                      std::move(segment_len_inv),
                      std::move(tangents),
                      std::move(raw_indices)) {}

    ~BruteForceFrenetFrame() = default;

 private:
    void XYToSLImplement(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const override;
};

class KdTreeFrenetFrame : public FrenetFrame {
 public:
    KdTreeFrenetFrame(std::vector<Vec2d> points,
                      std::vector<double> s_knots,
                      std::vector<double> segment_len_inv,
                      std::vector<Vec2d> tangents,
                      std::vector<int> raw_indices,
                      std::vector<Segment2d> segments,
                      std::shared_ptr<SegmentMatcherKdtree> segment_matcher)
        : FrenetFrame(std::move(points),
                      std::move(s_knots),
                      std::move(segment_len_inv),
                      std::move(tangents),
                      std::move(raw_indices)),
          segments_(std::move(segments)),
          segment_matcher_(std::move(segment_matcher)) {}

    ~KdTreeFrenetFrame() = default;

 protected:
    absl::StatusOr<FrenetCoordinate> XYToSLWithHeadingDiffLimitImplement(
        const Vec2d &xy,
        double heading,
        double max_heading_diff) const override;

    void XYToSLImplement(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const override;

 protected:
    std::vector<Segment2d> segments_;
    std::shared_ptr<SegmentMatcherKdtree> segment_matcher_;
};

class QtfmEnhancedKdTreeFrenetFrame : public KdTreeFrenetFrame {
 public:
    QtfmEnhancedKdTreeFrenetFrame(
        std::vector<Vec2d> points,
        std::vector<double> s_knots,
        std::vector<double> segment_len_inv,
        std::vector<Vec2d> tangents,
        std::vector<int> raw_indices,
        std::vector<Segment2d> segments,
        std::shared_ptr<SegmentMatcherKdtree> segment_matcher,
        std::shared_ptr<planning::QtfmSegmentMatcherV2> qtfm_segment_matcher)
        : KdTreeFrenetFrame(std::move(points),
                            std::move(s_knots),
                            std::move(segment_len_inv),
                            std::move(tangents),
                            std::move(raw_indices),
                            std::move(segments),
                            std::move(segment_matcher)),
          qtfm_segment_matcher_(std::move(qtfm_segment_matcher)) {}

    ~QtfmEnhancedKdTreeFrenetFrame() = default;

 private:
    void XYToSLImplement(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const override;

 private:
    std::shared_ptr<planning::QtfmSegmentMatcherV2> qtfm_segment_matcher_;
};

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;
class RTreeFrenetFrame : public FrenetFrame {
    typedef bg::model::point<float, 2, bg::cs::cartesian> point;
    typedef bg::model::segment<point> segment;
    typedef std::pair<segment, unsigned> value;
    typedef bgi::rtree<value, bgi::quadratic<16>> rtree;

 public:
    RTreeFrenetFrame(std::vector<Vec2d> points,
                     std::vector<double> s_knots,
                     std::vector<double> segment_len_inv,
                     std::vector<Vec2d> tangents,
                     std::vector<int> raw_indices,
                     std::vector<Segment2d> segments);

    ~RTreeFrenetFrame() = default;

 private:
    void XYToSLImplement(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const override;

 private:
    std::vector<Segment2d> segments_;
    std::shared_ptr<rtree> rtree_;
};

class BVHFrenetFrame : public FrenetFrame {
 public:
    BVHFrenetFrame(std::vector<Vec2d> points,
                   std::vector<double> s_knots,
                   std::vector<double> segment_len_inv,
                   std::vector<Vec2d> tangents,
                   std::vector<int> raw_indices,
                   std::vector<Segment2d> segments);
    BVHFrenetFrame(const BVHFrenetFrame &other) = delete;
    BVHFrenetFrame &operator=(const BVHFrenetFrame &other) = delete;
    BVHFrenetFrame(BVHFrenetFrame &&other) = delete;
    BVHFrenetFrame &operator=(BVHFrenetFrame &&other) = delete;

    ~BVHFrenetFrame() = default;

 private:
    void XYToSLImplement(const Vec2d &xy,
                         FrenetCoordinate *sl,
                         Vec2d *normal,
                         int *index,
                         double *alpha) const override;
    void XYToSLBatchImplement(absl::Span<const Vec2d> xys,
                              absl::Span<FrenetCoordinate> sls,
                              absl::Span<Vec2d> normals,
                              absl::Span<int> indices,
                              absl::Span<double> alphas) const override;

 private:
    std::vector<Segment2d> segments_;
    std::vector<senseAD::planning_pilot::Segment> bvh_segments_;
    senseAD::planning_pilot::PolyBVH bvh_;
};

absl::StatusOr<BruteForceFrenetFrame> BuildBruteForceFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points);

absl::StatusOr<KdTreeFrenetFrame> BuildKdTreeFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points);

absl::StatusOr<QtfmEnhancedKdTreeFrenetFrame>
BuildQtfmEnhancedKdTreeFrenetFrame(absl::Span<const Vec2d> raw_points,
                                   bool down_sample_raw_points);

absl::StatusOr<RTreeFrenetFrame> BuildRTreeFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points);

absl::StatusOr<std::unique_ptr<BVHFrenetFrame>> BuildBVHFrenetFrame(
    absl::Span<const Vec2d> raw_points, bool down_sample_raw_points);

}  // namespace pnc_x
