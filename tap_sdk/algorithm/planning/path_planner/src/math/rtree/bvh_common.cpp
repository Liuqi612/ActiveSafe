#include "bvh_common.hpp"

namespace senseAD {
namespace planning_pilot {

#ifdef BVH_USE_SIMD
#ifdef BVH_USE_AVX512
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out) {
    int i = 0;
    float32x16_t px = _mm512_set1_ps(p.x);
    float32x16_t py = _mm512_set1_ps(p.y);

    for (; (i + 15) < count; i += 16) {
        float ax[16], ay[16], bx[16], by[16];
        for (int k = 0; k < 16; k++) {
            ax[k] = segs[i + k].a.x;
            ay[k] = segs[i + k].a.y;
            bx[k] = segs[i + k].b.x;
            by[k] = segs[i + k].b.y;
        }

        float32x16_t axv = _mm512_loadu_ps(ax);
        float32x16_t ayv = _mm512_loadu_ps(ay);
        float32x16_t bxv = _mm512_loadu_ps(bx);
        float32x16_t byv = _mm512_loadu_ps(by);

        float32x16_t abx = _mm512_sub_ps(bxv, axv);
        float32x16_t aby = _mm512_sub_ps(byv, ayv);
        float32x16_t apx = _mm512_sub_ps(px, axv);
        float32x16_t apy = _mm512_sub_ps(py, ayv);

        float32x16_t num = _mm512_fmadd_ps(apx, abx, _mm512_mul_ps(apy, aby));
        float32x16_t den = _mm512_fmadd_ps(abx, abx, _mm512_mul_ps(aby, aby));
        den = _mm512_add_ps(den, _mm512_set1_ps(1e-12F));
        float32x16_t t = _mm512_div_ps(num, den);
        t = _mm512_max_ps(_mm512_set1_ps(0.F),
                          _mm512_min_ps(_mm512_set1_ps(1.F), t));

        float32x16_t qx = _mm512_fmadd_ps(abx, t, axv);
        float32x16_t qy = _mm512_fmadd_ps(aby, t, ayv);
        float32x16_t dx = _mm512_sub_ps(px, qx);
        float32x16_t dy = _mm512_sub_ps(py, qy);
        float32x16_t d2 = _mm512_fmadd_ps(dx, dx, _mm512_mul_ps(dy, dy));
        _mm512_storeu_ps(out + i, d2);
    }

    // Fall back to AVX2 for remaining elements
    if ((i + 7) < count) {
        float32x8_t px8 = _mm256_set1_ps(p.x);
        float32x8_t py8 = _mm256_set1_ps(p.y);

        for (; (i + 7) < count; i += 8) {
            float ax[8], ay[8], bx[8], by[8];
            for (int k = 0; k < 8; k++) {
                ax[k] = segs[i + k].a.x;
                ay[k] = segs[i + k].a.y;
                bx[k] = segs[i + k].b.x;
                by[k] = segs[i + k].b.y;
            }

            float32x8_t axv = _mm256_loadu_ps(ax);
            float32x8_t ayv = _mm256_loadu_ps(ay);
            float32x8_t bxv = _mm256_loadu_ps(bx);
            float32x8_t byv = _mm256_loadu_ps(by);

            float32x8_t abx = _mm256_sub_ps(bxv, axv);
            float32x8_t aby = _mm256_sub_ps(byv, ayv);
            float32x8_t apx = _mm256_sub_ps(px8, axv);
            float32x8_t apy = _mm256_sub_ps(py8, ayv);

            float32x8_t num =
                _mm256_fmadd_ps(apx, abx, _mm256_mul_ps(apy, aby));
            float32x8_t den =
                _mm256_fmadd_ps(abx, abx, _mm256_mul_ps(aby, aby));
            den = _mm256_add_ps(den, _mm256_set1_ps(1e-12F));
            float32x8_t t = _mm256_div_ps(num, den);
            t = _mm256_max_ps(_mm256_set1_ps(0.F),
                              _mm256_min_ps(_mm256_set1_ps(1.F), t));

            float32x8_t qx = _mm256_fmadd_ps(abx, t, axv);
            float32x8_t qy = _mm256_fmadd_ps(aby, t, ayv);
            float32x8_t dx = _mm256_sub_ps(px8, qx);
            float32x8_t dy = _mm256_sub_ps(py8, qy);
            float32x8_t d2 = _mm256_fmadd_ps(dx, dx, _mm256_mul_ps(dy, dy));
            _mm256_storeu_ps(out + i, d2);
        }
    }

    // Fall back to SSE for remaining elements
    if ((i + 3) < count) {
        float32x4_t px4 = _mm_set1_ps(p.x);
        float32x4_t py4 = _mm_set1_ps(p.y);

        for (; (i + 3) < count; i += 4) {
            float ax[4], ay[4], bx[4], by[4];
            for (int k = 0; k < 4; k++) {
                ax[k] = segs[i + k].a.x;
                ay[k] = segs[i + k].a.y;
                bx[k] = segs[i + k].b.x;
                by[k] = segs[i + k].b.y;
            }

            float32x4_t axv = _mm_loadu_ps(ax);
            float32x4_t ayv = _mm_loadu_ps(ay);
            float32x4_t bxv = _mm_loadu_ps(bx);
            float32x4_t byv = _mm_loadu_ps(by);

            float32x4_t abx = _mm_sub_ps(bxv, axv);
            float32x4_t aby = _mm_sub_ps(byv, ayv);
            float32x4_t apx = _mm_sub_ps(px4, axv);
            float32x4_t apy = _mm_sub_ps(py4, ayv);

            float32x4_t num =
                _mm_add_ps(_mm_mul_ps(apx, abx), _mm_mul_ps(apy, aby));
            float32x4_t den =
                _mm_add_ps(_mm_mul_ps(abx, abx), _mm_mul_ps(aby, aby));
            den = _mm_add_ps(den, _mm_set1_ps(1e-12F));
            float32x4_t t = _mm_div_ps(num, den);
            t = _mm_max_ps(_mm_set1_ps(0.F), _mm_min_ps(_mm_set1_ps(1.F), t));

            float32x4_t qx = _mm_add_ps(axv, _mm_mul_ps(abx, t));
            float32x4_t qy = _mm_add_ps(ayv, _mm_mul_ps(aby, t));
            float32x4_t dx = _mm_sub_ps(px4, qx);
            float32x4_t dy = _mm_sub_ps(py4, qy);
            float32x4_t d2 = _mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy));
            _mm_storeu_ps(out + i, d2);
        }
    }

    for (; i < count; i++) out[i] = dist2_point_segment(p, segs[i]);
}
#elif defined(BVH_USE_AVX2)
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out) {
    int i = 0;
    float32x8_t px = _mm256_set1_ps(p.x);
    float32x8_t py = _mm256_set1_ps(p.y);

    for (; i + 7 < count; i += 8) {
        float ax[8], ay[8], bx[8], by[8];
        for (int k = 0; k < 8; k++) {
            ax[k] = segs[i + k].a.x;
            ay[k] = segs[i + k].a.y;
            bx[k] = segs[i + k].b.x;
            by[k] = segs[i + k].b.y;
        }

        float32x8_t axv = _mm256_loadu_ps(ax);
        float32x8_t ayv = _mm256_loadu_ps(ay);
        float32x8_t bxv = _mm256_loadu_ps(bx);
        float32x8_t byv = _mm256_loadu_ps(by);

        float32x8_t abx = _mm256_sub_ps(bxv, axv);
        float32x8_t aby = _mm256_sub_ps(byv, ayv);
        float32x8_t apx = _mm256_sub_ps(px, axv);
        float32x8_t apy = _mm256_sub_ps(py, ayv);

        float32x8_t num = _mm256_fmadd_ps(apx, abx, _mm256_mul_ps(apy, aby));
        float32x8_t den = _mm256_fmadd_ps(abx, abx, _mm256_mul_ps(aby, aby));
        den = _mm256_add_ps(den, _mm256_set1_ps(1e-12F));
        float32x8_t t = _mm256_div_ps(num, den);
        t = _mm256_max_ps(_mm256_set1_ps(0.F),
                          _mm256_min_ps(_mm256_set1_ps(1.F), t));

        float32x8_t qx = _mm256_fmadd_ps(abx, t, axv);
        float32x8_t qy = _mm256_fmadd_ps(aby, t, ayv);
        float32x8_t dx = _mm256_sub_ps(px, qx);
        float32x8_t dy = _mm256_sub_ps(py, qy);
        float32x8_t d2 = _mm256_fmadd_ps(dx, dx, _mm256_mul_ps(dy, dy));
        _mm256_storeu_ps(out + i, d2);
    }

    // Fall back to SSE for remaining elements
    if ((i + 3) < count) {
        float32x4_t px4 = _mm_set1_ps(p.x);
        float32x4_t py4 = _mm_set1_ps(p.y);

        for (; (i + 3) < count; i += 4) {
            float ax[4], ay[4], bx[4], by[4];
            for (int k = 0; k < 4; k++) {
                ax[k] = segs[i + k].a.x;
                ay[k] = segs[i + k].a.y;
                bx[k] = segs[i + k].b.x;
                by[k] = segs[i + k].b.y;
            }

            float32x4_t axv = _mm_loadu_ps(ax);
            float32x4_t ayv = _mm_loadu_ps(ay);
            float32x4_t bxv = _mm_loadu_ps(bx);
            float32x4_t byv = _mm_loadu_ps(by);

            float32x4_t abx = _mm_sub_ps(bxv, axv);
            float32x4_t aby = _mm_sub_ps(byv, ayv);
            float32x4_t apx = _mm_sub_ps(px4, axv);
            float32x4_t apy = _mm_sub_ps(py4, ayv);

            float32x4_t num =
                _mm_add_ps(_mm_mul_ps(apx, abx), _mm_mul_ps(apy, aby));
            float32x4_t den =
                _mm_add_ps(_mm_mul_ps(abx, abx), _mm_mul_ps(aby, aby));
            den = _mm_add_ps(den, _mm_set1_ps(1e-12F));
            float32x4_t t = _mm_div_ps(num, den);
            t = _mm_max_ps(_mm_set1_ps(0.F), _mm_min_ps(_mm_set1_ps(1.F), t));

            float32x4_t qx = _mm_add_ps(axv, _mm_mul_ps(abx, t));
            float32x4_t qy = _mm_add_ps(ayv, _mm_mul_ps(aby, t));
            float32x4_t dx = _mm_sub_ps(px4, qx);
            float32x4_t dy = _mm_sub_ps(py4, qy);
            float32x4_t d2 = _mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy));
            _mm_storeu_ps(out + i, d2);
        }
    }

    for (; i < count; i++) out[i] = dist2_point_segment(p, segs[i]);
}
#else
inline void dist2_point_segment_simd(const Vec2f& p,
                                     const Segment* segs,
                                     int count,
                                     float* out) {
    int i = 0;
#ifdef BVH_USE_NEON
    float32x4_t px = vdupq_n_f32(p.x);
    float32x4_t py = vdupq_n_f32(p.y);
#else
    float32x4_t px = _mm_set1_ps(p.x);
    float32x4_t py = _mm_set1_ps(p.y);
#endif
    for (; i + 3 < count; i += 4) {
        float ax[4], ay[4], bx[4], by[4];
        for (int k = 0; k < 4; k++) {
            ax[k] = segs[i + k].a.x;
            ay[k] = segs[i + k].a.y;
            bx[k] = segs[i + k].b.x;
            by[k] = segs[i + k].b.y;
        }
#ifdef BVH_USE_NEON
        float32x4_t axv = vld1q_f32(ax);
        float32x4_t ayv = vld1q_f32(ay);
        float32x4_t bxv = vld1q_f32(bx);
        float32x4_t byv = vld1q_f32(by);

        float32x4_t abx = vsubq_f32(bxv, axv);
        float32x4_t aby = vsubq_f32(byv, ayv);
        float32x4_t apx = vsubq_f32(px, axv);
        float32x4_t apy = vsubq_f32(py, ayv);

        float32x4_t num = vmlaq_f32(vmulq_f32(apx, abx), apy, aby);
        float32x4_t den = vmlaq_f32(vmulq_f32(abx, abx), aby, aby);
        den = vaddq_f32(den, vdupq_n_f32(1e-12F));
        float32x4_t t = vdivq_f32(num, den);
        t = vmaxq_f32(vdupq_n_f32(0.F), vminq_f32(vdupq_n_f32(1.F), t));

        float32x4_t qx = vmlaq_f32(axv, abx, t);
        float32x4_t qy = vmlaq_f32(ayv, aby, t);
        float32x4_t dx = vsubq_f32(px, qx);
        float32x4_t dy = vsubq_f32(py, qy);
        float32x4_t d2 = vmlaq_f32(vmulq_f32(dx, dx), dy, dy);
        vst1q_f32(out + i, d2);
#else
        float32x4_t axv = _mm_loadu_ps(ax);
        float32x4_t ayv = _mm_loadu_ps(ay);
        float32x4_t bxv = _mm_loadu_ps(bx);
        float32x4_t byv = _mm_loadu_ps(by);

        float32x4_t abx = _mm_sub_ps(bxv, axv);
        float32x4_t aby = _mm_sub_ps(byv, ayv);
        float32x4_t apx = _mm_sub_ps(px, axv);
        float32x4_t apy = _mm_sub_ps(py, ayv);

        float32x4_t num =
            _mm_add_ps(_mm_mul_ps(apx, abx), _mm_mul_ps(apy, aby));
        float32x4_t den =
            _mm_add_ps(_mm_mul_ps(abx, abx), _mm_mul_ps(aby, aby));
        den = _mm_add_ps(den, _mm_set1_ps(1e-12F));
        float32x4_t t = _mm_div_ps(num, den);
        t = _mm_max_ps(_mm_set1_ps(0.F), _mm_min_ps(_mm_set1_ps(1.F), t));

        float32x4_t qx = _mm_add_ps(axv, _mm_mul_ps(abx, t));
        float32x4_t qy = _mm_add_ps(ayv, _mm_mul_ps(aby, t));
        float32x4_t dx = _mm_sub_ps(px, qx);
        float32x4_t dy = _mm_sub_ps(py, qy);
        float32x4_t d2 = _mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy));
        _mm_storeu_ps(out + i, d2);
#endif
    }
    for (; i < count; i++) out[i] = dist2_point_segment(p, segs[i]);
}
#endif
#endif

inline void dist2_point_segment_simd_soa_4(const Vec2f& p,
                                           const SegSOA& s,
                                           int start,
                                           float out[4]) {
#ifdef BVH_USE_NEON
    float32x4_t px = vdupq_n_f32(p.x);
    float32x4_t py = vdupq_n_f32(p.y);

    float32x4_t axv = vld1q_f32(&s.ax[start]);
    float32x4_t ayv = vld1q_f32(&s.ay[start]);
    float32x4_t abx = vld1q_f32(&s.abx[start]);
    float32x4_t aby = vld1q_f32(&s.aby[start]);
    float32x4_t apx = vsubq_f32(px, axv);
    float32x4_t apy = vsubq_f32(py, ayv);

    float32x4_t num = vmlaq_f32(vmulq_f32(apx, abx), apy, aby);
    float32x4_t den = vmlaq_f32(vmulq_f32(abx, abx), aby, aby);
    den = vaddq_f32(den, vdupq_n_f32(1e-12F));
#if defined(BVH_APPROX_DIV)
    // Faster than vdiv on many ARM cores; may change last-bit results.
    float32x4_t inv = vrecpeq_f32(den);
    inv = vmulq_f32(inv, vrecpsq_f32(den, inv));
    inv = vmulq_f32(inv, vrecpsq_f32(den, inv));
    float32x4_t t = vmulq_f32(num, inv);
#else
    float32x4_t t = vdivq_f32(num, den);
#endif
    t = vmaxq_f32(vdupq_n_f32(0.F), vminq_f32(vdupq_n_f32(1.F), t));

    float32x4_t dx = vmlsq_f32(apx, abx, t);  // ap - ab*t
    float32x4_t dy = vmlsq_f32(apy, aby, t);
    float32x4_t d2 = vmlaq_f32(vmulq_f32(dx, dx), dy, dy);
    vst1q_f32(out, d2);
#else
    float32x4_t px = _mm_set1_ps(p.x);
    float32x4_t py = _mm_set1_ps(p.y);

    float32x4_t axv = _mm_loadu_ps(&s.ax[static_cast<size_t>(start)]);
    float32x4_t ayv = _mm_loadu_ps(&s.ay[static_cast<size_t>(start)]);
    float32x4_t abx = _mm_loadu_ps(&s.abx[static_cast<size_t>(start)]);
    float32x4_t aby = _mm_loadu_ps(&s.aby[static_cast<size_t>(start)]);
    float32x4_t apx = _mm_sub_ps(px, axv);
    float32x4_t apy = _mm_sub_ps(py, ayv);

    float32x4_t num = _mm_add_ps(_mm_mul_ps(apx, abx), _mm_mul_ps(apy, aby));
    float32x4_t den = _mm_add_ps(_mm_mul_ps(abx, abx), _mm_mul_ps(aby, aby));
    den = _mm_add_ps(den, _mm_set1_ps(1e-12F));

    float32x4_t t = _mm_div_ps(num, den);
    t = _mm_max_ps(_mm_set1_ps(0.F), _mm_min_ps(_mm_set1_ps(1.F), t));

    float32x4_t dx = _mm_sub_ps(apx, _mm_mul_ps(abx, t));
    float32x4_t dy = _mm_sub_ps(apy, _mm_mul_ps(aby, t));
    float32x4_t d2 = _mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy));
    _mm_storeu_ps(out, d2);
#endif
}

#ifdef BVH_USE_SIMD
inline void dist2_point_segment_simd_soa_8(const Vec2f& p,
                                           const SegSOA& s,
                                           int start,
                                           float out[8]) {
#ifdef BVH_USE_AVX2
    float32x8_t px = _mm256_set1_ps(p.x);
    float32x8_t py = _mm256_set1_ps(p.y);

    float32x8_t axv = _mm256_loadu_ps(&s.ax[static_cast<size_t>(start)]);
    float32x8_t ayv = _mm256_loadu_ps(&s.ay[static_cast<size_t>(start)]);
    float32x8_t abx = _mm256_loadu_ps(&s.abx[static_cast<size_t>(start)]);
    float32x8_t aby = _mm256_loadu_ps(&s.aby[static_cast<size_t>(start)]);
    float32x8_t apx = _mm256_sub_ps(px, axv);
    float32x8_t apy = _mm256_sub_ps(py, ayv);

    float32x8_t num = _mm256_fmadd_ps(apx, abx, _mm256_mul_ps(apy, aby));
    float32x8_t den = _mm256_fmadd_ps(abx, abx, _mm256_mul_ps(aby, aby));
    den = _mm256_add_ps(den, _mm256_set1_ps(1e-12F));
    float32x8_t t = _mm256_div_ps(num, den);
    t = _mm256_max_ps(_mm256_set1_ps(0.F),
                      _mm256_min_ps(_mm256_set1_ps(1.F), t));

    float32x8_t dx =
        _mm256_fmsub_ps(abx, t, apx);  // -(apx - abx*t) = abx*t - apx
    dx = _mm256_sub_ps(apx, _mm256_mul_ps(abx, t));  // correct: apx - abx*t
    float32x8_t dy = _mm256_sub_ps(apy, _mm256_mul_ps(aby, t));
    float32x8_t d2 = _mm256_fmadd_ps(dx, dx, _mm256_mul_ps(dy, dy));
    _mm256_storeu_ps(out, d2);
#else
    // Fall back to 4-wide for each pair
    dist2_point_segment_simd_soa_4(p, s, start, out);
    dist2_point_segment_simd_soa_4(p, s, start + 4, out + 4);
#endif
}
#endif

// ================= Poly BVH =================

int PolyBVH::build_recursive(int left, int right) {
    float mi_x = 1e30F;
    float mi_y = 1e30F;
    float ma_x = -1e30F;
    float ma_y = -1e30F;
    for (int i = left; i < right; ++i) {
        int chunk_i = indices[static_cast<size_t>(i)];
        const auto& c = chunks[static_cast<size_t>(chunk_i)];
        mi_x = std::min(mi_x, c.min.x);
        mi_y = std::min(mi_y, c.min.y);
        ma_x = std::max(ma_x, c.max.x);
        ma_y = std::max(ma_y, c.max.y);
    }

    int count = right - left;
    if (count == 1) {
        int idx_left = indices[static_cast<size_t>(left)];
        return new_node(mi_x, mi_y, ma_x, ma_y, -1, -1, idx_left);
    }

    float ex = ma_x - mi_x;
    float ey = ma_y - mi_y;
    int axis = (ex > ey) ? 0 : 1;
    int mid = (left + right) / 2;

    std::nth_element(indices.begin() + left, indices.begin() + mid,
                     indices.begin() + right, [&](int a, int b) {
                         const auto& ca = chunks[a];
                         const auto& cb = chunks[b];
                         float val_a = (axis == 0) ? (ca.min.x + ca.max.x)
                                                   : (ca.min.y + ca.max.y);
                         float val_b = (axis == 0) ? (cb.min.x + cb.max.x)
                                                   : (cb.min.y + cb.max.y);
                         return val_a < val_b;
                     });

    int curr_idx = new_node(mi_x, mi_y, ma_x, ma_y);

    int l_idx = build_recursive(left, mid);
    int r_idx = build_recursive(mid, right);

    this->left[static_cast<size_t>(curr_idx)] = l_idx;
    this->right[static_cast<size_t>(curr_idx)] = r_idx;
    return curr_idx;
}

// Build from polylines
void PolyBVH::build(const std::vector<Segment>& all_segments,
                    const std::vector<Polyline>& polys) {
    // Build SegSOA
    soa.ax.clear();
    soa.ay.clear();
    soa.abx.clear();
    soa.aby.clear();
    soa.poly_idx.clear();
    soa.seg_idx.clear();

    soa.ax.resize(all_segments.size());
    soa.ay.resize(all_segments.size());
    soa.abx.resize(all_segments.size());
    soa.aby.resize(all_segments.size());
    soa.poly_idx.resize(all_segments.size());
    soa.seg_idx.resize(all_segments.size());

    int cur_poly = 0;
    int cur_seg = 0;
    size_t next_poly_start = 0;

    // Find first non-empty polyline
    while (cur_poly < (int)polys.size() &&
           polys[static_cast<size_t>(cur_poly)].segs.size() == 0) {
        cur_poly++;
    }
    if (cur_poly < (int)polys.size()) {
        for (int i = 0; i < cur_poly; ++i) {
            next_poly_start += polys[static_cast<size_t>(i)].segs.size();
        }
        next_poly_start += polys[static_cast<size_t>(cur_poly)].segs.size();
    }

    cur_poly = 0;
    cur_seg = 0;

    for (size_t i = 0; i < all_segments.size(); ++i) {
        if (i == next_poly_start && cur_poly < (int)polys.size() - 1) {
            cur_poly++;
            cur_seg = 0;
            while (cur_poly < (int)polys.size() &&
                   polys[static_cast<size_t>(cur_poly)].segs.size() == 0) {
                cur_poly++;
            }
            if (cur_poly < (int)polys.size()) {
                next_poly_start += polys[static_cast<size_t>(cur_poly)].segs.size();
            }
        }
        float ax = all_segments[i].a.x;
        float ay = all_segments[i].a.y;
        float abx = all_segments[i].b.x - ax;
        float aby = all_segments[i].b.y - ay;
        soa.ax[i] = ax;
        soa.ay[i] = ay;
        soa.abx[i] = abx;
        soa.aby[i] = aby;
        soa.poly_idx[i] = cur_poly;
        soa.seg_idx[i] = cur_seg++;
    }

    // Build Chunks
    chunks.clear();
    int CHUNK_SIZE = 4;  // SSE/NEON is 4-wide
    int global_offset = 0;
    for (int i = 0; i < (int)polys.size(); ++i) {
        const auto& p = polys[static_cast<size_t>(i)];
        int n = (int)p.segs.size();
        if (n == 0) continue;

        for (int j = 0; j < n; j += CHUNK_SIZE) {
            Chunk c;
            c.poly_idx = i;
            c.seg_idx = j;
            c.global_start = global_offset + j;
            c.count = std::min(CHUNK_SIZE, n - j);
            c.min = {1e30F, 1e30F};
            c.max = {-1e30F, -1e30F};
            for (int k = 0; k < c.count; ++k) {
                int seg_idx_k = c.global_start + k;
                const auto& s = all_segments[static_cast<size_t>(seg_idx_k)];
                c.min.x = std::min({c.min.x, s.a.x, s.b.x});
                c.min.y = std::min({c.min.y, s.a.y, s.b.y});
                c.max.x = std::max({c.max.x, s.a.x, s.b.x});
                c.max.y = std::max({c.max.y, s.a.y, s.b.y});
            }
            chunks.push_back(c);
        }
        global_offset += n;
    }

    // Build tree
    indices.resize(chunks.size());
    std::iota(indices.begin(), indices.end(), 0);
    int reserve_n = (int)chunks.size() * 2;
    minx.clear();
    minx.reserve(static_cast<size_t>(reserve_n));
    miny.clear();
    miny.reserve(static_cast<size_t>(reserve_n));
    maxx.clear();
    maxx.reserve(static_cast<size_t>(reserve_n));
    maxy.clear();
    maxy.reserve(static_cast<size_t>(reserve_n));
    left.clear();
    left.reserve(static_cast<size_t>(reserve_n));
    right.clear();
    right.reserve(static_cast<size_t>(reserve_n));
    chunk_idx.clear();
    chunk_idx.reserve(static_cast<size_t>(reserve_n));

    build_recursive(0, (int)indices.size());
}

// Build from segments directly (all segments treated as polyline 0)
void PolyBVH::build(const std::vector<Segment>& segments) {
    // Build SegSOA from segments
    soa.ax.clear();
    soa.ay.clear();
    soa.abx.clear();
    soa.aby.clear();
    soa.poly_idx.clear();
    soa.seg_idx.clear();

    soa.ax.resize(segments.size());
    soa.ay.resize(segments.size());
    soa.abx.resize(segments.size());
    soa.aby.resize(segments.size());
    soa.poly_idx.resize(segments.size());
    soa.seg_idx.resize(segments.size());

    for (size_t i = 0; i < segments.size(); ++i) {
        float ax = segments[i].a.x;
        float ay = segments[i].a.y;
        float abx = segments[i].b.x - ax;
        float aby = segments[i].b.y - ay;
        soa.ax[i] = ax;
        soa.ay[i] = ay;
        soa.abx[i] = abx;
        soa.aby[i] = aby;
        soa.poly_idx[i] = 0;  // All segments belong to polyline 0
        soa.seg_idx[i] = (int)i;
    }

    // Build Chunks (stored locally in this->chunks)
    chunks.clear();
    int CHUNK_SIZE = 4;  // SSE/NEON is 4-wide
    int seg_count = (int)segments.size();

    for (int j = 0; j < seg_count; j += CHUNK_SIZE) {
        Chunk c;
        c.poly_idx = 0;
        c.seg_idx = j;
        c.global_start = j;
        c.count = std::min(CHUNK_SIZE, seg_count - j);
        c.min = {1e30F, 1e30F};
        c.max = {-1e30F, -1e30F};
        for (int k = 0; k < c.count; ++k) {
            int seg_idx_k = c.global_start + k;
            const auto& s = segments[static_cast<size_t>(seg_idx_k)];
            c.min.x = std::min({c.min.x, s.a.x, s.b.x});
            c.min.y = std::min({c.min.y, s.a.y, s.b.y});
            c.max.x = std::max({c.max.x, s.a.x, s.b.x});
            c.max.y = std::max({c.max.y, s.a.y, s.b.y});
        }
        chunks.push_back(c);
    }

    // Setup and build tree
    indices.resize(chunks.size());
    std::iota(indices.begin(), indices.end(), 0);
    int reserve_n = (int)chunks.size() * 2;
    minx.clear();
    minx.reserve(static_cast<size_t>(reserve_n));
    miny.clear();
    miny.reserve(static_cast<size_t>(reserve_n));
    maxx.clear();
    maxx.reserve(static_cast<size_t>(reserve_n));
    maxy.clear();
    maxy.reserve(static_cast<size_t>(reserve_n));
    left.clear();
    left.reserve(static_cast<size_t>(reserve_n));
    right.clear();
    right.reserve(static_cast<size_t>(reserve_n));
    chunk_idx.clear();
    chunk_idx.reserve(static_cast<size_t>(reserve_n));

    build_recursive(0, (int)indices.size());
}

// Public API: Query single point with internal stats tracking
bool PolyBVH::query_iter(const Vec2f& p,
                         float& best_dist,
                         int& best_poly,
                         int& best_seg,
                         int& best_global) const {
    // Reset stats
    last_stats = QueryStats{};

    // Internal call
    query_iter_internal(p, best_dist, best_poly, best_seg, best_global,
                        last_stats.chunks_visited, last_stats.nodes_visited,
                        last_stats.aabb_evals, last_stats.simd_leaves);

    return best_global >= 0;
}

// Internal implementation (can be called with explicit stats tracking if
// needed)
void PolyBVH::query_iter_internal(const Vec2f& p,
                                  float& best_dist,
                                  int& best_poly,
                                  int& best_seg,
                                  int& best_global,
                                  long long& stats_chunks,
                                  long long& stats_nodes,
                                  long long& stats_aabb,
                                  long long& stats_simd_leaves) const {
    struct Item {
        int idx;
        float d;
    };

    Item stack[256];  // Increased from 128 to 256 for safety
    int sp = 0;
    const int MAX_STACK = 256;

    if (minx.empty()) return;  // Guard: BVH not built or built on empty input

    float root_dist =
        dist2_point_aabb_xy(p, minx[0], miny[0], maxx[0], maxy[0]);
    stack[sp++] = {0, root_dist};
    stats_aabb++;

    while (sp) {
        Item it = stack[--sp];
        if (it.d >= best_dist) continue;

        stats_nodes++;

        int cidx = chunk_idx[static_cast<size_t>(it.idx)];
        if (cidx != -1) {
            const auto& chunk = chunks[static_cast<size_t>(cidx)];
            stats_chunks++;

#ifdef BVH_USE_SIMD
            if (chunk.count == 4) {
                float d2s[4];
                dist2_point_segment_simd_soa_4(p, soa, chunk.global_start, d2s);
                for (int i = 0; i < 4; ++i) {
                    float d2 = d2s[i];
                    if (d2 < best_dist ||
                        (d2 == best_dist && (chunk.seg_idx + i) < best_seg)) {
                        best_dist = d2;
                        best_poly = chunk.poly_idx;
                        best_seg = chunk.seg_idx + i;
                        best_global = chunk.global_start + i;
                    }
                }
                stats_simd_leaves++;
                continue;
            }
#endif
            for (int i = 0; i < chunk.count; ++i) {
                float d2 = dist2_point_segment_soa_scalar(
                    p, soa, chunk.global_start + i);
                if (d2 < best_dist ||
                    (d2 == best_dist && (chunk.seg_idx + i) < best_seg)) {
                    best_dist = d2;
                    best_poly = chunk.poly_idx;
                    best_seg = chunk.seg_idx + i;
                    best_global = chunk.global_start + i;
                }
            }
            continue;
        }

        int l = this->left[static_cast<size_t>(it.idx)];
        int r = this->right[static_cast<size_t>(it.idx)];
        float dl = dist2_point_aabb_xy(p, minx[static_cast<size_t>(l)], miny[static_cast<size_t>(l)], maxx[static_cast<size_t>(l)], maxy[static_cast<size_t>(l)]);
        float dr = dist2_point_aabb_xy(p, minx[static_cast<size_t>(r)], miny[static_cast<size_t>(r)], maxx[static_cast<size_t>(r)], maxy[static_cast<size_t>(r)]);
        stats_aabb += 2;

        if (dl < dr) {
            // Push far node first (lower priority), near node last (higher priority)
            if (dr < best_dist && sp < MAX_STACK) {
                stack[sp++] = {r, dr};
            }
            if (dl < best_dist && sp < MAX_STACK) {
                stack[sp++] = {l, dl};
            }
        } else {
            if (dl < best_dist && sp < MAX_STACK) {
                stack[sp++] = {l, dl};
            }
            if (dr < best_dist && sp < MAX_STACK) {
                stack[sp++] = {r, dr};
            }
        }
    }
}

#ifdef BVH_USE_SIMD
inline float PolyBVH::hmin_f32x4(float32x4_t v) {
#ifdef BVH_USE_NEON
    float a = vgetq_lane_f32(v, 0);
    float b = vgetq_lane_f32(v, 1);
    float c = vgetq_lane_f32(v, 2);
    float d = vgetq_lane_f32(v, 3);
    return std::min(std::min(a, b), std::min(c, d));
#else
    __m128 shuf = _mm_movehdup_ps(v);
    __m128 mins = _mm_min_ps(v, shuf);
    shuf = _mm_movehl_ps(shuf, mins);
    mins = _mm_min_ps(mins, shuf);
    return _mm_cvtss_f32(mins);
#endif
}

inline bool PolyBVH::any_u32x4(uint32x4_t m) {
#ifdef BVH_USE_NEON
    return (vgetq_lane_u32(m, 0) | vgetq_lane_u32(m, 1) | vgetq_lane_u32(m, 2) |
            vgetq_lane_u32(m, 3)) != 0;
#else
    return _mm_movemask_ps(m) != 0;
#endif
}

inline float32x4_t PolyBVH::dist2_point_aabb_xy_4(float32x4_t px,
                                                  float32x4_t py,
                                                  float mi_x,
                                                  float mi_y,
                                                  float ma_x,
                                                  float ma_y) const {
#ifdef BVH_USE_NEON
    float32x4_t minxv = vdupq_n_f32(mi_x);
    float32x4_t minyv = vdupq_n_f32(mi_y);
    float32x4_t maxxv = vdupq_n_f32(ma_x);
    float32x4_t maxyv = vdupq_n_f32(ma_y);

    float32x4_t dx1 = vsubq_f32(minxv, px);
    float32x4_t dx2 = vsubq_f32(px, maxxv);
    float32x4_t dx = vmaxq_f32(vmaxq_f32(dx1, dx2), vdupq_n_f32(0.0F));

    float32x4_t dy1 = vsubq_f32(minyv, py);
    float32x4_t dy2 = vsubq_f32(py, maxyv);
    float32x4_t dy = vmaxq_f32(vmaxq_f32(dy1, dy2), vdupq_n_f32(0.0F));

    return vmlaq_f32(vmulq_f32(dx, dx), dy, dy);
#else
    float32x4_t minxv = _mm_set1_ps(mi_x);
    float32x4_t minyv = _mm_set1_ps(mi_y);
    float32x4_t maxxv = _mm_set1_ps(ma_x);
    float32x4_t maxyv = _mm_set1_ps(ma_y);

    float32x4_t dx1 = _mm_sub_ps(minxv, px);
    float32x4_t dx2 = _mm_sub_ps(px, maxxv);
    float32x4_t dx = _mm_max_ps(_mm_max_ps(dx1, dx2), _mm_set1_ps(0.0F));

    float32x4_t dy1 = _mm_sub_ps(minyv, py);
    float32x4_t dy2 = _mm_sub_ps(py, maxyv);
    float32x4_t dy = _mm_max_ps(_mm_max_ps(dy1, dy2), _mm_set1_ps(0.0F));

    return _mm_add_ps(_mm_mul_ps(dx, dx), _mm_mul_ps(dy, dy));
#endif
}

#ifdef BVH_USE_AVX2
inline float PolyBVH::hmin_f32x8(float32x8_t v) {
    __m128 lo = _mm256_castps256_ps128(v);
    __m128 hi = _mm256_extractf128_ps(v, 1);
    __m128 min4 = _mm_min_ps(lo, hi);
    __m128 shuf = _mm_movehdup_ps(min4);
    __m128 mins = _mm_min_ps(min4, shuf);
    shuf = _mm_movehl_ps(shuf, mins);
    mins = _mm_min_ps(mins, shuf);
    return _mm_cvtss_f32(mins);
}

inline bool PolyBVH::any_u32x8(uint32x8_t m) {
    return _mm256_movemask_ps(m) != 0;
}

inline float32x8_t PolyBVH::dist2_point_aabb_xy_8(float32x8_t px,
                                                  float32x8_t py,
                                                  float mi_x,
                                                  float mi_y,
                                                  float ma_x,
                                                  float ma_y) const {
    float32x8_t minxv = _mm256_set1_ps(mi_x);
    float32x8_t minyv = _mm256_set1_ps(mi_y);
    float32x8_t maxxv = _mm256_set1_ps(ma_x);
    float32x8_t maxyv = _mm256_set1_ps(ma_y);

    float32x8_t dx1 = _mm256_sub_ps(minxv, px);
    float32x8_t dx2 = _mm256_sub_ps(px, maxxv);
    float32x8_t dx =
        _mm256_max_ps(_mm256_max_ps(dx1, dx2), _mm256_set1_ps(0.0F));

    float32x8_t dy1 = _mm256_sub_ps(minyv, py);
    float32x8_t dy2 = _mm256_sub_ps(py, maxyv);
    float32x8_t dy =
        _mm256_max_ps(_mm256_max_ps(dy1, dy2), _mm256_set1_ps(0.0F));

    return _mm256_fmadd_ps(dx, dx, _mm256_mul_ps(dy, dy));
}
#endif

#ifdef BVH_USE_AVX512
inline float PolyBVH::hmin_f32x16(float32x16_t v) {
    __m256 lo = _mm512_castps512_ps256(v);
    __m256 hi = _mm512_extractf32x8_ps(v, 1);
    __m256 min8 = _mm256_min_ps(lo, hi);
    __m128 lo4 = _mm256_castps256_ps128(min8);
    __m128 hi4 = _mm256_extractf128_ps(min8, 1);
    __m128 min4 = _mm_min_ps(lo4, hi4);
    __m128 shuf = _mm_movehdup_ps(min4);
    __m128 mins = _mm_min_ps(min4, shuf);
    shuf = _mm_movehl_ps(shuf, mins);
    mins = _mm_min_ps(mins, shuf);
    return _mm_cvtss_f32(mins);
}

inline bool PolyBVH::any_mask16(mask16_t m) { return m != 0; }

inline float32x16_t PolyBVH::dist2_point_aabb_xy_16(float32x16_t px,
                                                    float32x16_t py,
                                                    float mi_x,
                                                    float mi_y,
                                                    float ma_x,
                                                    float ma_y) const {
    float32x16_t minxv = _mm512_set1_ps(mi_x);
    float32x16_t minyv = _mm512_set1_ps(mi_y);
    float32x16_t maxxv = _mm512_set1_ps(ma_x);
    float32x16_t maxyv = _mm512_set1_ps(ma_y);

    float32x16_t dx1 = _mm512_sub_ps(minxv, px);
    float32x16_t dx2 = _mm512_sub_ps(px, maxxv);
    float32x16_t dx =
        _mm512_max_ps(_mm512_max_ps(dx1, dx2), _mm512_set1_ps(0.0F));

    float32x16_t dy1 = _mm512_sub_ps(minyv, py);
    float32x16_t dy2 = _mm512_sub_ps(py, maxyv);
    float32x16_t dy =
        _mm512_max_ps(_mm512_max_ps(dy1, dy2), _mm512_set1_ps(0.0F));

    return _mm512_fmadd_ps(dx, dx, _mm512_mul_ps(dy, dy));
}
#endif

// Packet traversal for 4 query points.
// - `best_global[i]` and `best_dist2[i]` are both input/output.
// - Exact math by default (fast-math only affects the leaf NEON distance
// kernel).
inline void PolyBVH::query_packet4(const Vec2f p4[4],
                                   const SegSOA& soa,
                                   int best_global[4],
                                   int best_poly[4],
                                   int best_seg[4],
                                   float best_dist2[4],
                                   long long& stats_chunks,
                                   long long& stats_nodes,
                                   long long& stats_aabb,
                                   long long& stats_simd_leaves) const {
    float xs[4] = {p4[0].x, p4[1].x, p4[2].x, p4[3].x};
    float ys[4] = {p4[0].y, p4[1].y, p4[2].y, p4[3].y};
#ifdef BVH_USE_NEON
    float32x4_t px = vld1q_f32(xs);
    float32x4_t py = vld1q_f32(ys);
    float32x4_t bestv = vld1q_f32(best_dist2);
#else
    float32x4_t px = _mm_loadu_ps(xs);
    float32x4_t py = _mm_loadu_ps(ys);
    float32x4_t bestv = _mm_loadu_ps(best_dist2);
#endif

    struct Item {
        int idx;
        float key;
    };
    Item stack[256];  // Increased from 128 to 256 for safety
    int sp = 0;
    const int MAX_STACK = 256;

    float32x4_t root_d =
        dist2_point_aabb_xy_4(px, py, minx[0], miny[0], maxx[0], maxy[0]);
#ifdef BVH_USE_NEON
    uint32x4_t root_m = vcltq_f32(root_d, bestv);
#else
    uint32x4_t root_m = _mm_cmplt_ps(root_d, bestv);
#endif
    stats_aabb++;
    if (any_u32x4(root_m)) {
        stack[sp++] = {0, hmin_f32x4(root_d)};
    }

    while (sp) {
        Item it = stack[--sp];

        int idx = it.idx;
        stats_nodes++;

        int cidx = chunk_idx[static_cast<size_t>(idx)];
        if (cidx != -1) {
            const auto& chunk = chunks[static_cast<size_t>(cidx)];
            stats_chunks++;

            if (chunk.count == 4) {
                float d2s0[4], d2s1[4], d2s2[4], d2s3[4];
                dist2_point_segment_simd_soa_4(p4[0], soa, chunk.global_start,
                                               d2s0);
                dist2_point_segment_simd_soa_4(p4[1], soa, chunk.global_start,
                                               d2s1);
                dist2_point_segment_simd_soa_4(p4[2], soa, chunk.global_start,
                                               d2s2);
                dist2_point_segment_simd_soa_4(p4[3], soa, chunk.global_start,
                                               d2s3);

                float* d2sp[4] = {d2s0, d2s1, d2s2, d2s3};
                for (int lane = 0; lane < 4; ++lane) {
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    float* d2s = d2sp[lane];
                    for (int k = 0; k < 4; k++) {
                        if (d2s[k] < best ||
                            (d2s[k] == best && (chunk.seg_idx + k) < bests)) {
                            best = d2s[k];
                            bestg = chunk.global_start + k;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + k;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
#ifdef BVH_USE_NEON
                bestv = vld1q_f32(best_dist2);
#else
                bestv = _mm_loadu_ps(best_dist2);
#endif
                stats_simd_leaves++;
                continue;
            }

            // Rare tail chunks: scalar per lane
            for (int lane = 0; lane < 4; ++lane) {
                float best = best_dist2[lane];
                int bestg = best_global[lane];
                int bestp = best_poly[lane];
                int bests = best_seg[lane];
                for (int i = 0; i < chunk.count; ++i) {
                    int gi = chunk.global_start + i;
                    float d2 =
                        dist2_point_segment_soa_scalar(p4[lane], soa, gi);
                    if (d2 < best ||
                        (d2 == best && (chunk.seg_idx + i) < bests)) {
                        best = d2;
                        bestg = gi;
                        bestp = chunk.poly_idx;
                        bests = chunk.seg_idx + i;
                    }
                }
                best_dist2[lane] = best;
                best_global[lane] = bestg;
                best_poly[lane] = bestp;
                best_seg[lane] = bests;
            }
#ifdef BVH_USE_NEON
            bestv = vld1q_f32(best_dist2);
#else
            bestv = _mm_loadu_ps(best_dist2);
#endif
            continue;
        }

        int l = this->left[static_cast<size_t>(idx)];
        int r = this->right[static_cast<size_t>(idx)];

        float32x4_t dlv =
            dist2_point_aabb_xy_4(px, py, minx[static_cast<size_t>(l)], miny[static_cast<size_t>(l)], maxx[static_cast<size_t>(l)], maxy[static_cast<size_t>(l)]);
        float32x4_t drv =
            dist2_point_aabb_xy_4(px, py, minx[static_cast<size_t>(r)], miny[static_cast<size_t>(r)], maxx[static_cast<size_t>(r)], maxy[static_cast<size_t>(r)]);
        stats_aabb += 2;

#ifdef BVH_USE_NEON
        uint32x4_t ml = vcltq_f32(dlv, bestv);
        uint32x4_t mr = vcltq_f32(drv, bestv);
#else
        uint32x4_t ml = _mm_cmplt_ps(dlv, bestv);
        uint32x4_t mr = _mm_cmplt_ps(drv, bestv);
#endif

        bool push_l = any_u32x4(ml);
        bool push_r = any_u32x4(mr);

        if (!push_l && !push_r) continue;

        float kl = push_l ? hmin_f32x4(dlv) : 1e30F;
        float kr = push_r ? hmin_f32x4(drv) : 1e30F;

        // Push farther first so nearer is processed sooner (LIFO).
        if (kl < kr) {
            if (push_r) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
            if (push_l) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
        } else {
            if (push_l) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
            if (push_r) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
        }
    }
}

#ifdef BVH_USE_AVX2
// Packet traversal for 8 query points using AVX2.
inline void PolyBVH::query_packet8(const Vec2f p8[8],
                                   const SegSOA& soa,
                                   int best_global[8],
                                   int best_poly[8],
                                   int best_seg[8],
                                   float best_dist2[8],
                                   long long& stats_chunks,
                                   long long& stats_nodes,
                                   long long& stats_aabb,
                                   long long& stats_simd_leaves) const {
    float xs[8], ys[8];
    for (int i = 0; i < 8; i++) {
        xs[i] = p8[i].x;
        ys[i] = p8[i].y;
    }
    float32x8_t px = _mm256_loadu_ps(xs);
    float32x8_t py = _mm256_loadu_ps(ys);
    float32x8_t bestv = _mm256_loadu_ps(best_dist2);

    struct Item {
        int idx;
        float key;
    };
    Item stack[256];  // Increased from 128 to 256 for safety
    int sp = 0;
    const int MAX_STACK = 256;

    float32x8_t root_d =
        dist2_point_aabb_xy_8(px, py, minx[0], miny[0], maxx[0], maxy[0]);
    uint32x8_t root_m = _mm256_cmp_ps(root_d, bestv, _CMP_LT_OQ);
    stats_aabb++;
    if (any_u32x8(root_m)) {
        stack[sp++] = {0, hmin_f32x8(root_d)};
    }

    while (sp) {
        Item it = stack[--sp];
        // if (it.key >= hmin_f32x8(bestv)) continue; // Incorrect pruning
        // for packets

        int idx = it.idx;
        stats_nodes++;

        int cidx = chunk_idx[static_cast<size_t>(idx)];
        if (cidx != -1) {
            const auto& chunk = chunks[static_cast<size_t>(cidx)];
            stats_chunks++;

            if (chunk.count == 8) {
                // Optimized 8-wide: each lane processes 8 segments with
                // SIMD
                for (int lane = 0; lane < 8; ++lane) {
                    float d2s[8];
                    dist2_point_segment_simd_soa_8(p8[lane], soa,
                                                   chunk.global_start, d2s);
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    for (int i = 0; i < 8; ++i) {
                        if (d2s[i] < best ||
                            (d2s[i] == best && (chunk.seg_idx + i) < bests)) {
                            best = d2s[i];
                            bestg = chunk.global_start + i;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + i;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
                bestv = _mm256_loadu_ps(best_dist2);
                stats_simd_leaves++;
                continue;
            }

            if (chunk.count == 4) {
                for (int lane = 0; lane < 8; ++lane) {
                    float d2s[4];
                    dist2_point_segment_simd_soa_4(p8[lane], soa,
                                                   chunk.global_start, d2s);
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    for (int i = 0; i < 4; ++i) {
                        if (d2s[i] < best ||
                            (d2s[i] == best && (chunk.seg_idx + i) < bests)) {
                            best = d2s[i];
                            bestg = chunk.global_start + i;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + i;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
                bestv = _mm256_loadu_ps(best_dist2);
                stats_simd_leaves++;
                continue;
            }

            for (int lane = 0; lane < 8; ++lane) {
                float best = best_dist2[lane];
                int bestg = best_global[lane];
                int bestp = best_poly[lane];
                int bests = best_seg[lane];
                for (int i = 0; i < chunk.count; ++i) {
                    int gi = chunk.global_start + i;
                    float d2 =
                        dist2_point_segment_soa_scalar(p8[lane], soa, gi);
                    if (d2 < best ||
                        (d2 == best && (chunk.seg_idx + i) < bests)) {
                        best = d2;
                        bestg = gi;
                        bestp = chunk.poly_idx;
                        bests = chunk.seg_idx + i;
                    }
                }
                best_dist2[lane] = best;
                best_global[lane] = bestg;
                best_poly[lane] = bestp;
                best_seg[lane] = bests;
            }
            bestv = _mm256_loadu_ps(best_dist2);
            continue;
        }

        int l = this->left[static_cast<size_t>(idx)];
        int r = this->right[static_cast<size_t>(idx)];

        float32x8_t dlv =
            dist2_point_aabb_xy_8(px, py, minx[static_cast<size_t>(l)], miny[static_cast<size_t>(l)], maxx[static_cast<size_t>(l)], maxy[static_cast<size_t>(l)]);
        float32x8_t drv =
            dist2_point_aabb_xy_8(px, py, minx[static_cast<size_t>(r)], miny[static_cast<size_t>(r)], maxx[static_cast<size_t>(r)], maxy[static_cast<size_t>(r)]);
        stats_aabb += 2;

        uint32x8_t ml = _mm256_cmp_ps(dlv, bestv, _CMP_LT_OQ);
        uint32x8_t mr = _mm256_cmp_ps(drv, bestv, _CMP_LT_OQ);

        bool push_l = any_u32x8(ml);
        bool push_r = any_u32x8(mr);

        if (!push_l && !push_r) continue;

        float kl = push_l ? hmin_f32x8(dlv) : 1e30F;
        float kr = push_r ? hmin_f32x8(drv) : 1e30F;

        if (kl < kr) {
            if (push_r) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
            if (push_l) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
        } else {
            if (push_l) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
            if (push_r) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
        }
    }
}
#endif

#ifdef BVH_USE_AVX512
// Packet traversal for 16 query points using AVX-512.
inline void PolyBVH::query_packet16(const Vec2f p16[16],
                                    const SegSOA& soa,
                                    int best_global[16],
                                    int best_poly[16],
                                    int best_seg[16],
                                    float best_dist2[16],
                                    long long& stats_chunks,
                                    long long& stats_nodes,
                                    long long& stats_aabb,
                                    long long& stats_simd_leaves) const {
    float xs[16], ys[16];
    for (int i = 0; i < 16; i++) {
        xs[i] = p16[i].x;
        ys[i] = p16[i].y;
    }
    float32x16_t px = _mm512_loadu_ps(xs);
    float32x16_t py = _mm512_loadu_ps(ys);
    float32x16_t bestv = _mm512_loadu_ps(best_dist2);

    struct Item {
        int idx;
        float key;
    };
    Item stack[256];  // Increased from 128 to 256 for safety
    int sp = 0;
    const int MAX_STACK = 256;

    float32x16_t root_d =
        dist2_point_aabb_xy_16(px, py, minx[0], miny[0], maxx[0], maxy[0]);
    mask16_t root_m = _mm512_cmp_ps_mask(root_d, bestv, _CMP_LT_OQ);
    stats_aabb++;
    if (any_mask16(root_m)) {
        stack[sp++] = {0, hmin_f32x16(root_d)};
    }

    while (sp) {
        Item it = stack[--sp];
        // if (it.key >= hmin_f32x16(bestv)) continue; // Incorrect pruning
        // for packets

        int idx = it.idx;
        stats_nodes++;

        int cidx = chunk_idx[idx];
        if (cidx != -1) {
            const auto& chunk = chunks[cidx];
            stats_chunks++;

            if (chunk.count == 16) {
                // Optimized 16-wide: each lane processes 16 segments
                for (int lane = 0; lane < 16; ++lane) {
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    for (int i = 0; i < 16; ++i) {
                        int gi = chunk.global_start + i;
                        float d2 =
                            dist2_point_segment_soa_scalar(p16[lane], soa, gi);
                        if (d2 < best ||
                            (d2 == best && (chunk.seg_idx + i) < bests)) {
                            best = d2;
                            bestg = gi;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + i;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
                bestv = _mm512_loadu_ps(best_dist2);
                stats_simd_leaves++;
                continue;
            }

            if (chunk.count == 8) {
                // Optimized 8-wide: each lane processes 8 segments with
                // SIMD
                for (int lane = 0; lane < 16; ++lane) {
                    float d2s[8];
                    dist2_point_segment_simd_soa_8(p16[lane], soa,
                                                   chunk.global_start, d2s);
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    for (int i = 0; i < 8; ++i) {
                        if (d2s[i] < best ||
                            (d2s[i] == best && (chunk.seg_idx + i) < bests)) {
                            best = d2s[i];
                            bestg = chunk.global_start + i;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + i;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
                bestv = _mm512_loadu_ps(best_dist2);
                stats_simd_leaves++;
                continue;
            }

            if (chunk.count == 4) {
                for (int lane = 0; lane < 16; ++lane) {
                    float d2s[4];
                    dist2_point_segment_simd_soa_4(p16[lane], soa,
                                                   chunk.global_start, d2s);
                    float best = best_dist2[lane];
                    int bestg = best_global[lane];
                    int bestp = best_poly[lane];
                    int bests = best_seg[lane];
                    for (int i = 0; i < 4; ++i) {
                        if (d2s[i] < best ||
                            (d2s[i] == best && (chunk.seg_idx + i) < bests)) {
                            best = d2s[i];
                            bestg = chunk.global_start + i;
                            bestp = chunk.poly_idx;
                            bests = chunk.seg_idx + i;
                        }
                    }
                    best_dist2[lane] = best;
                    best_global[lane] = bestg;
                    best_poly[lane] = bestp;
                    best_seg[lane] = bests;
                }
                bestv = _mm512_loadu_ps(best_dist2);
                stats_simd_leaves++;
                continue;
            }

            for (int lane = 0; lane < 16; ++lane) {
                float best = best_dist2[lane];
                int bestg = best_global[lane];
                int bestp = best_poly[lane];
                int bests = best_seg[lane];
                for (int i = 0; i < chunk.count; ++i) {
                    int gi = chunk.global_start + i;
                    float d2 =
                        dist2_point_segment_soa_scalar(p16[lane], soa, gi);
                    if (d2 < best ||
                        (d2 == best && (chunk.seg_idx + i) < bests)) {
                        best = d2;
                        bestg = gi;
                        bestp = chunk.poly_idx;
                        bests = chunk.seg_idx + i;
                    }
                }
                best_dist2[lane] = best;
                best_global[lane] = bestg;
                best_poly[lane] = bestp;
                best_seg[lane] = bests;
            }
            bestv = _mm512_loadu_ps(best_dist2);
            continue;
        }

        int l = this->left[idx];
        int r = this->right[idx];

        float32x16_t dlv =
            dist2_point_aabb_xy_16(px, py, minx[l], miny[l], maxx[l], maxy[l]);
        float32x16_t drv =
            dist2_point_aabb_xy_16(px, py, minx[r], miny[r], maxx[r], maxy[r]);
        stats_aabb += 2;

        mask16_t ml = _mm512_cmp_ps_mask(dlv, bestv, _CMP_LT_OQ);
        mask16_t mr = _mm512_cmp_ps_mask(drv, bestv, _CMP_LT_OQ);

        bool push_l = any_mask16(ml);
        bool push_r = any_mask16(mr);

        if (!push_l && !push_r) continue;

        float kl = push_l ? hmin_f32x16(dlv) : 1e30F;
        float kr = push_r ? hmin_f32x16(drv) : 1e30F;

        if (kl < kr) {
            if (push_r) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
            if (push_l) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
        } else {
            if (push_l) {
                if ((sp + 1) >= MAX_STACK) continue;  // Stack full, skip left subtree
                stack[sp++] = {l, kl};
            }
            if (push_r) {
                if (sp >= MAX_STACK) continue;  // Stack full, skip right subtree
                stack[sp++] = {r, kr};
            }
        }
    }
}
#endif
#endif

void PolyBVH::query_batch(const Vec2f* queries,
                          int query_count,
                          float* out_best_dist2,
                          int* out_best_poly,
                          int* out_best_seg,
                          int* out_best_global,
                          const int* seed_best_global,
                          bool force_scalar) const {
    // Reset stats
    last_stats = QueryStats{};

    // Call implementation
    query_batch_impl(queries, query_count, out_best_dist2, out_best_poly,
                     out_best_seg, out_best_global, seed_best_global,
                     &last_stats.chunks_visited, &last_stats.nodes_visited,
                     &last_stats.aabb_evals, &last_stats.simd_leaves,
                     force_scalar);
}

// ================= Implementation of PolyBVH::query_batch_impl
// =================
inline void PolyBVH::query_batch_impl(const Vec2f* queries,
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
                                      bool force_scalar) const {
    long long local_chunks = 0;
    long long local_nodes = 0;
    long long local_aabb = 0;
    long long local_simd4_leaves = 0;

    int i = 0;

#ifdef BVH_USE_AVX512
    // AVX-512 packet traversal: 16 queries share one BVH walk.
    if (!force_scalar) {
        for (; i + 15 < query_count; i += 16) {
            Vec2f p16[16];
            for (int k = 0; k < 16; k++) p16[k] = queries[i + k];
            int bestg[16];
            int bestp[16];
            int bests[16];
            float bestd[16];
            for (int k = 0; k < 16; k++) {
                bestg[k] = -1;
                bestp[k] = -1;
                bests[k] = -1;
                bestd[k] = 1e30F;
            }

            if (seed_best_global) {
                for (int lane = 0; lane < 16; ++lane) {
                    int seed = seed_best_global[i + lane];
                    if (seed >= 0) {
                        bestg[lane] = seed;
                        bestp[lane] = this->soa.poly_idx[static_cast<size_t>(seed)];
                        bests[lane] = this->soa.seg_idx[static_cast<size_t>(seed)];
                        bestd[lane] = dist2_point_segment_soa_scalar(
                            p16[lane], this->soa, seed);
                    }
                }
            }

            this->query_packet16(p16, this->soa, bestg, bestp, bests, bestd,
                                 local_chunks, local_nodes, local_aabb,
                                 local_simd4_leaves);

            for (int k = 0; k < 16; k++) {
                out_best_global[i + k] = bestg[k];
                if (out_best_poly) out_best_poly[i + k] = bestp[k];
                if (out_best_seg) out_best_seg[i + k] = bests[k];
                if (out_best_dist2) out_best_dist2[i + k] = bestd[k];
            }
        }
    }
#endif

#ifdef BVH_USE_AVX2
    // AVX2 packet traversal: 8 queries share one BVH walk.
    if (!force_scalar) {
        for (; i + 7 < query_count; i += 8) {
            Vec2f p8[8];
            for (int k = 0; k < 8; k++) p8[k] = queries[i + k];
            int bestg[8];
            int bestp[8];
            int bests[8];
            float bestd[8];
            for (int k = 0; k < 8; k++) {
                bestg[k] = -1;
                bestp[k] = -1;
                bests[k] = -1;
                bestd[k] = 1e30F;
            }

            if (seed_best_global) {
                for (int lane = 0; lane < 8; ++lane) {
                    int seed = seed_best_global[i + lane];
                    if (seed >= 0) {
                        bestg[lane] = seed;
                        bestp[lane] = this->soa.poly_idx[static_cast<size_t>(seed)];
                        bests[lane] = this->soa.seg_idx[static_cast<size_t>(seed)];
                        bestd[lane] = dist2_point_segment_soa_scalar(
                            p8[lane], this->soa, seed);
                    }
                }
            }

            this->query_packet8(p8, this->soa, bestg, bestp, bests, bestd,
                                local_chunks, local_nodes, local_aabb,
                                local_simd4_leaves);

            for (int k = 0; k < 8; k++) {
                out_best_global[i + k] = bestg[k];
                if (out_best_poly) out_best_poly[i + k] = bestp[k];
                if (out_best_seg) out_best_seg[i + k] = bests[k];
                if (out_best_dist2) out_best_dist2[i + k] = bestd[k];
            }
        }
    }
#endif

#if defined(BVH_USE_SIMD) && !defined(BVH_USE_AVX2) && !defined(BVH_USE_AVX512)
    // Packet traversal: 4 queries share one BVH walk (SSE/NEON).
    if (!force_scalar) {
        for (; i + 3 < query_count; i += 4) {
            Vec2f p4[4] = {queries[i + 0], queries[i + 1], queries[i + 2],
                           queries[i + 3]};
            int bestg[4] = {-1, -1, -1, -1};
            int bestp[4] = {-1, -1, -1, -1};
            int bests[4] = {-1, -1, -1, -1};
            float bestd[4] = {1e30F, 1e30F, 1e30F, 1e30F};

            if (seed_best_global) {
                for (int lane = 0; lane < 4; ++lane) {
                    int seed = seed_best_global[i + lane];
                    if (seed >= 0) {
                        bestg[lane] = seed;
                        bestp[lane] = this->soa.poly_idx[static_cast<size_t>(seed)];
                        bests[lane] = this->soa.seg_idx[static_cast<size_t>(seed)];
                        bestd[lane] = dist2_point_segment_soa_scalar(
                            p4[lane], this->soa, seed);
                    }
                }
            }

            this->query_packet4(p4, this->soa, bestg, bestp, bests, bestd,
                                local_chunks, local_nodes, local_aabb,
                                local_simd4_leaves);

            for (int k = 0; k < 4; ++k) {
                out_best_global[i + k] = bestg[k];
                if (out_best_poly) out_best_poly[i + k] = bestp[k];
                if (out_best_seg) out_best_seg[i + k] = bests[k];
                if (out_best_dist2) out_best_dist2[i + k] = bestd[k];
            }
        }
    }
#endif

    // Tail / scalar path.
    for (; i < query_count; ++i) {
        const Vec2f& p = queries[i];

        float best = 1e30F;
        int best_poly = -1;
        int best_seg = -1;
        int best_global = -1;

        if (seed_best_global) {
            int seed = seed_best_global[i];
            if (seed >= 0) {
                best_global = seed;
                best_poly = this->soa.poly_idx[static_cast<size_t>(seed)];
                best_seg = this->soa.seg_idx[static_cast<size_t>(seed)];
                best = dist2_point_segment_soa_scalar(p, this->soa, seed);
            }
        }

        this->query_iter_internal(p, best, best_poly, best_seg, best_global,
                                  local_chunks, local_nodes, local_aabb,
                                  local_simd4_leaves);

        out_best_global[i] = best_global;
        if (out_best_poly) out_best_poly[i] = best_poly;
        if (out_best_seg) out_best_seg[i] = best_seg;
        if (out_best_dist2) out_best_dist2[i] = best;
    }

    if (stats_chunks) *stats_chunks += local_chunks;
    if (stats_nodes) *stats_nodes += local_nodes;
    if (stats_aabb) *stats_aabb += local_aabb;
    if (stats_simd4_leaves) *stats_simd4_leaves += local_simd4_leaves;
}

}  // namespace planning_pilot
}  // namespace senseAD
