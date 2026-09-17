

#include "common/path_sl_boundary.h"
#include "math/geometry/util.h"
#include "math/piecewise_linear_function.h"
namespace pnc_x {
namespace planning {
namespace {
constexpr double kDesiredPathSlBoundarySampleStep = 5.0;
constexpr int kPathSlBoundaryMinInterval = 2;
}  // namespace

void PathSlBoundary::BuildResampledData() {
    PiecewiseLinearFunction<double, double> ref_center_l_s_plf(
        s_vec_, ref_center_l_vec_);
    PiecewiseLinearFunction<double, double> right_l_s_plf(s_vec_, right_l_vec_);
    PiecewiseLinearFunction<double, double> left_l_s_plf(s_vec_, left_l_vec_);
    PiecewiseLinearFunction<double, double> opt_right_l_s_plf(s_vec_,
                                                              opt_right_l_vec_);
    PiecewiseLinearFunction<double, double> opt_left_l_s_plf(s_vec_,
                                                             opt_left_l_vec_);
    PiecewiseLinearFunction<double, double> target_right_l_s_plf(
        s_vec_, target_right_l_vec_);
    PiecewiseLinearFunction<double, double> target_left_l_s_plf(
        s_vec_, target_left_l_vec_);
    PiecewiseLinearFunction<Vec2d, double> ref_center_xy_s_plf(
        s_vec_, ref_center_xy_vec_);
    PiecewiseLinearFunction<Vec2d, double> right_xy_s_plf(s_vec_,
                                                          right_xy_vec_);
    PiecewiseLinearFunction<Vec2d, double> left_xy_s_plf(s_vec_, left_xy_vec_);

    PiecewiseLinearFunction<Vec2d, double> target_right_xy_s_plf(
        s_vec_, target_right_xy_vec_);
    PiecewiseLinearFunction<Vec2d, double> target_left_xy_s_plf(
        s_vec_, target_left_xy_vec_);
    const double start_s = s_vec_.front();
    const double end_s = s_vec_.back();
    const int num_interval = std::max<int>(
        static_cast<int>((end_s - start_s) / kDesiredPathSlBoundarySampleStep),
        kPathSlBoundaryMinInterval);
    sample_interval_ = (end_s - start_s) / static_cast<double>(num_interval);
    const int num_points = num_interval + 1;
    resampled_s_vec_.reserve(num_points);
    for (int i = 0; i < num_points; ++i) {
        const double cur_s = start_s + (static_cast<double>(i) * sample_interval_);
        resampled_s_vec_.push_back(cur_s);
    }
    resampled_ref_center_l_vec_ = ref_center_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_right_l_vec_ = right_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_left_l_vec_ = left_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_opt_right_l_vec_ = opt_right_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_opt_left_l_vec_ = opt_left_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_target_right_l_vec_ =
        target_right_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_target_left_l_vec_ =
        target_left_l_s_plf.Evaluate(resampled_s_vec_);
    resampled_ref_center_xy_vec_ =
        ref_center_xy_s_plf.Evaluate(resampled_s_vec_);
    resampled_right_xy_vec_ = right_xy_s_plf.Evaluate(resampled_s_vec_);
    resampled_left_xy_vec_ = left_xy_s_plf.Evaluate(resampled_s_vec_);

    resampled_target_right_xy_vec_ =
        target_right_xy_s_plf.Evaluate(resampled_s_vec_);
    resampled_target_left_xy_vec_ =
        target_left_xy_s_plf.Evaluate(resampled_s_vec_);
}

PathSlBoundary::PathSlBoundary(std::vector<double> s,
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
                               std::vector<Vec2d> target_left_xy)
    : s_vec_(std::move(s)),
      ref_center_l_vec_(std::move(ref_center_l)),
      right_l_vec_(std::move(right_l)),
      left_l_vec_(std::move(left_l)),
      opt_right_l_vec_(std::move(opt_right_l)),
      opt_left_l_vec_(std::move(opt_left_l)),
      target_right_l_vec_(std::move(target_right_l)),
      target_left_l_vec_(std::move(target_left_l)),
      ref_center_xy_vec_(std::move(ref_center_xy)),
      right_xy_vec_(std::move(right_xy)),
      left_xy_vec_(std::move(left_xy)),

      target_right_xy_vec_(std::move(target_right_xy)),
      target_left_xy_vec_(std::move(target_left_xy)) {
    const int vec_size = s_vec_.size();
    XCHECK_GT(vec_size, 1);
    XCHECK_EQ(vec_size, ref_center_l_vec_.size());
    XCHECK_EQ(vec_size, ref_center_xy_vec_.size());
    XCHECK_EQ(vec_size, right_l_vec_.size());
    XCHECK_EQ(vec_size, left_l_vec_.size());
    XCHECK_EQ(vec_size, opt_right_l_vec_.size());
    XCHECK_EQ(vec_size, opt_left_l_vec_.size());
    XCHECK_EQ(vec_size, target_right_l_vec_.size());
    XCHECK_EQ(vec_size, target_left_l_vec_.size());
    XCHECK_EQ(vec_size, right_xy_vec_.size());
    XCHECK_EQ(vec_size, left_xy_vec_.size());

    XCHECK_EQ(vec_size, target_right_xy_vec_.size());
    XCHECK_EQ(vec_size, target_left_xy_vec_.size());
    BuildResampledData();
}

PathSlBoundary::PathSlBoundary(std::vector<double> s,
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
                               std::vector<Vec2d> target_left_xy)
    : s_vec_(std::move(s)),
      right_l_vec_(std::move(right_l)),
      left_l_vec_(std::move(left_l)),
      opt_right_l_vec_(std::move(opt_right_l)),
      opt_left_l_vec_(std::move(opt_left_l)),
      target_right_l_vec_(std::move(target_right_l)),
      target_left_l_vec_(std::move(target_left_l)),
      right_xy_vec_(std::move(right_xy)),
      left_xy_vec_(std::move(left_xy)),

      target_right_xy_vec_(std::move(target_right_xy)),
      target_left_xy_vec_(std::move(target_left_xy)) {
    const int vec_size = s_vec_.size();
    XCHECK_GT(vec_size, 1);
    XCHECK_EQ(vec_size, right_l_vec_.size());
    XCHECK_EQ(vec_size, left_l_vec_.size());
    XCHECK_EQ(vec_size, opt_right_l_vec_.size());
    XCHECK_EQ(vec_size, opt_left_l_vec_.size());
    XCHECK_EQ(vec_size, target_right_l_vec_.size());
    XCHECK_EQ(vec_size, target_left_l_vec_.size());
    XCHECK_EQ(vec_size, right_xy_vec_.size());
    XCHECK_EQ(vec_size, left_xy_vec_.size());

    XCHECK_EQ(vec_size, target_right_xy_vec_.size());
    XCHECK_EQ(vec_size, target_left_xy_vec_.size());

    ref_center_l_vec_.reserve(vec_size);
    ref_center_xy_vec_.reserve(vec_size);
    for (int i = 0; i < vec_size; ++i) {
        ref_center_l_vec_.emplace_back(0.5 *
                                       (right_l_vec_[i] + left_l_vec_[i]));
        ref_center_xy_vec_.emplace_back(0.5 *
                                        (right_xy_vec_[i] + left_xy_vec_[i]));
    }
    BuildResampledData();
}

void PathSlBoundary::ModifySoftBoundByDpLabel(const DrivePassage &drive_passage,
                                              const double s_catchup,
                                              const double s_overtake,
                                              const double l_press,
                                              const bool is_left) {
    const double ego_width = 2.05;
    const double lat_buffer = 1.6;
    for (int idx_s = 0; idx_s < s_vec_.size(); idx_s++) {
        if (s_vec_[idx_s] < s_catchup) continue;
        if (s_vec_[idx_s] > s_overtake) break;
        const auto &station = drive_passage.station(StationIndex(idx_s));
        if (is_left) {
            target_right_l_vec_[idx_s] =
                std::fmax(target_right_l_vec_[idx_s], l_press);
            target_left_l_vec_[idx_s] = std::fmax(
                target_left_l_vec_[idx_s], l_press + ego_width + lat_buffer);
        } else {
            target_left_l_vec_[idx_s] =
                std::fmin(target_left_l_vec_[idx_s], l_press);
            target_right_l_vec_[idx_s] = std::fmin(
                target_right_l_vec_[idx_s], l_press - ego_width - lat_buffer);
        }
        target_left_xy_vec_[idx_s] =
            station.lat_point(target_left_l_vec_[idx_s]);
        target_right_xy_vec_[idx_s] =
            station.lat_point(target_right_l_vec_[idx_s]);
    }

    PiecewiseLinearFunction<double, double> target_right_l_s_plf(
        s_vec_, target_right_l_vec_);
    PiecewiseLinearFunction<double, double> target_left_l_s_plf(
        s_vec_, target_left_l_vec_);
    PiecewiseLinearFunction<Vec2d, double> target_right_xy_s_plf(
        s_vec_, target_right_xy_vec_);
    PiecewiseLinearFunction<Vec2d, double> target_left_xy_s_plf(
        s_vec_, target_left_xy_vec_);
    for (int idx_res_s = 0; idx_res_s < resampled_s_vec_.size(); idx_res_s++) {
        double resample_s = resampled_s_vec_[idx_res_s];
        if (resample_s < s_catchup) continue;
        if (resample_s > s_overtake) break;
        resampled_target_right_l_vec_[idx_res_s] =
            target_right_l_s_plf.Evaluate(resample_s);
        resampled_target_right_xy_vec_[idx_res_s] =
            target_right_xy_s_plf.Evaluate(resample_s);
        resampled_target_left_l_vec_[idx_res_s] =
            target_left_l_s_plf.Evaluate(resample_s);
        resampled_target_left_xy_vec_[idx_res_s] =
            target_left_xy_s_plf.Evaluate(resample_s);
    }
}

void PathSlBoundary::ModifyHardBoundByDpLabel(const DrivePassage &drive_passage,
                                              const double s_catchup,
                                              const double s_overtake,
                                              const double l_press,
                                              const bool is_left) {
    const double ego_width = 2.05;
    const double lat_buffer = 1.6;
    for (int idx_s = 0; idx_s < s_vec_.size(); idx_s++) {
        if (s_vec_[idx_s] < s_catchup) continue;
        if (s_vec_[idx_s] > s_overtake) break;
        const auto &station = drive_passage.station(StationIndex(idx_s));
        if (is_left) {
            right_l_vec_[idx_s] = std::fmax(right_l_vec_[idx_s], l_press);
            left_l_vec_[idx_s] =
                std::fmax(left_l_vec_[idx_s], l_press + ego_width + lat_buffer);
        } else {
            left_l_vec_[idx_s] = std::fmin(left_l_vec_[idx_s], l_press);
            right_l_vec_[idx_s] = std::fmin(right_l_vec_[idx_s],
                                            l_press - ego_width - lat_buffer);
        }
        left_xy_vec_[idx_s] = station.lat_point(left_l_vec_[idx_s]);
        right_xy_vec_[idx_s] = station.lat_point(right_l_vec_[idx_s]);
    }

    PiecewiseLinearFunction<double, double> right_l_s_plf(s_vec_, right_l_vec_);
    PiecewiseLinearFunction<double, double> left_l_s_plf(s_vec_, left_l_vec_);
    PiecewiseLinearFunction<Vec2d, double> right_xy_s_plf(s_vec_,
                                                          right_xy_vec_);
    PiecewiseLinearFunction<Vec2d, double> left_xy_s_plf(s_vec_, left_xy_vec_);
    for (int idx_res_s = 0; idx_res_s < resampled_s_vec_.size(); idx_res_s++) {
        double resample_s = resampled_s_vec_[idx_res_s];
        if (resample_s < s_catchup) continue;
        if (resample_s > s_overtake) break;
        resampled_right_l_vec_[idx_res_s] = right_l_s_plf.Evaluate(resample_s);
        resampled_right_xy_vec_[idx_res_s] =
            right_xy_s_plf.Evaluate(resample_s);
        resampled_left_l_vec_[idx_res_s] = left_l_s_plf.Evaluate(resample_s);
        resampled_left_xy_vec_[idx_res_s] = left_xy_s_plf.Evaluate(resample_s);
    }
}

bool PathSlBoundary::IsEmpty() const { return s_vec_.empty(); }
int PathSlBoundary::size() const { return s_vec_.size(); }

absl::Span<const double> PathSlBoundary::s_vector() const { return s_vec_; }

double PathSlBoundary::start_s() const {
    if (!XCHECK(!s_vec_.empty())) {
        return 0.0;
    }
    return s_vec_.front();
}

double PathSlBoundary::end_s() const {
    if (!XCHECK(!s_vec_.empty())) {
        return 0.0;
    }
    return s_vec_.back();
}

absl::Span<const double> PathSlBoundary::reference_center_l_vector() const {
    return ref_center_l_vec_;
}

absl::Span<const double> PathSlBoundary::right_l_vector() const {
    return right_l_vec_;
}

absl::Span<const double> PathSlBoundary::left_l_vector() const {
    return left_l_vec_;
}

absl::Span<const double> PathSlBoundary::opt_right_l_vector() const {
    return opt_right_l_vec_;
}

absl::Span<const double> PathSlBoundary::opt_left_l_vector() const {
    return opt_left_l_vec_;
}

absl::Span<const double> PathSlBoundary::target_right_l_vector() const {
    return target_right_l_vec_;
}

absl::Span<const double> PathSlBoundary::target_left_l_vector() const {
    return target_left_l_vec_;
}

absl::Span<const Vec2d> PathSlBoundary::reference_center_xy_vector() const {
    return ref_center_xy_vec_;
}

absl::Span<const Vec2d> PathSlBoundary::right_xy_vector() const {
    return right_xy_vec_;
}

absl::Span<const Vec2d> PathSlBoundary::left_xy_vector() const {
    return left_xy_vec_;
}

absl::Span<const Vec2d> PathSlBoundary::target_right_xy_vector() const {
    return target_right_xy_vec_;
}

absl::Span<const Vec2d> PathSlBoundary::target_left_xy_vector() const {
    return target_left_xy_vec_;
}

std::vector<SlBoundaryType> PathSlBoundary::right_type_vector() const {
    return right_type_vec_;
}

std::vector<SlBoundaryType> PathSlBoundary::left_type_vector() const {
    return left_type_vec_;
}

void PathSlBoundary::SwapOptBoundary() {
    right_l_vec_.swap(opt_right_l_vec_);
    left_l_vec_.swap(opt_left_l_vec_);

    resampled_right_l_vec_.swap(resampled_opt_right_l_vec_);
    resampled_left_l_vec_.swap(resampled_opt_left_l_vec_);
}

}  // namespace planning
}  // namespace pnc_x
