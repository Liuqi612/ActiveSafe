
#pragma once

#include <vector>

#include "path_planner/src/math/geometry/aabox2d.h"
#include "path_planner/src/math/vec.h"

namespace pnc_x {

class Polyline2d {
 public:
    Polyline2d() = delete;
    explicit Polyline2d(std::vector<Vec2d> points);
    Polyline2d(std::vector<Vec2d> points, std::vector<double> point_s);

    double length() const { return point_s_.back(); }

    const std::vector<Vec2d> &points() const { return points_; }
    const std::vector<double> &point_s() const { return point_s_; }

    AABox2d aabb() const { return aabb_; }

    Vec2d Sample(double s) const;

    std::vector<Vec2d> Sample(const std::vector<double> &s) const;

    Vec2d SampleTangent(double s) const;

    std::vector<Vec2d> SampleTangent(const std::vector<double> &s) const;

    int GetSegmentIndexFromS(double s) const;

 protected:
    std::vector<Vec2d> points_;
    std::vector<double> point_s_;

    AABox2d aabb_;
};

class SampledPolyline2d : public Polyline2d {
 public:
    SampledPolyline2d() = delete;
    SampledPolyline2d(std::vector<Vec2d> points, double interval);
    SampledPolyline2d(std::vector<Vec2d> points,
                      std::vector<double> point_s,
                      double interval);

    const std::vector<Vec2d> &samples() const { return samples_; }
    const std::vector<double> &sample_s() const { return sample_s_; }
    const std::vector<Vec2d> &tangents() const { return tangents_; }

    int GetSampleSegmentIndexFromS(double s) const;

 protected:
    void BuildSamples();

    std::vector<Vec2d> samples_;
    std::vector<double> sample_s_;
    std::vector<Vec2d> tangents_;

    double interval_;
};

}  // namespace pnc_x
