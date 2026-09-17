
#include "math/signalprocess/signal_process/SignalProcess.h"
namespace active_safety {
namespace math {
static constexpr uint32_t kMaxTick{65534U};
static constexpr float    kMinDelayTime{0.0F};
static constexpr float    kMaxDelayTime{1800.0F};
static constexpr float    kMinUnitTime{0.001F};
static constexpr float    kMaxUnitTime{1.0F};

bool SignalProcess::detectRisingEdge(bool current_state) {
    if (!last_state_ && current_state) {
        rising_edge_ = true;
    } else {
        rising_edge_ = false;
    }
    return rising_edge_;
}
//
bool SignalProcess::detectFallingEdge(bool current_state) {
    if (last_state_ && !current_state) {
        falling_edge_ = true;
    } else {
        falling_edge_ = false;
    }
    return falling_edge_;
}
//
void SignalProcess::increaseTime(float unit_time_s) {
    //计数
    if (count_ < kMaxTick) {
        ++count_;
    }
    //转成时间
    cur_delay_time_ = unit_time_s * static_cast<float>(count_);
}
//
void SignalProcess::resetTime() {
    count_          = 0U;
    cur_delay_time_ = 0.0F;
}
//
float SignalProcess::delayTimeLimit(float delay_time) {
    delay_time = std::min(std::max(kMinDelayTime, delay_time), kMaxDelayTime);
    return delay_time;
}
//
float SignalProcess::unitTimeLimit(float unit_time) {
    unit_time = std::min(std::max(kMinUnitTime, unit_time), kMaxUnitTime);
    return unit_time;
}
} // namespace math
} // namespace active_safety
