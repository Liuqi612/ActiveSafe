
#pragma once

#include <algorithm>
#include <limits>
#include <optional>
#include <string>
#include <utility>
#include <vector>

#include "math/geometry/segment2d.h"
#include "math/rtree/bvh_common.hpp"
#include "math/vec.h"
#include "util/qtfm_segment_matcher_v2.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

class MinSegmentDistanceProblem {
 public:
    static double kEpsilon;

    // Scratch storage for the SIMD batch query.  Callers that issue repeated
    // queries (for example, once per DDP state) can keep one workspace alive
    // and avoid rebuilding the temporary float/int buffers on every call.
    struct BatchQueryWorkspace {
        std::vector<senseAD::planning_pilot::Vec2f> queries;
        std::vector<int> padded_results;
        std::vector<int> indices;
    };

    struct SecondOrderDerivativeType {
        double df_dx = 0.0;
        double df_dy = 0.0;
        double d2f_dx_dx = 0.0;
        double d2f_dx_dy = 0.0;
        double d2f_dy_dy = 0.0;
    };

    MinSegmentDistanceProblem(
        std::vector<std::pair<std::string, Segment2d>> named_segments,
        double cutoff_distance,
        const std::vector<int> &optional_start_segment_ids);

    const Segment2d *GetNearestSegment(const Vec2d &point) const;

    double Evaluate(const Vec2d &point) const;

    double EvaluateWithNearestSegmentId(const Vec2d &point,
                                        std::string *segment_id) const;

    double EvaluateWithSecondOrderDerivatives(
        const Vec2d &point, SecondOrderDerivativeType *derivative_output) const;

    MinSegmentDistanceProblem(const MinSegmentDistanceProblem &other);

    double cutoff_distance() const;

    const std::vector<std::pair<std::string, Segment2d>> &named_segments()
        const;

 protected:
    int GetNearestSegmentIndex(const Vec2d &point) const;
    bool HasBVH() const;
    void QueryNearestSegmentIndicesBatch(
        const std::vector<Vec2d> &points,
        std::vector<int> *out_indices) const;
    void QueryNearestSegmentIndicesBatch(
        const std::vector<Vec2d> &points,
        std::vector<int> *out_indices,
        BatchQueryWorkspace *workspace) const;

 private:
    double DistanceToCenterWithDerivative(
        const Vec2d &point,
        const Vec2d &center,
        SecondOrderDerivativeType *derivative) const;

    double DistanceToLineWithDerivative(
        const Vec2d &point,
        const Segment2d &segment_on_line,
        SecondOrderDerivativeType *derivative) const;

    std::vector<std::pair<std::string, Segment2d>> named_segments_;
    std::vector<senseAD::planning_pilot::Segment> bvh_segments_;
    std::vector<senseAD::planning_pilot::Polyline> bvh_polylines_;
    senseAD::planning_pilot::PolyBVH bvh_;

    double cutoff_distance_ = 0.0;
};

class MsdProblemWithBuffer final : public MinSegmentDistanceProblem {
 public:
    struct SegmentType {
        std::string id;
        Segment2d segment;
        double buffer = 0.0;
        double lane_width = 0.0;
        double length = 0.0;
    };

    MsdProblemWithBuffer(std::vector<SegmentType> named_segments_with_buffer,
                         double cutoff_distance,
                         const std::vector<int> &optional_start_segment_ids);

    const SegmentType *GetNearestSegmentWithBuffer(const Vec2d &point) const;
    void GetNearestSegmentsWithBuffer(
        const std::vector<Vec2d> &points,
        std::vector<const SegmentType *> *out_segments) const;
    void GetNearestSegmentsWithBuffer(
        const std::vector<Vec2d> &points,
        std::vector<const SegmentType *> *out_segments,
        BatchQueryWorkspace *workspace) const;

 private:
    static std::vector<std::pair<std::string, Segment2d>> ExtractNamedSegments(
        const std::vector<SegmentType> &named_segments_with_buffer);

    std::vector<SegmentType> named_segments_with_buffer_;
};

}  // namespace planning
}  // namespace pnc_x
