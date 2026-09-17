
#pragma once

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "math/eigen.h"
#include "math/frenet_frame.h"
#include "optimization/problem/cost_helper.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

template <typename PROB>
class CenterLineQueryHelper : public CostHelper<PROB> {
 public:
    using StatesType = typename PROB::StatesType;
    using ControlsType = typename PROB::ControlsType;

    CenterLineQueryHelper(int horizon,
                          const std::vector<Vec2d> &points,
                          int last_real_point_index,
                          std::string name,
                          bool use_qtfm)
        : CostHelper<PROB>(horizon, std::move(name)),
          last_real_point_index_(last_real_point_index) {
        static_cast<void>(use_qtfm);
        XCHECK_GT(points.size(), 1);
        constexpr double kEps = 1e-9;
        for (int idx = 0; idx < points.size() - 1; ++idx) {
            const double dist2 = (points[idx + 1] - points[idx]).squaredNorm();
            XCHECK_GE(dist2, kEps);
        }
        auto frame_or = BuildBVHFrenetFrame(points, false);
        XCHECK(frame_or.ok());
        path_ = std::move(frame_or).value();

        XCHECK_EQ(points.size(), path_->points().size());

        s_l_list_.resize(CostHelper<PROB>::horizon());
        normals_.resize(CostHelper<PROB>::horizon());
        indices_.resize(CostHelper<PROB>::horizon());
        index_pairs_.resize(CostHelper<PROB>::horizon());
        alphas_.resize(CostHelper<PROB>::horizon());
    }

    const std::vector<FrenetCoordinate> &s_l_list() const { return s_l_list_; }
    const std::vector<Vec2d> &normals() const { return normals_; }
    const std::vector<int> &indices() const { return indices_; }
    const std::vector<std::pair<int, int>> &index_pairs() const {
        return index_pairs_;
    }
    const std::vector<double> &alphas() const { return alphas_; }
    const std::vector<double> &s_knots() const { return path_->s_knots(); }
    const std::vector<Vec2d> &tangents() const { return path_->tangents(); }
    const std::vector<Vec2d> &points() const { return path_->points(); }
    int last_real_point_index() const { return last_real_point_index_; }

    void Update(const StatesType &xs, const ControlsType &us) override {
        const auto &raw_indices = path_->raw_indices();
        std::vector<Vec2d> positions;
        positions.reserve(CostHelper<PROB>::horizon());
        for (int k = 0; k < CostHelper<PROB>::horizon(); ++k) {
            positions.push_back(PROB::StateGetPos(PROB::GetStateAtStep(xs, k)));
        }

        path_->XYToSLBatch(positions, &s_l_list_, &normals_, &indices_,
                           &alphas_);
        for (int k = 0; k < CostHelper<PROB>::horizon(); ++k) {
            const int index = indices_[k];
            auto &index_pair = index_pairs_[k];
            index_pair.first = raw_indices[index];
            index_pair.second = raw_indices[index + 1];
        }
    }

    const FrenetFrame &path() const {
        XCHECK_NOTNULL(path_);
        return *path_;
    }

 private:
    std::string name_ = "";
    std::unique_ptr<FrenetFrame> path_;
    int last_real_point_index_;

    std::vector<FrenetCoordinate> s_l_list_;
    std::vector<Vec2d> normals_;
    std::vector<int> indices_;
    std::vector<std::pair<int, int>> index_pairs_;
    std::vector<double> alphas_;
};

}  // namespace planning
}  // namespace pnc_x
