

#include "util/time_util.h"

namespace pnc_x {

absl::Time FromProto(const pnc_x::planning::Timestamp &proto) {
    return absl::FromUnixSeconds(proto.seconds()) +
           absl::Nanoseconds(proto.nanos());
}

void ToProto(absl::Time time, pnc_x::planning::Timestamp *proto) {
    const int64_t s = absl::ToUnixSeconds(time);
    proto->set_seconds(s);
    proto->set_nanos(static_cast<int32_t>((time - absl::FromUnixSeconds(s)) /
                                          absl::Nanoseconds(1)));
}

double ToUnixDoubleSeconds(absl::Time t) {
    return absl::ToDoubleSeconds(absl::time_internal::ToUnixDuration(t));
}

absl::Time FromUnixDoubleSeconds(double s) {
    return absl::time_internal::FromUnixDuration(
        absl::time_internal::MakePosDoubleDuration(s));
}

double UnixNow() {
    return ToUnixDoubleSeconds(absl::Now());
}

std::string FetchCurrentTimeString() {
    return absl::FormatTime("%Y-%m-%d %H:%M:%S", absl::Now(),
                            absl::UTCTimeZone());
}

std::string FetchTimeString(const absl::Time &time) {
    return absl::FormatTime("%Y-%m-%d %H:%M:%S", time, absl::UTCTimeZone());
}

std::string FetchTimeString(const absl::Time &time, absl::TimeZone zone) {
    return absl::FormatTime("%Y-%m-%d %H:%M:%S", time, zone);
}

constexpr int64_t SecondsToMicroSeconds(double s) {
    return static_cast<int64_t>(s * 1E6);
}

}  // namespace pnc_x
