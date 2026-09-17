/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_MATH_UTILS_UTIL_MATH_H_
#define TAP_SDK_MATH_UTILS_UTIL_MATH_H_
#include "common/basic_types.h"

#include <Eigen/Dense>
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
namespace active_safety {
namespace math {

//=== 基础数学运算 ===//
float SafeDivide(float num, float den);
int   Sign(float val);
float SignF(float val);
float Clamp(float val, float min, float max);
bool  SolveQuadratic(float a, float b, float c, float &root1, float &root2);
//=== 信号处理 ===//
float LowPassFilter(float current, float prev, float gain);
float DeadZone(float input, float full, float threshold);
float MapAngToInterval(float max_angle, float angle);
float RemoveNoise(float input, float thres);
//=== 运动预测 ===//
struct MotionPrediction {
    float position;
    float velocity;
    float acceleration;
};

void PredictMotionWithStop(float pos, float vel, float acc, float time, float &pred_pos,
                           float &pred_vel, float &pred_accel);

float PredictPosition(float pos, float vel, float acc, float time);

//=== 坐标转换 ===//
void CalculateCurveCoords(float curvature, float radius, float longitudinal, float lateral,
                          float *outLongitudinal, float *outLateral);

// 读取指定位的值
template<typename T>
inline bool GetDiagBitValue(const T& value, const uint32_t bit_idx) {
    return (value & (T(1U) << bit_idx)) != 0;
}

} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_UTILS_UTIL_MATH_H_
