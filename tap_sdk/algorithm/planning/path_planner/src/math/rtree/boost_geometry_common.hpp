/*
* Copyright (C) 2025 by SenseTime Group Limited. All rights reserved.
*/

#pragma once
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <sstream>
#include <ostream>

namespace senseAD {
namespace planning_pilot {

namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

// using BgPoint = bg::model::point<double, 2, bg::cs::cartesian>;
using BgPoint = bg::model::d2::point_xy<float>;
using BgSegment = bg::model::segment<BgPoint>;
using BgLineString = bg::model::linestring<BgPoint>;
using BgBox = bg::model::box<BgPoint>;
using BgPolygon = bg::model::polygon<BgPoint>;
using PointI = std::pair<BgPoint, int>;
using SegmentI = std::pair<BgSegment, int>;
using RTree = bgi::rtree<SegmentI, bgi::rstar<16UL>>;
using RTreePtr = std::shared_ptr<RTree>;

void DebugBgElement(const std::vector<std::vector<BgPoint>>& trajectories);
void DebugBgElement(std::stringstream& o, const BgPoint& p);
void DebugBgElement(std::stringstream& o, const BgSegment& s);
void DebugBgElement(std::stringstream& o, const BgLineString& l);
void DebugBgElement(std::stringstream& o, const BgBox& b);
void DebugBgElement(std::stringstream& o, const BgPolygon& p);
void DebugBgElement(std::stringstream& o, const RTree& t);

template<typename XY>
inline BgPoint BGPoint(const XY& xy) {
    return BgPoint(xy.x, xy.y);
}

template<typename XY>
inline std::vector<BgSegment> BgSegments(const std::vector<XY>& traj) {
    std::vector<BgSegment> segments;
    if (traj.size() < 2) {
        return segments;
    }

    segments.reserve(traj.size() - 1);
    for (size_t i = 1UL; i < traj.size(); ++i) {
        segments.emplace_back(BgPoint(traj[i-1UL]), BgPoint(traj[i]));
    }
    return segments;
}

} // namespace planning_pilot
} // namespace senseAD


