
#pragma once

#include <optional>
#include <set>
#include <utility>
#include <vector>
#include <boost/geometry.hpp>

#include "pncx_geometry.pb.h"
#include "path_planner/src/math/vec.h"

namespace boost {
namespace geometry {
namespace traits {

template <typename T>
struct radius {};

template <typename T>
struct tag<pnc_x::Vec3<T>> {
    using type = point_tag;
};
template <typename T>
struct tag<boost::geometry::model::linestring<pnc_x::Vec3<T>>> {
    using type = linestring_tag;
};
template <typename T>
struct dimension<pnc_x::Vec3<T>> : boost::mpl::int_<3> {};
template <typename T>
struct coordinate_type<pnc_x::Vec3<T>> {
    using type = T;
};
template <typename T>
struct coordinate_system<pnc_x::Vec3<T>> {
    using type = boost::geometry::cs::cartesian;
};

template <typename T, std::size_t Index>
struct access<pnc_x::Vec3<T>, Index> {
    static_assert(Index < 3, "Out of range");
    using Point = pnc_x::Vec3<T>;
    using CoordinateType = typename coordinate_type<Point>::type;
    static CoordinateType get(const Point &p) { return p[Index]; }
    static void set(Point &p, const CoordinateType &value) { p[Index] = value; }
};

template <typename T>
struct tag<pnc_x::Vec2<T>> {
    using type = point_tag;
};
template <typename T>
struct dimension<pnc_x::Vec2<T>> : boost::mpl::int_<2> {};
template <typename T>
struct coordinate_type<pnc_x::Vec2<T>> {
    using type = T;
};
template <typename T>
struct coordinate_system<pnc_x::Vec2<T>> {
    using type = boost::geometry::cs::cartesian;
};

template <typename T, std::size_t Index>
struct access<pnc_x::Vec2<T>, Index> {
    static_assert(Index < 2, "Out of range");
    using Point = pnc_x::Vec2<T>;
    using CoordinateType = typename coordinate_type<Point>::type;
    static CoordinateType get(const Point &p) { return p[Index]; }
    static void set(Point &p, const CoordinateType &value) { p[Index] = value; }
};

template <>
struct tag<pnc_x::mapping::GeoPointProto> {
    using type = point_tag;
};
template <>
struct dimension<pnc_x::mapping::GeoPointProto> : boost::mpl::int_<2> {};
template <>
struct coordinate_type<pnc_x::mapping::GeoPointProto> {
    using type = double;
};
template <>
struct coordinate_system<pnc_x::mapping::GeoPointProto> {
    using type = boost::geometry::cs::geographic<boost::geometry::radian>;
};

template <std::size_t Index>
struct access<pnc_x::mapping::GeoPointProto, Index> {
    static_assert(Index < 2, "Out of range");
    using Point = pnc_x::mapping::GeoPointProto;
    using CoordinateType = typename coordinate_type<Point>::type;
    static CoordinateType get(const Point &p) {
        switch (Index) {
            case 0:
                return p.longitude();
            case 1:
                return p.latitude();
        }
        return 0;
    }
    static void set(Point &p, const CoordinateType &value) {
        switch (Index) {
            case 0:
                p.set_longitude(value);
                break;
            case 1:
                p.set_latitude(value);
                break;
        }
    }
};
template <typename T>
struct radius<pnc_x::Vec2<T>> {
    static double convert(double radius_meter) { return radius_meter; }
};
template <typename T>
struct radius<pnc_x::Vec3<T>> {
    static double convert(double radius_meter) { return radius_meter; }
};
template <>
struct radius<pnc_x::mapping::GeoPointProto> {
    static double convert(double radius_meter) {
        constexpr double kMeterPerRadianOnEquator = 6371000.0;
        return radius_meter * (1.0 / kMeterPerRadianOnEquator);
    }
};

}  // namespace traits
}  // namespace geometry
}  // namespace boost

namespace pnc_x {
namespace rtree {
namespace bg = boost::geometry;
namespace bgi = boost::geometry::index;

template <typename Value, typename Point = Vec3d>
class PointRTree {
 public:
    using Index = std::pair<Point, Value>;
    void AddPoint(const Point &point, const Value value) {
        rtree_.insert(std::make_pair(point, value));
    }
    void Remove(const Index &index) { rtree_.remove(index); }
    boost::optional<Index> GetNearest(const Point &point) const {
        auto result = GetNearestN(point, 1);
        if (result.empty()) return boost::none;
        return boost::optional(result.front());
    }
    std::vector<Index> GetNearestN(const Point &point, int n) const {
        std::vector<Index> result;
        result.reserve(n);
        rtree_.query(bgi::nearest(point, n), std::back_inserter(result));
        return result;
    }
    std::size_t size() const { return rtree_.size(); }

 private:
    bgi::rtree<Index, bgi::quadratic<16>> rtree_;
};

template <typename Value, typename PointT = Vec3d>
class RTree {
 public:
    using value_type = Value;
    using Point = PointT;
    using LineString = bg::model::linestring<Point>;
    using Polygon = bg::model::polygon<Point>;
    using Box = bg::model::box<Point>;
    using Index = std::pair<Box, Value>;
    Index AddPoint(const Point &point, const Value value) {
        auto index = std::make_pair(bg::return_envelope<Box>(point), value);
        rtree_.insert(index);
        return index;
    }
    template <typename Container>
    Index AddLineString(const Container &line_points,
                        const Value value,
                        LineString *line = nullptr) {
        LineString local_line;
        if (line == nullptr) line = &local_line;
        line->clear();
        for (const auto &point : line_points) bg::append(*line, point);
        auto index = std::make_pair(bg::return_envelope<Box>(*line), value);
        rtree_.insert(index);
        return index;
    }
    template <typename Container>
    Index AddPolygon(const Container &polygon_points,
                     const Value value,
                     Polygon *poly = nullptr) {
        Polygon local_poly;
        if (poly == nullptr) poly = &local_poly;
        poly->clear();
        for (const auto &point : polygon_points) bg::append(*poly, point);
        auto index = std::make_pair(bg::return_envelope<Box>(*poly), value);
        rtree_.insert(index);
        return index;
    }
    void Remove(const Index &index) { rtree_.remove(index); }

    boost::optional<Index> GetNearestBBox(const Point &point) const {
        auto result = GetNearestBBoxN(point, 1);
        if (result.empty()) return boost::none;
        return boost::optional(result.front());
    }
    std::vector<Index> GetNearestBBoxN(const Point &point, int n) const {
        std::vector<Index> result;
        rtree_.query(bgi::nearest(point, n), std::back_inserter(result));
        return result;
    }

    std::vector<Index> GetBBoxUnderPoint(const Point &point) const {
        std::vector<Index> ret;
        rtree_.query(bgi::intersects(point), std::back_inserter(ret));
        return ret;
    }

    std::vector<Index> GetIntersectingBBox(Point center,
                                           double radius_meter) const {
        double radius = bg::traits::radius<Point>::convert(radius_meter);

        Point max_corner;
        double x = bg::get<0>(center);
        double y = bg::get<1>(center);
        bg::set<0>(max_corner, x + radius);
        bg::set<1>(max_corner, y + radius);

        bg::set<0>(center, x - radius);
        bg::set<1>(center, y - radius);
        return GetIntersectingBBox(center, max_corner);
    }

    std::vector<Index> GetIntersectingBBox(Point point1, Point point2) const {
        double x1 = bg::get<0>(point1);
        double x2 = bg::get<0>(point2);
        double y1 = bg::get<1>(point1);
        double y2 = bg::get<1>(point2);
        if (x1 > x2) {
            bg::set<0>(point1, x2);
            bg::set<0>(point2, x1);
        }
        if (y1 > y2) {
            bg::set<1>(point1, y2);
            bg::set<1>(point2, y1);
        }
        Box box(point1, point2);

        return GetIntersectingBBox(box);
    }
    std::vector<Index> GetIntersectingBBox(const Box &box) const {
        std::vector<Index> ret;
        rtree_.query(bgi::intersects(box), std::back_inserter(ret));
        return ret;
    }
    std::size_t size() const { return rtree_.size(); }

 private:
    bgi::rtree<Index, bgi::quadratic<16>> rtree_;
};
}  // namespace rtree
}  // namespace pnc_x
