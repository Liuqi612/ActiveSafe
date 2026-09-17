#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "optimization/ddp/ddp_optimizer_hook.h"
#include "optimization/problem/cost.h"
#include "static_boundary_cost_lite.h"
#include "aggregate_static_object_cost.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class PerStepCostRecorderHook : public DdpOptimizerHook<PROB> {
public:
  using StateType = typename PROB::StateType;
  using ControlType = typename PROB::ControlType;
  using StatesType = typename PROB::StatesType;
  using ControlsType = typename PROB::ControlsType;
  using OptimizerInspector =
      typename DdpOptimizerHook<PROB>::OptimizerInspector;

  struct Row {
    std::string name; // 命名分项名（DividedG 的子项名）
    bool is_soft = false;

    // 每步的 cost 值（长度 = horizon）
    std::vector<double> values;
    double total = 0.0;

    std::vector<GradArrow> arrows;
  };

  // costs: 传同一批 Cost 实例；using_scale=true
  // 表示取“带scale”的值（与优化一致）
  PerStepCostRecorderHook(int horizon, const std::vector<Cost<PROB> *> &costs,
                          bool using_scale = true,
                          double store_threshold = -1.0 /*<0表示不过滤*/)
      : DdpOptimizerHook<PROB>(horizon), costs_(costs),
        using_scale_(using_scale), store_threshold_(store_threshold) {}

  void OnSolveEnd(const StatesType &xs, const ControlsType &us,
                  const OptimizerInspector & /*oi*/) override {
    Collect(xs, us);
  }

  // 如果你想每轮迭代都记录，把上面那行挪到这里用即可
  // void OnIterationEnd(int iter, const StatesType& xs, const ControlsType& us,
  //                     const OptimizerInspector& oi) override { Collect(xs,
  //                     us); }

  const std::vector<Row> &table() const { return rows_; }

  // 可选：按名字查一行
  const Row *FindRow(const std::string &name) const {
    auto it = index_.find(name);
    return (it == index_.end()) ? nullptr : &rows_[it->second];
  }

private:
  void Collect(const StatesType &xs, const ControlsType &us) {
    const int H = DdpOptimizerHook<PROB>::horizon();
    rows_.clear();
    index_.clear();

    for (auto *cost : costs_) {
      for (int k = 0; k < H; ++k) {
        const StateType xk = PROB::GetStateAtStep(xs, k);
        const ControlType uk = PROB::GetControlAtStep(us, k);

        const auto div = cost->EvaluateGWithDebugInfo(k, xk, uk, using_scale_);
        const auto &boundary_info = cost->EvaluateBoundary(k);
        int index = 0;
        for (const auto &sub : div.gs()) {
          std::string name = sub.name;
          auto it = index_.find(name);
          if (it == index_.end()) {
            Row r;
            r.name = name;
            r.is_soft = sub.is_soft;
            r.values.assign(H, 0.0);
            r.arrows.resize(H); // 箭头后面填充
            index_[name] = static_cast<int>(rows_.size());
            rows_.push_back(std::move(r));
          }
          Row &r = rows_[index_[name]];
          r.values[k] = sub.value;
          r.total += sub.value;
          if (boundary_info.has_boundary) {
            if ((index % 2) == 0) {
              r.arrows[k] = boundary_info.outer_arrow;
            } else {
              r.arrows[k] = boundary_info.inner_arrow;
            }
          }
          index++;
        }
      }
    }
  }

  std::vector<Cost<PROB> *> costs_;
  bool using_scale_ = true;
  double store_threshold_ = -1.0;

  std::vector<Row> rows_;
  std::unordered_map<std::string, int> index_; // name -> row idx
};

} // namespace planning
} // namespace pnc_x
