
#pragma once

#include <memory>
#include <utility>
#include <vector>

#include "initializer/geometry/geometry_form.h"
#include "initializer/geometry/geometry_state.h"
#include "initializer/motion_state.h"

namespace pnc_x {
namespace planning {

enum MotionFormType {
    CONST_ACCEL_MOTION = 1,
    STATIONARY_MOTION = 2,
    COMPLETE_MOTION = 3,
};
struct SampledMotionFormStates {
    std::vector<MotionState> const_interval_states;
    std::vector<MotionState> equal_interval_states;
};

class MotionForm {
 public:
    virtual double duration() const = 0;
    virtual MotionState GetStartMotionState() const = 0;
    virtual MotionState GetEndMotionState() const = 0;
    virtual MotionState State(double t) const = 0;
    virtual const GeometryForm *geometry() const = 0;
    virtual MotionFormType type() const = 0;

    virtual SampledMotionFormStates SampleStates() const = 0;

    virtual std::vector<MotionState> SampleEqualIntervalStates() const = 0;
    virtual ~MotionForm() {}

    static int kConstTimeIntervalSampleStep;

    static int kMinEqualTimeIntervalSampleStep;
    static int kMaxEqualTimeIntervalSampleStep;
    static double kDesireEqualTimeInterval;
};

class ConstAccelMotion final : public MotionForm {
 public:
    explicit ConstAccelMotion(double init_v,
                              double init_a,
                              const GeometryForm *geometry);

    explicit ConstAccelMotion(std::pair<double, double> v_pair,
                              const GeometryForm *geometry);

    double duration() const override { return duration_; }
    MotionState GetStartMotionState() const override;
    MotionState GetEndMotionState() const override;

    MotionState State(double t) const override;

    const GeometryForm *geometry() const override { return geometry_; }
    MotionFormType type() const override {
        return MotionFormType::CONST_ACCEL_MOTION;
    }

    SampledMotionFormStates SampleStates() const override;
    std::vector<MotionState> SampleEqualIntervalStates() const override;

 private:
    double init_v_ = 0.0;
    double a_ = 0.0;
    double duration_ = 0.0;

    double stop_time_ = 0.0;
    double stop_distance_ = 0.0;

    const GeometryForm *geometry_ = nullptr;
};

class StationaryMotion final : public MotionForm {
 public:
    explicit StationaryMotion(double duration,
                              const StationaryGeometry *geometry)
        : duration_(duration), geometry_(geometry) {}

    explicit StationaryMotion(double duration, GeometryState state)
        : duration_(duration),
          geometry_form_(
              std::make_unique<StationaryGeometry>(std::move(state))),
          geometry_(geometry_form_.get()) {}
    double duration() const override { return duration_; }
    MotionState GetStartMotionState() const override;
    MotionState GetEndMotionState() const override;
    MotionState State(double t) const override;

    const GeometryForm *geometry() const override { return geometry_; }
    MotionFormType type() const override {
        return MotionFormType::STATIONARY_MOTION;
    }
    SampledMotionFormStates SampleStates() const override;
    std::vector<MotionState> SampleEqualIntervalStates() const override;

 private:
    std::vector<MotionState> Sample(double d_t) const;
    double duration_ = 0.0;

    std::unique_ptr<StationaryGeometry> geometry_form_;

    const GeometryForm *geometry_ = nullptr;
};

}  // namespace planning
}  // namespace pnc_x
