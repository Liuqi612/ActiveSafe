
#pragma once

#ifndef PNC_UTILS_TIME_UTIL_H_
#define PNC_UTILS_TIME_UTIL_H_

#include <cstdint>
#include <string>

#include "pncx_timestamp.pb.h"
#include <absl/time/clock.h>
#include <absl/time/time.h>
#include <google/protobuf/util/time_util.h>

namespace pnc_x {

constexpr absl::Time kMaxTime = absl::FromUnixSeconds(
    google::protobuf::util::TimeUtil::kTimestampMaxSeconds);

double ToUnixDoubleSeconds(absl::Time t);

absl::Time FromUnixDoubleSeconds(double s);

double UnixNow();

std::string FetchCurrentTimeString();

std::string FetchTimeString(const absl::Time &time);

std::string FetchTimeString(const absl::Time &time, absl::TimeZone zone);

constexpr double MicroSecondsToSeconds(int64_t microseconds) {
    return static_cast<double>(microseconds) * 1E-6;
}

constexpr int64_t SecondsToMicroSeconds(double s);

absl::Time FromProto(const pnc_x::planning::Timestamp &proto);

void ToProto(absl::Time time, pnc_x::planning::Timestamp *proto);

}  // namespace pnc_x

#endif
