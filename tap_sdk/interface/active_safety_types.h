/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */
#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>
namespace active_safety {

typedef struct {
    uint32_t id;
    uint32_t type;
    uint32_t source;
    float posx;
    float posy;
    float spdx;
    float spdy;
    float accelx;
    float accely;
    float heading;
    float ttc;
} AsTargetInfo_T;

typedef struct {
    std::string topic;
    uint64_t timestamp_ns;
} ReplayEntry;

typedef struct {
    std::vector<ReplayEntry> inputs;
    std::vector<ReplayEntry> outputs;
    void reset() {
        inputs.clear();
        outputs.clear();
    }
    void add_input(std::string topic, uint64_t timestamp_ns) { inputs.emplace_back(ReplayEntry{topic, timestamp_ns}); }
    void add_output(std::string topic, uint64_t timestamp_ns) { outputs.emplace_back(ReplayEntry{topic, timestamp_ns}); }
} ReplayFrame;

} // namespace active_safety