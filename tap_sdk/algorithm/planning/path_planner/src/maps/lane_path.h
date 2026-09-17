
#pragma once

#include <string>
#include <utility>
#include <vector>

#include "common/log.h"

#include "pncx_lane_path.pb.h"
#include "maps/lane_path_data.h"
#include "maps/lane_point.h"
#include "maps/lane_sequence.h"
#include "maps/semantic_map_defs.h"

namespace pnc_x {
namespace mapping {

constexpr double kEpsilon = 1e-6;

class LanePath {
 public:
    LanePath() = default;

    LanePath(LanePathData lane_path_data,
             std::vector<double> lane_end_s,
             std::vector<double> lane_lengths);

    const LanePathData &lane_path_data() const;

    const ads_x::planning::LaneSequencePtr &lane_seq() const;

    void set_lane_seq(const ads_x::planning::LaneSequencePtr &lane_seq);

    int size() const;
    int lane_ids_size() const;

    bool IsEmpty() const;
    bool IsEqual(const LanePath &other) const;
    bool operator==(const LanePath &other) const;
    bool operator!=(const LanePath &other) const;

    const std::vector<ElementId> &lane_ids() const;

    ElementId lane_id(int i) const;
    double start_fraction() const;
    double end_fraction() const;
    double start_s(int i) const;
    double end_s(int i) const;

    std::string DebugString() const;

    LanePoint front() const;
    LanePoint back() const;

    double length() const;

    struct LaneSegment {
        int lane_index;
        mapping::ElementId lane_id;
        double start_fraction;
        double end_fraction;
        double start_s;
        double end_s;

        LaneSegment(int lane_index,
                    mapping::ElementId lane_id,
                    double start_fraction,
                    double end_fraction,
                    double start_s,
                    double end_s);

        double length() const;

        bool HasOverlap(
            const LaneSegment &other,
            std::pair<double, double> *overlap_fraction = nullptr) const;
    };

    class LaneSegmentIterator {
     public:
        explicit LaneSegmentIterator(const LanePath *lane_path,
                                     int lane_index = 0);

        const LanePath &lane_path() const;
        int lane_index() const;

        LaneSegment operator*() const;

        LaneSegmentIterator &operator=(const LaneSegmentIterator &other);

        bool operator==(const LaneSegmentIterator &other) const;
        bool operator!=(const LaneSegmentIterator &other) const;
        bool operator<(const LaneSegmentIterator &other) const;

        LaneSegmentIterator operator+(int inc) const;
        LaneSegmentIterator operator-(int inc) const;
        int operator-(const LaneSegmentIterator &other) const;

        LaneSegmentIterator operator++();
        const LaneSegmentIterator &operator++(int);
        LaneSegmentIterator operator--();
        const LaneSegmentIterator &operator--(int);

     private:
        const LanePath &lane_path_;
        int lane_index_;
    };

    LaneSegmentIterator begin() const;
    LaneSegmentIterator end() const;

    LaneSegmentIterator GetIteratorAt(int lane_index) const;

    LaneSegment lane_segment(int lane_index) const;

    using LaneIndexPoint = std::pair<int, double>;

    LanePoint ArclengthToLanePoint(double s) const;
    double FirstOccurrenceOfLanePointToArclength(LanePoint point) const;
    double LastOccurrenceOfLanePointToArclength(LanePoint point) const;
    LaneIndexPoint FirstOccurrenceOfLanePointToLaneIndexPoint(
        LanePoint point) const;
    LaneIndexPoint LastOccurrenceOfLanePointToLaneIndexPoint(
        LanePoint point) const;
    int ArclengthToLaneIndex(double s) const;
    double LaneIndexToArclength(int lane_index) const;
    LaneIndexPoint ArclengthToLaneIndexPoint(double s) const;
    double LaneIndexPointToArclength(int lane_index,
                                     double lane_fraction) const;
    double LaneIndexPointToArclength(
        const LaneIndexPoint &lane_index_point) const;

    LaneSegmentIterator LaneIndexPointToLaneSegmentIterator(
        LaneIndexPoint lane_index_point) const;

    bool ContainsLanePoint(
        LanePoint point,
        LaneIndexPoint *first_encountered_lane_index_point = nullptr,
        bool forward_search = true) const;

    LanePath BeforeFirstOccurrenceOfLanePoint(LanePoint point) const;
    LanePath BeforeLastOccurrenceOfLanePoint(LanePoint point) const;
    LanePath AfterFirstOccurrenceOfLanePoint(LanePoint point) const;
    LanePath AfterLastOccurrenceOfLanePoint(LanePoint point) const;
    LanePath BeforeArclength(double s) const;
    LanePath AfterArclength(double s) const;
    LanePath BeforeLaneIndexPoint(int lane_index, double lane_fraction) const;
    LanePath AfterLaneIndexPoint(int lane_index, double lane_fraction) const;
    LanePath BeforeLaneIndexPoint(const LaneIndexPoint &lane_index_point) const;
    LanePath AfterLaneIndexPoint(const LaneIndexPoint &lane_index_point) const;

 private:
    LanePathData lane_path_data_;
    std::vector<double> lane_end_s_;
    std::vector<double> lane_lengths_;
    ads_x::planning::LaneSequencePtr lane_seq_;
};

}  // namespace mapping
}  // namespace pnc_x
