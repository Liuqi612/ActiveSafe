/*
* Copyright (C) 2025 by SenseTime Group Limited. All rights reserved.
*/

#include "boost_geometry_common.hpp"
#include <iostream>

namespace senseAD {
namespace planning_pilot {

void DebugBgElement(const std::vector<std::vector<BgPoint>>& trajectories) {
    for (size_t i = 0UL; i < trajectories.size(); ++i) {
        std::stringstream ss_x;
        ss_x << "\n" << "traj_" << i << "_x =[";
        std::stringstream ss_y;
        ss_y << "\n" << "traj_" << i << "_y =[";
        for (const auto& p : trajectories[i]) {
            ss_x << p.x() << ",";
            ss_y << p.y() << ",";
        }
        ss_x << "]\n";
        ss_y << "]\n";

        std::cout << ss_x.str();
        std::cout << ss_y.str();
    }
}

void DebugBgElement(std::stringstream& o, const BgPoint& p) {
    o << "\n" << "point_x="<< "[" << p.x() << "]"
    << "\n" << "point_y="<< "[" << p.y() << "]";
    o << "\n";
}

void DebugBgElement(std::stringstream& o, const BgSegment& s) {
    o << "\n" << "segment_x="<< "[" << s.first.x() << "," << s.second.x() << "]"
    << "\n" << "segment_y="<< "[" << s.first.y() << "," << s.second.y() << "]";
    o << "\n";
}

void DebugBgElement(std::stringstream& o, const BgLineString& l) {
    o << "\n" << "linestring_x="<< "[";
    for (const auto& p : l) {
        o << p.x() << ",";
    }
    o << "]";
    o << "\n" << "linestring_" << "_y="<< "[";
    for (const auto& p : l) {
        o << p.y() << ",";
    }
    o << "]" << "\n";
}

void DebugBgElement(std::stringstream& o, const BgBox& b) {
    const auto& min_corner = b.min_corner();
    const auto& max_corner = b.max_corner();

    double x_min = min_corner.x();
    double y_min = min_corner.y();
    double x_max = max_corner.x();
    double y_max = max_corner.y();
    o << "\n" << "box_x_0="<< "["
    << x_min << ","
    << x_max << "]";
    o << "\n" << "box_x_1="<< "["
    << x_max << ","
    << x_max << "]";
    o << "\n" << "box_x_2="<< "["
    << x_max << ","
    << x_min << "]";
    o << "\n" << "box_x_3="<< "["
    << x_min << ","
    << x_min << "]";

    o << "\n" << "box_x_0="<< "["
    << y_min << ","
    << y_min << "]";
    o << "\n" << "box_x_1="<< "["
    << y_min << ","
    << y_max << "]";
    o << "\n" << "box_x_2="<< "["
    << y_max << ","
    << y_max << "]";
    o << "\n" << "box_x_3="<< "["
    << y_max << ","
    << y_min << "]";
    o << "\n";
}

void DebugBgElement(std::stringstream& o, const BgPolygon& p) {
    if (p.outer().size() < 2UL) {
        o << "p.outer().size() < 2 \n";
        return;
    }
    for (size_t i = 1UL; i < p.outer().size(); ++i) {
        o << "\n" << "polygon_x_" << (i - 1UL) << "="<< "["
        << p.outer()[i - 1UL].x() << ","
        << p.outer()[i].x() << "]";
        o << "\n" << "polygon_y_" << (i - 1UL) << "="<< "["
        << p.outer()[i - 1UL].y() << ","
        << p.outer()[i].y() << "]";
    }
    o << "\n";
}

void DebugBgElement(std::stringstream& o, const RTree& t) {
    std::map<std::string, std::pair<std::string, std::string>> seg_debug_string_map;
    size_t index = 0UL;
    for (auto it = t.begin(); it != t.end(); ++it, ++index) {
        const auto& seg = *it;
        const auto& p1 = seg.first.first;
        const auto& p2 = seg.first.second;
        const auto id = std::to_string(seg.second) + "_" + std::to_string(index);
        std::stringstream x_ss;
        x_ss << p1.x() << "," << p2.x() << ",";
        std::stringstream y_ss;
        y_ss << p1.y() << "," << p2.y() << ",";
        seg_debug_string_map[id] = {x_ss.str(), y_ss.str()};
    }
    
    o << "\n";
    for (const auto& m : seg_debug_string_map) {
        o << "rtree_x_" << m.first << "="<< "[" << m.second.first << "]\n";
        o << "rtree_y_" << m.first << "="<< "[" << m.second.second << "]\n";
    }
    o << "\n";
}

} // namespace planning_pilot
} // namespace senseAD


