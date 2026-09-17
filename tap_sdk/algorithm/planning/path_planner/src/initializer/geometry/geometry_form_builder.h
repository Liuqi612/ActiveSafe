
#pragma once

#include <memory>
#include <vector>

#include "pncx_initializer.pb.h"
#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_state.h"
#include "math/frenet_common.h"
#include "math/frenet_frame.h"
#include "math/piecewise_linear_function.h"
#include "math/vec.h"
#include "router/drive_passage.h"
#include <absl/status/statusor.h>

namespace pnc_x {
namespace planning {

struct DrivePassageSamplePoint {
    Vec2d xy;
    double l;
    double accumulated_s;
    int station_index;
};

class GeometryFormBuilder {
 public:
    GeometryFormBuilder() = default;

    explicit GeometryFormBuilder(const DrivePassage *passage,
                                 double max_sampling_acc_s,
                                 double s_from_start_with_diff);

    bool InitResult() const { return init_; }

    absl::StatusOr<PiecewiseLinearGeometry> BuildCubicSpiralGeometry(
        const GeometryState &start_state,
        const DrivePassageSamplePoint &end) const;

    absl::StatusOr<PiecewiseLinearGeometry> BuildCubicSpiralGeometry(
        const DrivePassageSamplePoint &start,
        const DrivePassageSamplePoint &end) const;

    absl::StatusOr<PiecewiseLinearGeometry> BuildQuinticSpiralGeometry(
        const GeometryState &start_state,
        const DrivePassageSamplePoint &end) const;

    absl::StatusOr<PiecewiseLinearGeometry> BuildQuinticSpiralGeometry(
        const DrivePassageSamplePoint &start,
        const DrivePassageSamplePoint &end) const;

    absl::StatusOr<PiecewiseLinearGeometry> BuildLateralQuinticPolyGeometry(
        const GeometryState &start_state,
        const DrivePassageSamplePoint &end) const;

    absl::StatusOr<PiecewiseLinearGeometry> BuildLateralQuinticPolyGeometry(
        const DrivePassageSamplePoint &start,
        const DrivePassageSamplePoint &end) const;

    double LookUpRefK(const double station) const {
        return k_s_.Evaluate(station);
    }

    FrenetCoordinate LookUpSL(const Vec2d &xy) const {
        return smoothed_frenet_frame_->XYToSL(xy);
    }

    double smooth_dp_sampling_acc_s() const {
        return default_max_sampling_acc_s_;
    }

    void FillSmoothDrivePassage(GeometryGraphProto *proto) const;

 private:
    const DrivePassage *passage_;
    double default_max_sampling_acc_s_;
    std::vector<double> station_k_;

    PiecewiseLinearFunction<double, double> k_s_;
    std::vector<Vec2d> smoothed_xy_;
    PiecewiseLinearFunction<double, double> smoothed_hsin_s_;
    PiecewiseLinearFunction<double, double> smoothed_hcos_s_;
    std::unique_ptr<FrenetFrame> smoothed_frenet_frame_;
    std::unique_ptr<FrenetFrame> frenet_frame_;

    bool init_ = false;
};

}  // namespace planning
}  // namespace pnc_x
