

#include <algorithm>

#include "object/spacetime_object_state.h"
#include "prediction/prediction_util.h"

// SIMD 头文件
#if defined(__AVX512F__)
    #include <immintrin.h>
    #define SIMD_WIDTH_FLOAT 16  // AVX512 一次处理16个float
#elif defined(__AVX2__)
    #include <immintrin.h>
    #define SIMD_WIDTH_FLOAT 8   // AVX2 一次处理8个float
#elif defined(__SSE2__)
    #include <emmintrin.h>
    #define SIMD_WIDTH_FLOAT 4   // SSE2 一次处理4个float
#elif defined(__ARM_NEON__) || defined(__ARM_NEON)
    #include <arm_neon.h>
    #define SIMD_WIDTH_FLOAT 4   // NEON 一次处理4个float
#else
    #define SIMD_WIDTH_FLOAT 1   // 标量版本
#endif

namespace pnc_x {
namespace planning {

// ============= SIMD 辅助函数：批量轮廓点变换 =============

#if defined(__AVX512F__)

inline void simd_transform_contour_points(
    const float* __restrict x_in,
    const float* __restrict y_in,
    float* __restrict x_out,
    float* __restrict y_out,
    int count,
    float cos_rot, float sin_rot,
    float tx, float ty) {
    
    const __m512 cos_v = _mm512_set1_ps(cos_rot);
    const __m512 sin_v = _mm512_set1_ps(sin_rot);
    const __m512 tx_v = _mm512_set1_ps(tx);
    const __m512 ty_v = _mm512_set1_ps(ty);
    
    int i = 0;
    for (; i + 16 <= count; i += 16) {
        __m512 x = _mm512_loadu_ps(x_in + i);
        __m512 y = _mm512_loadu_ps(y_in + i);
        
        __m512 x_out_v = _mm512_fmadd_ps(cos_v, x, _mm512_fnmadd_ps(sin_v, y, tx_v));
        __m512 y_out_v = _mm512_fmadd_ps(sin_v, x, _mm512_fmadd_ps(cos_v, y, ty_v));
        
        _mm512_storeu_ps(x_out + i, x_out_v);
        _mm512_storeu_ps(y_out + i, y_out_v);
    }
    
    for (; i < count; ++i) {
        x_out[i] = cos_rot * x_in[i] - sin_rot * y_in[i] + tx;
        y_out[i] = sin_rot * x_in[i] + cos_rot * y_in[i] + ty;
    }
}

#elif defined(__AVX2__)

inline void simd_transform_contour_points(
    const float* __restrict x_in,
    const float* __restrict y_in,
    float* __restrict x_out,
    float* __restrict y_out,
    int count,
    float cos_rot, float sin_rot,
    float tx, float ty) {
    
    const __m256 cos_v = _mm256_set1_ps(cos_rot);
    const __m256 sin_v = _mm256_set1_ps(sin_rot);
    const __m256 tx_v = _mm256_set1_ps(tx);
    const __m256 ty_v = _mm256_set1_ps(ty);
    
    int i = 0;
    for (; i + 8 <= count; i += 8) {
        __m256 x = _mm256_loadu_ps(x_in + i);
        __m256 y = _mm256_loadu_ps(y_in + i);
        
        __m256 x_out_v = _mm256_fmadd_ps(cos_v, x, _mm256_fnmadd_ps(sin_v, y, tx_v));
        __m256 y_out_v = _mm256_fmadd_ps(sin_v, x, _mm256_fmadd_ps(cos_v, y, ty_v));
        
        _mm256_storeu_ps(x_out + i, x_out_v);
        _mm256_storeu_ps(y_out + i, y_out_v);
    }
    
    for (; i < count; ++i) {
        x_out[i] = cos_rot * x_in[i] - sin_rot * y_in[i] + tx;
        y_out[i] = sin_rot * x_in[i] + cos_rot * y_in[i] + ty;
    }
}

#elif defined(__SSE2__)

inline void simd_transform_contour_points(
    const float* __restrict x_in,
    const float* __restrict y_in,
    float* __restrict x_out,
    float* __restrict y_out,
    int count,
    float cos_rot, float sin_rot,
    float tx, float ty) {
    
    const __m128 cos_v = _mm_set1_ps(cos_rot);
    const __m128 sin_v = _mm_set1_ps(sin_rot);
    const __m128 tx_v = _mm_set1_ps(tx);
    const __m128 ty_v = _mm_set1_ps(ty);
    
    int i = 0;
    for (; (i + 4) <= count; i += 4) {
        __m128 x = _mm_loadu_ps(x_in + i);
        __m128 y = _mm_loadu_ps(y_in + i);
        
        __m128 x_out_v = _mm_add_ps(_mm_mul_ps(cos_v, x), 
                                    _mm_sub_ps(tx_v, _mm_mul_ps(sin_v, y)));
        __m128 y_out_v = _mm_add_ps(_mm_mul_ps(sin_v, x), 
                                    _mm_add_ps(_mm_mul_ps(cos_v, y), ty_v));
        
        _mm_storeu_ps(x_out + i, x_out_v);
        _mm_storeu_ps(y_out + i, y_out_v);
    }
    
    for (; i < count; ++i) {
        x_out[i] = (cos_rot * x_in[i]) - (sin_rot * y_in[i]) + tx;
        y_out[i] = (sin_rot * x_in[i]) + (cos_rot * y_in[i]) + ty;
    }
}

#elif defined(__ARM_NEON__) || defined(__ARM_NEON)

inline void simd_transform_contour_points(
    const float* __restrict x_in,
    const float* __restrict y_in,
    float* __restrict x_out,
    float* __restrict y_out,
    int count,
    float cos_rot, float sin_rot,
    float tx, float ty) {
    
    float32x4_t cos_v = vdupq_n_f32(cos_rot);
    float32x4_t sin_v = vdupq_n_f32(sin_rot);
    float32x4_t tx_v = vdupq_n_f32(tx);
    float32x4_t ty_v = vdupq_n_f32(ty);
    
    int i = 0;
    for (; i + 4 <= count; i += 4) {
        float32x4_t x = vld1q_f32(x_in + i);
        float32x4_t y = vld1q_f32(y_in + i);
        
        float32x4_t x_out_v = vfmaq_f32(tx_v, cos_v, x);
        x_out_v = vfmsq_f32(x_out_v, sin_v, y);
        
        float32x4_t y_out_v = vfmaq_f32(ty_v, sin_v, x);
        y_out_v = vfmaq_f32(y_out_v, cos_v, y);
        
        vst1q_f32(x_out + i, x_out_v);
        vst1q_f32(y_out + i, y_out_v);
    }
    
    for (; i < count; ++i) {
        x_out[i] = (cos_rot * x_in[i]) - (sin_rot * y_in[i]) + tx;
        y_out[i] = (sin_rot * x_in[i]) + (cos_rot * y_in[i]) + ty;
    }
}

#else

// 标量版本
inline void simd_transform_contour_points(
    const float* __restrict x_in,
    const float* __restrict y_in,
    float* __restrict x_out,
    float* __restrict y_out,
    int count,
    float cos_rot, float sin_rot,
    float tx, float ty) {
    
    for (int i = 0; i < count; ++i) {
        x_out[i] = cos_rot * x_in[i] - sin_rot * y_in[i] + tx;
        y_out[i] = sin_rot * x_in[i] + cos_rot * y_in[i] + ty;
    }
}

#endif

void SampleTrajectoryStates(
    const prediction::PredictedTrajectory &pred_traj,
    const Vec2d &init_pos,
    const Polygon2d &init_contour,
    const Box2d &init_box,
    std::vector<SpacetimeObjectState> *states) {
    if (states == nullptr) {
        return;
    }
    const auto &traj_points = pred_traj.points();
    const int num_traj_points = traj_points.size();
    states->resize(num_traj_points);
    if (traj_points.empty()) return;

    if (prediction::IsStationaryTrajectory(pred_traj)) {
        for (int i = 0; i < num_traj_points; ++i) {
            auto &state = (*states)[i];
            state.traj_point = &traj_points[i];
            state.box = init_box;
            state.contour = init_contour;
        }
        return;
    }

    const Vec2d box_pos_shift = init_box.center() - init_pos;

    for (int i = 0; i < num_traj_points; ++i) {
        auto &obj_state = (*states)[i];
        obj_state.traj_point = &traj_points[i];
        const Vec2d &pt_pos = traj_points[i].pos();
        const double pt_theta = traj_points[i].theta();
        const double cos_theta = traj_points[i].cos_theta();
        const double sin_theta = traj_points[i].sin_theta();

        obj_state.box = Box2d(pt_pos + box_pos_shift, pt_theta, cos_theta, sin_theta,
                              init_box.length(), init_box.width());
        obj_state.contour.SetFromBox(obj_state.box);
    }
}

std::vector<SpacetimeObjectState> SampleTrajectoryStates(
    const prediction::PredictedTrajectory &pred_traj,
    const Vec2d &init_pos,
    const Polygon2d &init_contour,
    const Box2d &init_box) {
    std::vector<SpacetimeObjectState> states;
    SampleTrajectoryStates(pred_traj, init_pos, init_contour, init_box,
                           &states);
    return states;
}

}  // namespace planning
}  // namespace pnc_x
