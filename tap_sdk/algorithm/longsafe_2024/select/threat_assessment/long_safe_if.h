/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include "single_threat_assessor.h"

#include <cstddef>
#include <cstdint>
namespace senseAD {
namespace tap {

struct AsLgSafeTgt {
    PrimaryTarget prm_tgt;
};

struct As_LongSafeOut_T {
    AsLgSafeTgt longsafe_aeb;
    AsLgSafeTgt longsafe_fcw;
    uint8_t     longsafe_roll_cnt;
    uint8_t     longsafe_major_version;
    uint8_t     longsafe_minor_version;
    uint8_t     uint8_reserve1;
    uint8_t     uint8_reserve2;
    uint8_t     uint8_reserve3;
};

} // namespace tap
} // namespace senseAD