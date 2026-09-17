
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/log.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class CostHelper {
 public:
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    explicit CostHelper(int horizon_in, std::string name_in = "")
        : horizon_(horizon_in), name_(std::move(name_in)) {
        XCHECK_GT(horizon_, 0);
    }

    virtual ~CostHelper() {}

    const std::string &name() const { return name_; }

    virtual void Update(const StatesType &xs, const ControlsType &us) {}

    int horizon() const { return horizon_; }

 private:
    int horizon_ = 0;
    std::string name_ = "";
};

}  // namespace planning
}  // namespace pnc_x
