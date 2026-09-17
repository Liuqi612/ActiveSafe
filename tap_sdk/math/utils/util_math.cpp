/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#include "util_math.h"
namespace active_safety {
namespace math {
//=== 基础运算实现 ===//
float SafeDivide(float num, float den) {
    if (std::abs(den) < m_eps) {
        // 特殊处理：返回同符号的极大值避免异常
        return num > 0 ? std::numeric_limits<float>::max()
                       : num < 0 ? -std::numeric_limits<float>::max() : 0;
    }
    return num / den;
}

int Sign(float val) {
    return (val > m_eps) ? 1 : ((val < -m_eps) ? -1 : 0);
}

float SignF(float val) {
    return (val > m_eps) ? 1.0F : ((val < -m_eps) ? -1.0F : 0.0F);
}

float Clamp(float val, float min, float max) {
    return (val < min) ? min : ((val > max) ? max : val);
}

bool SolveQuadratic(float a, float b, float c, float &root1, float &root2) {
    // 检查a是否为0（退化为一元一次方程）
    if (std::abs(a) < 1e-10) {
        if (std::abs(b) < 1e-10) {
            return false; // a=0, b=0: 无解
        }
        // 一元一次方程
        root1 = root2 = -c / b;
        return true;
    }

    // 计算判别式
    float discriminant = b * b - 4 * a * c;

    // 判别式小于0，无实数解
    if (discriminant < -1e-10) {
        return false;
    }

    // 避免数值误差
    if (std::abs(discriminant) < 1e-10) {
        discriminant = 0;
    }

    // 计算根
    if (discriminant >= 0) {
        float sqrt_d = std::sqrt(discriminant);
        root1        = (-b - sqrt_d) / (2 * a);
        root2        = (-b + sqrt_d) / (2 * a);
        return true;
    }

    return false;
}
//=== 信号处理实现 ===//
float LowPassFilter(float current, float prev, float gain) {
    gain = Clamp(gain, 0.0F, 1.0F); // 确保增益在合理范围
    return prev + gain * (current - prev);
}

float DeadZone(float input, float full, float threshold) {
    const float absVal = std::abs(input);
    if (absVal <= threshold)
        return 0.0F;
    if (absVal >= full)
        return input;

    // 线性过渡段计算
    const float factor = (absVal - threshold) / (full - threshold);
    return Clamp(factor, 0.0F, 1.0F) * input;
}

float MapAngToInterval(float max_angle, float angle) {
    // for avoid endless loop
    float angle_tmp = angle;
    if (fabsf(angle) > INT_MAX) {
        // error angle
        angle_tmp = 0.00001F;
    }
    if (fabsf(angle) > static_cast<float>(M_PI) * 2.0F) {
        int multiple = static_cast<int>(angle / (static_cast<float>(M_PI) * 2.0F));
        angle_tmp    = angle - multiple * static_cast<float>(M_PI) * 2.0F;
    }

    float mapd_ang = max_angle - angle_tmp;
    if (mapd_ang < 0.0F) {
        while (mapd_ang < 0.0F) {
            mapd_ang = mapd_ang + max_angle * 2.0F;
        }
    } else {
        while (mapd_ang > max_angle * 2.0F) {
            mapd_ang = mapd_ang - max_angle * 2.0F;
        }
    }
    mapd_ang = max_angle - mapd_ang;

    return mapd_ang;
}

float RemoveNoise(float input, float thres) {
    if (fabsf(input) < thres) {
        return 0.0F;
    } else {
        return input;
    }
}

//=== 运动预测实现 ===//
void PredictMotionWithStop(float pos, float vel, float acc, float time, float &pred_pos,
                           float &pred_vel, float &pred_accel) {
    // 计算理论停止时间
    const float stopTime = (acc != 0) ? -vel / acc : time;

    if ((stopTime > 0)  &&  (stopTime < time)) {
        // 会在预测时间内停止
        pred_pos   = pos + vel * stopTime + 0.5F * acc * stopTime * stopTime;
        pred_vel   = 0.0F;
        pred_accel = 0.0F;
    } else {
        // 不会停止
        pred_pos   = pos + vel * time + 0.5F * acc * time * time;
        pred_vel   = vel + acc * time;
        pred_accel = acc;
    }
}

float PredictPosition(float pos, float vel, float acc, float time) {
    return pos + vel * time + 0.5F * acc * time * time;
}

//=== 坐标转换实现 ===//
void CalculateCurveCoords(float curvature, float radius, float longitudinal, float lateral,
                          float *outLongitudinal, float *outLateral) {
    if (!outLongitudinal || !outLateral)
        return;

    if (std::abs(curvature) > 0.001) {
        *outLongitudinal = -radius * std::atan(SafeDivide(longitudinal, lateral - radius));

        *outLateral =
            radius - Clamp(longitudinal / std::sin(*outLongitudinal * curvature), -1e5F, 1e5F);
    } else {
        // 直线特殊情况处理
        *outLongitudinal = longitudinal;
        *outLateral      = lateral;
    }
}
} // namespace math
} // namespace active_safety
