
#pragma once

#include <algorithm>
#include <limits>
#include <string>
#include <utility>
#include <vector>

#include "initializer/geometry/geometry_graph.h"
#include "initializer/initializer_input.h"
#include "initializer/motion_graph.h"
#include "initializer/ref_speed_table.h"
#include "pncx_initializer_config.pb.h"

namespace pnc_x {
namespace planning {

struct GeometryEdgeInfo {
    const GeometryForm *geometry_form = nullptr;
    std::vector<GeometryState> states;
    bool terminating = false;
};

struct MotionEdgeInfo {
    double start_t = 0.0;
    const MotionForm *motion_form = nullptr;
    std::vector<MotionState> const_interval_states;
    std::vector<MotionState> equal_interval_states;
};

class FeatureCost {
 public:
    explicit FeatureCost(std::string local_name) : name_(std::move(local_name)) {}

    virtual void ComputeCost(const MotionEdgeInfo &edge_info,
                             absl::Span<double> cost) const {}

    virtual void ComputeCost(const GeometryEdgeInfo &edge_info,
                             absl::Span<double> cost) const {}

    std::string name() const { return name_; }

    virtual ~FeatureCost() {}

 private:
    std::string name_;
};

}  // namespace planning
}  // namespace pnc_x
