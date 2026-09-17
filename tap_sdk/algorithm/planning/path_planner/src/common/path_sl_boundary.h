
#pragma once

#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <ostream>
#include <utility>
#include <vector>

#include "math/util.h"
#include "math/vec.h"
#include "router/drive_passage.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace planning {

enum SlBoundaryType {
    TYPE_CURB = 0,
    TYPE_LANE_BOUNDARY = 1,
    TYPE_OBJECT = 2,
    TYPE_VEGETATION = 3
};

class PathSlBoundary {
 public:
    PathSlBoundary() = default;

    explicit PathSlBoundary(std::vector<double> s,
                            std::vector<double> ref_center_l,
                            std::vector<double> right_l,
                            std::vector<double> left_l,
                            std::vector<double> opt_right_l,
                            std::vector<double> opt_left_l,
                            std::vector<double> target_right_l,
                            std::vector<double> target_left_l,
                            std::vector<Vec2d> ref_center_xy,
                            std::vector<Vec2d> right_xy,
                            std::vector<Vec2d> left_xy,
                            std::vector<Vec2d> opt_right_xy,
                            std::vector<Vec2d> opt_left_xy,
                            std::vector<Vec2d> target_right_xy,
                            std::vector<Vec2d> target_left_xy);

    explicit PathSlBoundary(std::vector<double> s,
                            std::vector<double> right_l,
                            std::vector<double> left_l,
                            std::vector<double> opt_right_l,
                            std::vector<double> opt_left_l,
                            std::vector<double> target_right_l,
                            std::vector<double> target_left_l,
                            std::vector<Vec2d> right_xy,
                            std::vector<Vec2d> left_xy,
                            std::vector<Vec2d> opt_right_xy,
                            std::vector<Vec2d> opt_left_xy,
                            std::vector<Vec2d> target_right_xy,
                            std::vector<Vec2d> target_left_xy);

    bool IsEmpty() const;
    int size() const;

    absl::Span<const double> s_vector() const;

    double start_s() const;

    double end_s() const;

    absl::Span<const double> reference_center_l_vector() const;

    absl::Span<const double> right_l_vector() const;

    absl::Span<const double> left_l_vector() const;

    absl::Span<const double> opt_right_l_vector() const;

    absl::Span<const double> opt_left_l_vector() const;

    absl::Span<const double> target_right_l_vector() const;

    absl::Span<const double> target_left_l_vector() const;

    absl::Span<const Vec2d> reference_center_xy_vector() const;

    absl::Span<const Vec2d> right_xy_vector() const;

    absl::Span<const Vec2d> left_xy_vector() const;

    absl::Span<const Vec2d> target_right_xy_vector() const;

    absl::Span<const Vec2d> target_left_xy_vector() const;

    std::vector<SlBoundaryType> right_type_vector() const;

    std::vector<SlBoundaryType> left_type_vector() const;

    std::pair<double, double> QueryBoundaryL(double s) const;
    std::pair<double, double> QueryBoundaryLxyt(double s) const;

    std::pair<double, double> QueryOptBoundaryL(double s) const;

    std::pair<double, double> QueryTargetBoundaryL(double s) const;

    std::pair<Vec2d, Vec2d> QueryBoundaryXY(double s) const;

    std::pair<Vec2d, Vec2d> QueryOptBoundaryXY(double s) const;

    std::pair<Vec2d, Vec2d> QueryTargetBoundaryXY(double s) const;

    double QueryReferenceCenterL(double s) const;
    Vec2d QueryReferenceCenterXY(double s) const;

    void ModifySoftBoundByDpLabel(const DrivePassage &drive_passage,
                                  const double s_catchup,
                                  const double s_overtake,
                                  const double l_press,
                                  const bool is_left);

    void ModifyHardBoundByDpLabel(const DrivePassage &drive_passage,
                                  const double s_catchup,
                                  const double s_overtake,
                                  const double l_press,
                                  const bool is_left);

    void SwapOptBoundary();

    void DumpToDebugFrame(int task_i, std::string additional_info = "") const;

 private:
    void BuildResampledData();

    std::pair<int, double> FindLerpInfo(double s) const;
    std::pair<int, double> FindLerpInfoXYT(double s) const;

    std::vector<double> s_vec_;
    std::vector<double> ref_center_l_vec_;

    std::vector<double> right_l_vec_;
    std::vector<double> left_l_vec_;

    std::vector<double> opt_right_l_vec_;
    std::vector<double> opt_left_l_vec_;

    std::vector<double> target_right_l_vec_;
    std::vector<double> target_left_l_vec_;
    std::vector<Vec2d> ref_center_xy_vec_;
    std::vector<Vec2d> right_xy_vec_;
    std::vector<Vec2d> left_xy_vec_;

    std::vector<Vec2d> target_right_xy_vec_;
    std::vector<Vec2d> target_left_xy_vec_;
    std::vector<SlBoundaryType> right_type_vec_;
    std::vector<SlBoundaryType> left_type_vec_;

    std::vector<double> resampled_s_vec_;
    std::vector<double> resampled_ref_center_l_vec_;

    std::vector<double> resampled_right_l_vec_;
    std::vector<double> resampled_left_l_vec_;
    std::vector<double> resampled_opt_right_l_vec_;
    std::vector<double> resampled_opt_left_l_vec_;

    std::vector<double> resampled_target_right_l_vec_;
    std::vector<double> resampled_target_left_l_vec_;
    std::vector<Vec2d> resampled_ref_center_xy_vec_;
    std::vector<Vec2d> resampled_right_xy_vec_;
    std::vector<Vec2d> resampled_left_xy_vec_;

    std::vector<Vec2d> resampled_target_right_xy_vec_;
    std::vector<Vec2d> resampled_target_left_xy_vec_;
    double sample_interval_ = 0.0;
};

inline std::pair<double, double> PathSlBoundary::QueryBoundaryL(
    double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(Lerp(resampled_right_l_vec_[index],
                               resampled_right_l_vec_[index + 1], factor),
                          Lerp(resampled_left_l_vec_[index],
                               resampled_left_l_vec_[index + 1], factor));
}

inline std::pair<double, double> PathSlBoundary::QueryBoundaryLxyt(
    double s) const {
    std::pair<int, double> index_factor = FindLerpInfoXYT(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(Lerp(resampled_right_l_vec_[index],
                               resampled_right_l_vec_[index + 1], factor),
                          Lerp(resampled_left_l_vec_[index],
                               resampled_left_l_vec_[index + 1], factor));
}

inline std::pair<Vec2d, Vec2d> PathSlBoundary::QueryBoundaryXY(double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(Lerp(resampled_right_xy_vec_[index],
                               resampled_right_xy_vec_[index + 1], factor),
                          Lerp(resampled_left_xy_vec_[index],
                               resampled_left_xy_vec_[index + 1], factor));
}

inline std::pair<double, double> PathSlBoundary::QueryOptBoundaryL(
    double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(Lerp(resampled_opt_right_l_vec_[index],
                               resampled_opt_right_l_vec_[index + 1], factor),
                          Lerp(resampled_opt_left_l_vec_[index],
                               resampled_opt_left_l_vec_[index + 1], factor));
}

inline std::pair<double, double> PathSlBoundary::QueryTargetBoundaryL(
    double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(
        Lerp(resampled_target_right_l_vec_[index],
             resampled_target_right_l_vec_[index + 1], factor),
        Lerp(resampled_target_left_l_vec_[index],
             resampled_target_left_l_vec_[index + 1], factor));
}

inline std::pair<Vec2d, Vec2d> PathSlBoundary::QueryTargetBoundaryXY(
    double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return std::make_pair(
        Lerp(resampled_target_right_xy_vec_[index],
             resampled_target_right_xy_vec_[index + 1], factor),
        Lerp(resampled_target_left_xy_vec_[index],
             resampled_target_left_xy_vec_[index + 1], factor));
}

inline double PathSlBoundary::QueryReferenceCenterL(double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return Lerp(resampled_ref_center_l_vec_[index],
                resampled_ref_center_l_vec_[index + 1], factor);
}

inline Vec2d PathSlBoundary::QueryReferenceCenterXY(double s) const {
    std::pair<int, double> index_factor = FindLerpInfo(s);
    std::size_t index = static_cast<std::size_t>(index_factor.first);
    double factor = index_factor.second;
    return Lerp(resampled_ref_center_xy_vec_[index],
                resampled_ref_center_xy_vec_[index + 1], factor);
}

inline std::pair<int, double> PathSlBoundary::FindLerpInfo(double s) const {
    if (sample_interval_ == 0.0) {
        return {0, 0};
    }
    int idx = static_cast<int>(
        std::floor((s - resampled_s_vec_.front()) / sample_interval_));
    idx = boost::algorithm::clamp<int>(
        idx, 0, static_cast<int>(resampled_s_vec_.size()) - 2);
    return {idx,
            (s - resampled_s_vec_[static_cast<std::size_t>(idx)]) /
                sample_interval_};
}

inline std::pair<int, double> PathSlBoundary::FindLerpInfoXYT(double s) const {
    if (sample_interval_ == 0.0) {
        return {0, 0.0};
    }

    int idx = static_cast<int>(
        std::floor((s - resampled_s_vec_.front()) / sample_interval_));
    idx = boost::algorithm::clamp<int>(
        idx, 0, static_cast<int>(resampled_s_vec_.size()) - 2);

    return {idx,
            (s - resampled_s_vec_[static_cast<std::size_t>(idx)]) /
                sample_interval_};
}

}  // namespace planning
}  // namespace pnc_x
