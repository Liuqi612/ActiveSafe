/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <Eigen/Dense>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <utility>
#include <vector>
namespace active_safety {
namespace math {

struct Point2D {
    float x, y;

    Point2D(float x = 0.0f, float y = 0.0f) : x(x), y(y) {}

    Point2D  operator-(const Point2D &b) const { return {x - b.x, y - b.y}; }
    Point2D &operator=(const Point2D &) = default;
    bool     operator==(const Point2D &b) const { return (x == b.x && y == b.y); }

    Point2D operator/(const float &scale) const { return Point2D(x / scale, y / scale); }
    Point2D operator*(const float &scale) const { return Point2D(x * scale, y * scale); }

    float Dot(const Point2D &b) const { return x * b.x + y * b.y; }
    float Norm() const { return std::sqrt(x * x + y * y); }
    float Project(const Point2D &p) const { return this->Dot(p / p.Norm()); }
    float Cross(const Point2D &p) const { return x * p.y - y * p.x; }
};

struct Box2D {
  public:
    Point2D left_top, right_top, left_bottom, right_bottom;

    void BuildFromCenter(float center_x, float center_y, float heading_rad, float length, float width) noexcept {
        const float cos_theta = std::cos(heading_rad);
        const float sin_theta = std::sin(heading_rad);

        const float half_len = length * 0.5f;
        const float half_wid = width * 0.5f;

        const float dx1 = -half_len * cos_theta;
        const float dy1 = -half_len * sin_theta;
        const float dx2 = half_wid * sin_theta;
        const float dy2 = -half_wid * cos_theta;

        left_top.x     = center_x + dx1 - dx2;
        left_top.y     = center_y + dy1 - dy2;
        right_top.x    = center_x + dx1 + dx2;
        right_top.y    = center_y + dy1 + dy2;
        left_bottom.x  = center_x - dx1 - dx2;
        left_bottom.y  = center_y - dy1 - dy2;
        right_bottom.x = center_x - dx1 + dx2;
        right_bottom.y = center_y - dy1 + dy2;

        ComputeAABB();
    }

    // AABB judge if collision, true means not collision
    bool QuickRejectTest(const Box2D &other) const {
        return min_x > other.max_x || max_x < other.min_x || min_y > other.max_y || max_y < other.min_y;
    }

    void ComputeAABB() noexcept {
        float x[4] = {left_top.x, right_top.x, left_bottom.x, right_bottom.x};
        float y[4] = {left_top.y, right_top.y, left_bottom.y, right_bottom.y};

        min_x = max_x = x[0];
        min_y = max_y = y[0];

        for (int i = 1; i < 4; ++i) {
            min_x = std::min(min_x, x[i]);
            max_x = std::max(max_x, x[i]);
            min_y = std::min(min_y, y[i]);
            max_y = std::max(max_y, y[i]);
        }
    }

  private:
    float min_x, max_x, min_y, max_y;
};

struct Polygon {
    std::vector<Point2D> point_list;

    std::vector<Point2D>::iterator       begin() { return point_list.begin(); }
    std::vector<Point2D>::const_iterator begin() const { return point_list.begin(); }
    std::vector<Point2D>::iterator       end() { return point_list.end(); }
    std::vector<Point2D>::const_iterator end() const { return point_list.end(); }
    void                                 clear() { point_list.clear(); }
};

struct Geometry {
    // 线段与圆相交的结果：交点坐标 + 对应的圆弧长度。
    struct SegmentCircleIntersection {
        Point2D point;      // 交点在原始坐标系下的坐标
        float   arc_length; // 交点对应的弧长：radius * atan2(y_c, x_c)（以圆心为原点，在圆上坐标为 (x_c, y_c)）
    };
    // 射线法（Ray-Casting Algorithm）是判断点是否在多边形内的经典算法，其基本思路是：
    // 1. 从待测点 pt 水平向右发射一条射线；
    // 2. 统计该射线与多边形边的交点数量：
    //    a) 如果交点数量为奇数，则点在多边形内；
    //    b) 如果交点数量为偶数，则点在多边形外。
    static bool IsPointInPoly(const Polygon &polygon, const Point2D &pt) {
        if (polygon.point_list.size() < 3) {
            return false;
        }
        bool inside = false;

        const size_t n = polygon.point_list.size();

        for (size_t i = 0, j = n - 1; i < n; j = i++) {
            const Point2D &p1 = polygon.point_list[i];
            const Point2D &p2 = polygon.point_list[j];

            // 检查点是否在多边形的顶点上
            if (pt == p1 || pt == p2)
                return true;

            // 检查点是否在边的水平线上
            if ((p1.y == p2.y) && (pt.y == p1.y) && (pt.x >= std::min(p1.x, p2.x)) && (pt.x <= std::max(p1.x, p2.x))) {
                return true;
            }

            // 检查射线是否与边相交
            if ((p1.y > pt.y) != (p2.y > pt.y)) { // 跨越 Y 坐标
                float x_intersect = (p2.x - p1.x) * (pt.y - p1.y) / (p2.y - p1.y) + p1.x;

                // 点在边上
                if (pt.x == x_intersect)
                    return true;

                // 射线向右延伸，计算交点
                if (pt.x < x_intersect) {
                    inside = !inside;
                }
            }
        }
        return inside;
    }

    // 判断点 p 是否落在线段 [a, b] 的轴对齐包围盒（AABB）内。
    // 注意：这里只检查投影范围，不检查共线性，通常配合其他几何判定一起使用。
    static bool IsPointOnSegmentBoundingBox(const Point2D &p, const Point2D &a, const Point2D &b) {
        const float min_x = std::min(a.x, b.x);
        const float max_x = std::max(a.x, b.x);
        const float min_y = std::min(a.y, b.y);
        const float max_y = std::max(a.y, b.y);
        return (p.x >= min_x && p.x <= max_x && p.y >= min_y && p.y <= max_y);
    }

    // 计算线段 p0-p1 与圆的几何交点。
    //
    // 几何语义：
    //   - 圆：以 center 为圆心、radius 为半径；
    //   - 线段：以 p0、p1 为端点；
    //   - 只返回真实的几何交点（0 / 1 / 2 个）：
    //       * 一般相交：两交点；
    //       * 相切：一个交点；
    //       * 无交：空；
    //       * 退化为点（p0 == p1）：仅当该点“在圆上”（不含圆内）时返回一个交点。
    //
    // 坐标系约定：
    //   - 调用方提供的 p0、p1、center 在同一坐标系中；
    //   - 返回的交点也在该坐标系中；
    //   - 内部会先将坐标平移到“以圆心为原点”的局部坐标系进行运算。
    //   - 同时返回每个交点相对于圆的“弧长”：
    //       * 先在局部坐标系下计算交点的极角 angle = atan2(y_c, x_c)；
    //       * 再计算 arc_length = radius * angle；
    //       * angle 以局部坐标系 x 轴正方向为 0，逆时针为正，范围 (-pi, pi]。
    static std::vector<SegmentCircleIntersection> IntersectSegmentCircle(const Point2D &p0, const Point2D &p1, float radius, const Point2D &center) {
        std::vector<SegmentCircleIntersection> result;

        if (radius <= 0.0f) {
            return result;
        }

        // 平移到以圆心为原点的坐标系
        const Point2D p0c(p0.x - center.x, p0.y - center.y);
        const Point2D p1c(p1.x - center.x, p1.y - center.y);

        const Point2D d = p1c - p0c; // 方向向量

        const float d2 = d.x * d.x + d.y * d.y; // |d|^2

        if (d2 <= 0.0f) {
            // 退化为点（p0 == p1 或近似如此）：
            // 仅当该点“在圆上”时认为存在交点；在圆内但不在圆上不计为交点。
            const float dist2 = p0c.x * p0c.x + p0c.y * p0c.y;
            const float R2    = radius * radius;
            const float eps   = 1e-4f; // 半径平方的浮点容差
            if (std::fabs(dist2 - R2) <= eps) {
                const float angle      = std::atan2(p0c.y, p0c.x);
                const float arc_length = radius * angle;
                result.push_back(SegmentCircleIntersection{p0, arc_length});
            }
            return result;
        }

        const float R2     = radius * radius;
        const float cross  = p0c.Cross(p1c);
        const float cross2 = cross * cross;
        const float delta  = R2 * d2 - cross2; // 判别式：<0 无交点，=0 相切，>0 两交点

        if (delta < 0.0f) {
            // 无交点
            return result;
        }

        // 判别式 delta = R^2 * |d|^2 - (p0 × p1)^2 已经保证 delta >= 0。
        // 下面根据解析几何推导出的闭式解，计算直线与圆的两个交点：
        //
        //    设：
        //      d   = p1 - p0               （线段方向向量）
        //      |d| = sqrt(d2)
        //      c   = p0 × p1               （二维叉积，对应有向面积）
        //
        //    则直线与圆 (center 在原点) 的交点可写成：
        //
        //      x = (c * d_y ± sign(d_y) * d_x * sqrt(delta)) / |d|^2
        //      y = (-c * d_x ± |d_y| * sqrt(delta))          / |d|^2
        //
        //    其中：
        //      - 使用 sign(d_y) 和 |d_y| 可以在 d_y 为负时保持公式数值稳定；
        //      - “±” 对应圆与直线的两处交点；当 delta = 0 时两者重合（相切）。
        const float delta_sqrt = std::sqrt(delta);
        const float sign_dy    = (d.y >= 0.0f) ? 1.0f : -1.0f;

        // 两个候选交点（在“圆心为原点”的坐标系里），i0 / i1 分别对应 “+” / “-” 的解。
        Point2D i0;
        Point2D i1;
        i0.x = (cross * d.y + sign_dy * d.x * delta_sqrt) / d2;
        i1.x = (cross * d.y - sign_dy * d.x * delta_sqrt) / d2;

        const float abs_dy = std::fabs(d.y);

        i0.y = (-cross * d.x + abs_dy * delta_sqrt) / d2;
        i1.y = (-cross * d.x - abs_dy * delta_sqrt) / d2;

        // 判别式为 0 时，两交点重合，相当于相切，此时 i0 == i1。
        // 无论是相交还是相切，统一通过包围盒判断交点是否在线段范围内；
        //   - 若交点在线段延长线上但不在 [p0, p1] 之间，则视为“与线段无交点”。
        if (IsPointOnSegmentBoundingBox(i0, p0c, p1c)) {
            const float angle0      = std::atan2(i0.y, i0.x); // 在以圆心为原点的局部坐标系下
            const float arc_length0 = radius * angle0;
            result.push_back(SegmentCircleIntersection{Point2D(i0.x + center.x, i0.y + center.y), // 平移回原坐标系
                                                       arc_length0});
        }
        if (delta > 0.0f && IsPointOnSegmentBoundingBox(i1, p0c, p1c)) {
            const float angle1      = std::atan2(i1.y, i1.x);
            const float arc_length1 = radius * angle1;
            result.push_back(SegmentCircleIntersection{Point2D(i1.x + center.x, i1.y + center.y), arc_length1});
        }

        return result;
    }

    struct LineIntersection {
        bool    has_intersection = false;
        Point2D point;     // 交点
        float   t1 = 0.0f; // 在第一条线上的参数 t
        float   t2 = 0.0f; // 在第二条线上的参数 u
    };
    enum class LineIntersectionType {
        NO_INTERSECTION,
        SEGMENT_SEGMENT,
        SEGMENT_LINE, // 第 1 条是 segment，第 2 条是 line
        LINE_SEGMENT, // 第 1 条是 line，第 2 条是 segment
        LINE_LINE
    };

    /**
     * @brief 计算两条直线的交点
     * @param p0 第一条直线的起点
     * @param p1 第一条直线的终点
     * @param q0 第二条直线的起点
     * @param q1 第二条直线的终点
     * @return 交点
     */
    static LineIntersection IntersectLinesParametric(const Point2D &p0, const Point2D &p1, const Point2D &q0, const Point2D &q1) {
        LineIntersection res;

        Point2D d1    = p1 - p0;
        Point2D d2    = q1 - q0;
        float   denom = d1.Cross(d2); // d1 × d2

        const float eps = 1e-6f;
        if (std::fabs(denom) <= eps) {
            // 平行或共线：这里统一视为“无唯一交点”
            return res;
        }

        Point2D r(q0.x - p0.x, q0.y - p0.y);
        float   t = r.Cross(d2) / denom; // 在第一条线上的参数
        float   u = r.Cross(d1) / denom; // 在第二条线上的参数

        res.has_intersection = true;
        res.t1               = t;
        res.t2               = u;
        res.point            = Point2D(p0.x + d1.x * t, p0.y + d1.y * t);
        return res;
    };

    static LineIntersectionType GetLineIntersectionType(const LineIntersection &inter, bool first_is_segment, bool second_is_segment) {
        if (!inter.has_intersection) {
            return LineIntersectionType::NO_INTERSECTION;
        }

        bool t1_in = (inter.t1 >= 0.0f && inter.t1 <= 1.0f);
        bool t2_in = (inter.t2 >= 0.0f && inter.t2 <= 1.0f);

        if (first_is_segment && !t1_in)
            return LineIntersectionType::NO_INTERSECTION;
        if (second_is_segment && !t2_in)
            return LineIntersectionType::NO_INTERSECTION;

        if (first_is_segment && second_is_segment)
            return LineIntersectionType::SEGMENT_SEGMENT;
        if (first_is_segment && !second_is_segment)
            return LineIntersectionType::SEGMENT_LINE;
        if (!first_is_segment && second_is_segment)
            return LineIntersectionType::LINE_SEGMENT;
        return LineIntersectionType::LINE_LINE; // 两个都是无限直线
    }

    /**
     * @brief 使用分离轴定理 (SAT) 判断两个凸多边形是否重叠
     * @param poly1 第一个凸多边形
     * @param poly2 第二个凸多边形
     * @return 如果重叠返回 true
     */
    static bool IsPolyOverlapSAT(const Polygon &poly1, const Polygon &poly2) {
        if (poly1.point_list.size() < 3 || poly2.point_list.size() < 3) {
            return false;
        }

        if (CheckSeparatingAxis(poly1, poly2))
            return false;
        if (CheckSeparatingAxis(poly2, poly1))
            return false;

        return true; // 未找到分离轴，发生重叠
    }

  private:
    /**
     * @brief 计算多边形在指定轴上的投影范围
     */
    static std::pair<float, float> GetProjectionRange(const Polygon &poly, const Point2D &axis) {
        float min_p = std::numeric_limits<float>::max();
        float max_p = -std::numeric_limits<float>::max();
        for (const auto &pt : poly.point_list) {
            float proj = pt.Dot(axis);
            min_p      = std::min(min_p, proj);
            max_p      = std::max(max_p, proj);
        }
        return {min_p, max_p};
    }

    /**
     * @brief 检查第一个多边形的每一条边是否是分离轴
     */
    static bool CheckSeparatingAxis(const Polygon &p1, const Polygon &p2) {
        const size_t n = p1.point_list.size();
        for (size_t i = 0; i < n; ++i) {
            const Point2D &v1 = p1.point_list[i];
            const Point2D &v2 = p1.point_list[(i + 1) % n];

            // 计算边的法向量（分离轴）
            Point2D axis(v1.y - v2.y, v2.x - v1.x);

            // 在该轴上投影两个多边形
            std::pair<float, float> range1 = GetProjectionRange(p1, axis);
            std::pair<float, float> range2 = GetProjectionRange(p2, axis);

            // 检查投影是否不重叠
            if (range1.second < range2.first || range2.second < range1.first) {
                return true; // 找到分离轴
            }
        }
        return false;
    }
};

} // namespace math
} // namespace active_safety
