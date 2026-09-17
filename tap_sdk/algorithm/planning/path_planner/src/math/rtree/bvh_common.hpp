/*
 * Copyright (C) 2026 by SenseTime Group Guanghu planning Team: yunizhou
 * Limited. All rights reserved.
 */

#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <random>
#include <vector>

#if defined(__ARM_NEON__) || defined(__ARM_NEON)
#include <arm_neon.h>
#define BVH_USE_NEON
#define BVH_SIMD_WIDTH 4
#elif defined(__AVX512F__)
#include <immintrin.h>
#define BVH_USE_AVX512
#define BVH_SIMD_WIDTH 16
#elif defined(__AVX2__)
#include <immintrin.h>
#define BVH_USE_AVX2
#define BVH_SIMD_WIDTH 8
#elif defined(__SSE__) || defined(_M_X64) || defined(_M_IX86)
#include <immintrin.h>
#define BVH_USE_SSE
#define BVH_SIMD_WIDTH 4
#endif

#if defined(BVH_USE_NEON) || defined(BVH_USE_SSE) || defined(BVH_USE_AVX2) || \
    defined(BVH_USE_AVX512)
#define BVH_USE_SIMD
#endif

#if defined(BVH_USE_SSE) || defined(BVH_USE_AVX2) || defined(BVH_USE_AVX512)
using float32x4_t = __m128;
using uint32x4_t = __m128;
#endif
#ifdef BVH_USE_AVX2
using float32x8_t = __m256;
using uint32x8_t = __m256;
#endif
#ifdef BVH_USE_AVX512
using float32x8_t = __m256;
using uint32x8_t = __m256;
using float32x16_t = __m512;
using mask16_t = __mmask16;
#endif

namespace senseAD {
namespace planning_pilot {
// ================= Math =================
struct Vec2f {
    float x;
    float y;
};
inline Vec2f operator+(Vec2f a, Vec2f b) { return {a.x + b.x, a.y + b.y}; }
inline Vec2f operator-(Vec2f a, Vec2f b) { return {a.x - b.x, a.y - b.y}; }
inline Vec2f operator*(Vec2f a, float s) { return {a.x * s, a.y * s}; }
inline float dot(Vec2f a, Vec2f b) { return (a.x * b.x) + (a.y * b.y); }
inline float norm2(Vec2f a) { return dot(a, a); }

// ================= Geometry =================
struct Segment {
    Vec2f a;
    Vec2f b;
};

inline float dist2_point_segment(const Vec2f& p, const Segment& s) {
    Vec2f ab = s.b - s.a;
    Vec2f ap = p - s.a;
    float denom = norm2(ab) + 1e-12F;
    float t = dot(ap, ab) / denom;
    t = std::min(1.F, std::max(0.F, t));
    Vec2f q = s.a + ab * t;
    return norm2(p - q);
}

#ifdef BVH_USE_SIMD
#ifdef BVH_USE_AVX512
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out);
#elif defined(BVH_USE_AVX2)
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out);
#else
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out);
#endif
#endif

// ================= Polyline =================
struct Polyline {
    std::vector<Segment> segs;
    Vec2f min;
    Vec2f max;
};

inline Polyline make_polyline(const std::vector<Vec2f>& pts) {
    Polyline pl;
    pl.min = pl.max = pts[0UL];
    for (size_t i = 1UL; i < pts.size(); i++) {
        pl.segs.push_back({pts[i - 1UL], pts[i]});
        pl.min.x = std::min(pl.min.x, pts[i].x);
        pl.min.y = std::min(pl.min.y, pts[i].y);
        pl.max.x = std::max(pl.max.x, pts[i].x);
        pl.max.y = std::max(pl.max.y, pts[i].y);
    }
    return pl;
}

inline float dist2_point_aabb(const Vec2f& p,
                              const Vec2f& mi,
                              const Vec2f& ma) {
    float dx = std::max(std::max(mi.x - p.x, 0.0F), p.x - ma.x);
    float dy = std::max(std::max(mi.y - p.y, 0.0F), p.y - ma.y);
    return (dx * dx) + (dy * dy);
}

inline float dist2_point_aabb_xy(
    const Vec2f& p, float minx, float miny, float maxx, float maxy) {
    float dx = std::max(std::max(minx - p.x, 0.0F), p.x - maxx);
    float dy = std::max(std::max(miny - p.y, 0.0F), p.y - maxy);
    return (dx * dx) + (dy * dy);
}

// ================= Query =================
struct QueryCache {
    int poly_id = -1;
    int seg_id = -1;
};

struct SegSOA {
    std::vector<float> ax;
    std::vector<float> ay;
    std::vector<float> abx;
    std::vector<float> aby;
    std::vector<int> poly_idx;
    std::vector<int> seg_idx;
};

inline float dist2_point_segment_soa_scalar(const Vec2f& p,
                                            const SegSOA& s,
                                            int i) {
    float apx = p.x - s.ax[static_cast<unsigned long>(i)];
    float apy = p.y - s.ay[static_cast<unsigned long>(i)];
    float abx = s.abx[static_cast<unsigned long>(i)];
    float aby = s.aby[static_cast<unsigned long>(i)];
    float denom = ((abx * abx) + (aby * aby)) + 1e-12F;
    float t = ((apx * abx) + (apy * aby)) / denom;
    if (t < 0.F) {
        t = 0.F;
    } else if (t > 1.F) {
        t = 1.F;
    }
    float dx = apx - (abx * t);
    float dy = apy - (aby * t);
    return (dx * dx) + (dy * dy);
}

inline void dist2_point_segment_simd_soa_4(const Vec2f& p,
                                           const SegSOA& s,
                                           int start,
                                           float out[4]);

#ifdef BVH_USE_SIMD
inline void dist2_point_segment_simd_soa_8(const Vec2f& p,
                                           const SegSOA& s,
                                           int start,
                                           float out[8]);
#endif

// ================= Chunk BVH =================
struct Chunk {
    int global_start;
    int count;
    Vec2f min;
    Vec2f max;
    int poly_idx;
    int seg_idx;
};

// ================= Debug Statistics =================
struct QueryStats {
    long long chunks_visited = 0;
    long long nodes_visited = 0;
    long long aabb_evals = 0;
    long long simd_leaves = 0;
};

struct PolyBVH {
    // SoA node storage
    std::vector<float> minx;
    std::vector<float> miny;
    std::vector<float> maxx;
    std::vector<float> maxy;
    std::vector<int> left;
    std::vector<int> right;
    std::vector<int> chunk_idx;

    std::vector<int> indices;
    std::vector<Chunk> chunks;
    SegSOA soa;

    mutable QueryStats last_stats;

    inline int new_node(float mi_x,
                        float mi_y,
                        float ma_x,
                        float ma_y,
                        int l = -1,
                        int r = -1,
                        int c = -1) {
        minx.push_back(mi_x);
        miny.push_back(mi_y);
        maxx.push_back(ma_x);
        maxy.push_back(ma_y);
        left.push_back(l);
        right.push_back(r);
        chunk_idx.push_back(c);
        return static_cast<int>(chunk_idx.size()) - 1;
    }

    int build_recursive(int left, int right);
    void build(const std::vector<Segment>& all_segments,
               const std::vector<Polyline>& polys);
    void build(const std::vector<Segment>& segments);
    QueryStats get_debug_info() const { return last_stats; }
    bool query_iter(const Vec2f& p,
                    float& best_dist,
                    int& best_poly,
                    int& best_seg,
                    int& best_global) const;
    void query_iter_internal(const Vec2f& p,
                             float& best_dist,
                             int& best_poly,
                             int& best_seg,
                             int& best_global,
                             long long& stats_chunks,
                             long long& stats_nodes,
                             long long& stats_aabb,
                             long long& stats_simd_leaves) const;

#ifdef BVH_USE_SIMD
    static inline float hmin_f32x4(float32x4_t v);
    static inline bool any_u32x4(uint32x4_t m);
    inline float32x4_t dist2_point_aabb_xy_4(float32x4_t px,
                                             float32x4_t py,
                                             float mi_x,
                                             float mi_y,
                                             float ma_x,
                                             float ma_y) const;

#ifdef BVH_USE_AVX2
    static inline float hmin_f32x8(float32x8_t v);
    static inline bool any_u32x8(uint32x8_t m);
    inline float32x8_t dist2_point_aabb_xy_8(float32x8_t px,
                                             float32x8_t py,
                                             float mi_x,
                                             float mi_y,
                                             float ma_x,
                                             float ma_y) const;
#endif

#ifdef BVH_USE_AVX512
    static inline float hmin_f32x16(float32x16_t v);
    static inline bool any_mask16(mask16_t m);
    inline float32x16_t dist2_point_aabb_xy_16(float32x16_t px,
                                               float32x16_t py,
                                               float mi_x,
                                               float mi_y,
                                               float ma_x,
                                               float ma_y) const;
#endif

    inline void query_packet4(const Vec2f p4[4],
                              const SegSOA& soa,
                              int best_global[4],
                              int best_poly[4],
                              int best_seg[4],
                              float best_dist2[4],
                              long long& stats_chunks,
                              long long& stats_nodes,
                              long long& stats_aabb,
                              long long& stats_simd_leaves) const;

#ifdef BVH_USE_AVX2
    inline void query_packet8(const Vec2f p8[8],
                              const SegSOA& soa,
                              int best_global[8],
                              int best_poly[8],
                              int best_seg[8],
                              float best_dist2[8],
                              long long& stats_chunks,
                              long long& stats_nodes,
                              long long& stats_aabb,
                              long long& stats_simd_leaves) const;
#endif

#ifdef BVH_USE_AVX512
    inline void query_packet16(const Vec2f p16[16],
                               const SegSOA& soa,
                               int best_global[16],
                               int best_poly[16],
                               int best_seg[16],
                               float best_dist2[16],
                               long long& stats_chunks,
                               long long& stats_nodes,
                               long long& stats_aabb,
                               long long& stats_simd_leaves) const;
#endif
#endif

    void query_batch_impl(const Vec2f* queries,
                          int query_count,
                          float* out_best_dist2,
                          int* out_best_poly,
                          int* out_best_seg,
                          int* out_best_global,
                          const int* seed_best_global,
                          long long* stats_chunks,
                          long long* stats_nodes,
                          long long* stats_aabb,
                          long long* stats_simd4_leaves,
                          bool force_scalar) const;

    void query_batch(const Vec2f* queries,
                     int query_count,
                     float* out_best_dist2 = nullptr,
                     int* out_best_poly = nullptr,
                     int* out_best_seg = nullptr,
                     int* out_best_global = nullptr,
                     const int* seed_best_global = nullptr,
                     bool force_scalar = false) const;
};

// ================= Benchmark =================
struct GlobalCache {
    int poly_idx = -1;
    int seg_idx = -1;
    int global_idx = -1;
};

}  // namespace planning_pilot
}  // namespace senseAD
