
#pragma once

#include <optional>
#include <string>
#include <utility>
#include <vector>

#include <absl/types/span.h>
#include <boost/optional.hpp>

namespace pnc_x {
namespace planning {

class SpeedLimit {
 public:
    struct SpeedLimitRange {
        double start_s = 0.0;
        double end_s = 0.0;
        double speed_limit = 0.0;
        std::string info;
    };

    struct SpeedLimitInfo {
        SpeedLimitInfo() = delete;
        explicit SpeedLimitInfo(const SpeedLimitRange &speed_limit_range)
            : speed_limit(speed_limit_range.speed_limit),
              info(speed_limit_range.info) {}

        SpeedLimitInfo(double speed, std::string newinfo)
            : speed_limit(speed), info(std::move(newinfo)) {}

        SpeedLimitInfo(const SpeedLimitInfo &other)
            : speed_limit(other.speed_limit), info(other.info) {}

        SpeedLimitInfo &operator=(const SpeedLimitInfo &other) {
            if (&other == this) {
                return *this;
            }
            speed_limit = other.speed_limit;
            info = other.info;
            return *this;
        }

        SpeedLimitInfo(SpeedLimitInfo &&) = default;
        SpeedLimitInfo &operator=(SpeedLimitInfo &&) = default;
        ~SpeedLimitInfo() noexcept = default;

        double speed_limit = 0.0;
        std::string info;
    };

    explicit SpeedLimit(
        const std::vector<SpeedLimitRange> &new_speed_limit_ranges);

    boost::optional<SpeedLimitInfo> GetSpeedLimitInfoByS(double s) const;

    boost::optional<double> GetSpeedLimitByS(double s) const;

    absl::Span<const SpeedLimitRange> speed_limit_ranges() const {
        return speed_limit_ranges_;
    }

 private:
    std::vector<SpeedLimitRange> speed_limit_ranges_;
};

}  // namespace planning
}  // namespace pnc_x
