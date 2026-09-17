/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#pragma once
#include <Eigen/Dense>
#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
#include "math/utils/util_math.h"
#include "math/geometry/geometry.h"
namespace senseAD {
namespace tap_newtsel {

// Use the standard Point2D from active_safety::math
using Point2D = active_safety::math::Point2D;

struct Box2D {
 public:
  void BuildFromCenter(float center_x, float center_y, float heading_rad,
                       float length, float width) noexcept {
    const float cos_theta = std::cos(heading_rad);
    const float sin_theta = std::sin(heading_rad);

    const float half_len = length * 0.5f;
    const float half_wid = width * 0.5f;

    const float dx1 = -half_len * cos_theta;
    const float dy1 = -half_len * sin_theta;
    const float dx2 = half_wid * sin_theta;
    const float dy2 = -half_wid * cos_theta;

    left_top.x = center_x + dx1 - dx2;
    left_top.y = center_y + dy1 - dy2;
    right_top.x = center_x + dx1 + dx2;
    right_top.y = center_y + dy1 + dy2;
    left_bottom.x = center_x - dx1 - dx2;
    left_bottom.y = center_y - dy1 - dy2;
    right_bottom.x = center_x - dx1 + dx2;
    right_bottom.y = center_y - dy1 + dy2;

    ComputeAABB();
  }
  // AABB judge if collision, true means not collision
  bool QuickRejectTest(const Box2D &other) {
    return min_x > other.max_x || max_x < other.min_x || min_y > other.max_y ||
           max_y < other.min_y;
  }
  bool IsPointInsidePolygon(const Eigen::Vector2f &pt) {
    // 简单判断点是否在垂直的矩形内
    //  将点视为一个极小的Box
    Box2D pointBox;
    pointBox.BuildFromCenter(pt.x(), pt.y(), 0.0f, 0.001f,
                             0.001f);  // 微小尺寸避免浮点误差

    // 用SAT检测碰撞
    return IsCollisionSAT(pointBox);
  }
  bool IsCollisionSAT(const Box2D &other) {
    // or judge if collision with SAT
    return !(CheckAxis(left_top, right_top, other) ||
             CheckAxis(left_top, left_bottom, other) ||
             other.CheckAxis(other.left_top, other.right_top, *this) ||
             other.CheckAxis(other.left_top, other.left_bottom, *this));
  }
  // 并行计算AABB极值
  void ComputeAABB() noexcept {
    float x[4] = {left_top.x, right_top.x, left_bottom.x, right_bottom.x};
    float y[4] = {left_top.y, right_top.y, left_bottom.y, right_bottom.y};

    min_x = max_x = x[0];
    min_y = max_y = y[0];

    min_x = std::min(std::min(x[0], x[1]), std::min(x[2], x[3]));
    max_x = std::max(std::max(x[0], x[1]), std::max(x[2], x[3]));
    min_y = std::min(std::min(y[0], y[1]), std::min(y[2], y[3]));
    max_y = std::max(std::max(y[0], y[1]), std::max(y[2], y[3]));
  }

 public:
  //
  Point2D left_top, right_top, left_bottom, right_bottom;

 private:
  float min_x, max_x, min_y, max_y;

  float Project(const Point2D &axis, const Point2D &p) const noexcept {
    return axis.x * p.x + axis.y * p.y;
  }

  void ProjectMax(const Point2D &axis, const Point2D &p0, const Point2D &p1,
                  const Point2D &p2, const Point2D &p3, float &max,
                  float &min) const noexcept {
    const float d0 = Project(axis, p0);
    const float d1 = Project(axis, p1);
    const float d2 = Project(axis, p2);
    const float d3 = Project(axis, p3);
    max = std::max(std::max(d0, d1), std::max(d2, d3));
    min = std::min(std::min(d0, d1), std::min(d2, d3));
  }

  bool CheckAxis(Point2D p1, Point2D p2, const Box2D &other) const noexcept {
    const Point2D axis = {p2.y - p1.y, p1.x - p2.x};
    float min1, max1;
    ProjectMax(axis, left_top, left_bottom, right_top, right_bottom, max1,
               min1);
    float min2, max2;
    other.ProjectMax(axis, other.right_top, other.left_bottom,
                     other.right_bottom, other.left_top, max2, min2);
    return (min1 >= max2) || (min2 >= max1);
  }
};

}  // namespace tap_newtsel
}  // namespace senseAD
