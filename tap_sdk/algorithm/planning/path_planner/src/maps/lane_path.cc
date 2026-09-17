

#include "maps/lane_path.h"

#include <algorithm>
#include <cmath>
#include <memory>
#include <ostream>

#include <absl/strings/str_format.h>
#include <absl/strings/str_join.h>

#include "maps/map_or_die_macros.h"
#include "math/util.h"

namespace pnc_x {
namespace mapping {

std::string LanePath::DebugString() const {
    return IsEmpty()
               ? "Empty lane path."
               : absl::StrFormat(
                     "lane_ids: %s, start_fraction: %7.6f, end_fraction:  "
                     "%7.6f, length: %7.6f.",
                     absl::StrJoin(lane_path_data_.lane_ids(), ", "),
                     start_fraction(), end_fraction(), length());
}

bool LanePath::LaneSegment::HasOverlap(
    const LaneSegment &other,
    std::pair<double, double> *overlap_fraction) const {
    if (lane_id != other.lane_id) return false;

    const double min_fraction = std::max(start_fraction, other.start_fraction);
    const double max_fraction = std::min(end_fraction, other.end_fraction);

    if (max_fraction >= min_fraction) {
        if (overlap_fraction) {
            *overlap_fraction = std::make_pair(min_fraction, max_fraction);
        }
        return true;
    }
    return false;
}

LanePoint LanePath::ArclengthToLanePoint(double s) const {
    const auto lane_index_point = ArclengthToLaneIndexPoint(s);
    return {lane_path_data_.lane_ids()[lane_index_point.first],
            lane_index_point.second};
}

double LanePath::FirstOccurrenceOfLanePointToArclength(LanePoint point) const {
    return LaneIndexPointToArclength(
        FirstOccurrenceOfLanePointToLaneIndexPoint(point));
}

double LanePath::LastOccurrenceOfLanePointToArclength(LanePoint point) const {
    return LaneIndexPointToArclength(
        LastOccurrenceOfLanePointToLaneIndexPoint(point));
}

LanePath::LaneIndexPoint LanePath::FirstOccurrenceOfLanePointToLaneIndexPoint(
    LanePoint point) const {
    LaneIndexPoint lip;
    if (ContainsLanePoint(point, &lip, true)) {
        return lip;
    } else {
        // LOG(FATAL) << "Lane point " << point.DebugString()
        //            << " is not on lane path " << DebugString();
        return lip;
    }
}

LanePath::LaneIndexPoint LanePath::LastOccurrenceOfLanePointToLaneIndexPoint(
    LanePoint point) const {
    LaneIndexPoint lip;
    if (ContainsLanePoint(point, &lip, false)) {
        return lip;
    } else {
        // LOG(FATAL) << "Lane point " << point.DebugString()
        //            << " is not on lane path " << DebugString();
        return lip;
    }
}

int LanePath::ArclengthToLaneIndex(double s) const {
    if (!XCHECK_GE(lane_end_s_.size(), 2)) {
        return 0;
    }
    if (s >= length()) return lane_path_data_.size() - 1;
    if (s <= 0.0) return 0;
    const int index =
        std::upper_bound(lane_end_s_.begin(), lane_end_s_.end(), s) -
        lane_end_s_.begin() - 1;
    XCHECK_GE(index, 0);
    XCHECK_LT(index, lane_path_data_.size());
    return index;
}

double LanePath::LaneIndexToArclength(int lane_index) const {
    if (!XCHECK_LT(lane_index, lane_path_data_.size())) {
        return 0.0;
    }
    return lane_end_s_[lane_index];
}

LanePath::LaneIndexPoint LanePath::ArclengthToLaneIndexPoint(double s) const {
    if (!XCHECK_GE(lane_end_s_.size(), 2)) {
        return {0, lane_path_data_.start_fraction()};
    }
    if (s >= length()) {
        return {lane_path_data_.size() - 1, lane_path_data_.end_fraction()};
    }

    if (s <= 0.0) return {0, lane_path_data_.start_fraction()};
    const int index = ArclengthToLaneIndex(s);
    (void)XCHECK_GE(s, lane_end_s_[static_cast<size_t>(index)]);
    (void)XCHECK_LE(s, lane_end_s_[static_cast<size_t>(index) + 1U]);
    const double lane_fraction = Lerp(
        (index == 0 ? lane_path_data_.start_fraction() : 0.0),
        ((index + 1) == lane_path_data_.size() ? lane_path_data_.end_fraction()
                                               : 1.0),
        LerpFactor(lane_end_s_[static_cast<size_t>(index)], lane_end_s_[static_cast<size_t>(index) + 1U], s));
    (void)XCHECK_GE(lane_fraction, 0.0);
    (void)XCHECK_LE(lane_fraction, 1.0);
    return {index, boost::algorithm::clamp(lane_fraction, 0.0, 1.0)};
}

double LanePath::LaneIndexPointToArclength(int lane_index,
                                           double lane_fraction) const {
    if (!XCHECK_GE(lane_index, 0) ||
        !XCHECK_LT(lane_index, lane_path_data_.size()) ||
        !XCHECK_GE(lane_fraction, 0.0) || !XCHECK_LE(lane_fraction, 1.0)) {
        return 0.0;
    }
    return Lerp(
        lane_end_s_[static_cast<size_t>(lane_index)],
        lane_end_s_[static_cast<size_t>(lane_index) + 1U],
        LerpFactor((lane_index == 0 ? lane_path_data_.start_fraction() : 0.0),
                   ((lane_index + 1) == lane_path_data_.size()
                        ? lane_path_data_.end_fraction()
                        : 1.0),
                   lane_fraction));
}

double LanePath::LaneIndexPointToArclength(
    const LaneIndexPoint &lane_index_point) const {
    return LaneIndexPointToArclength(lane_index_point.first,
                                     lane_index_point.second);
}

bool LanePath::ContainsLanePoint(
    LanePoint point,
    LaneIndexPoint *first_encountered_lane_index_point,
    bool forward_search) const {
    const int size = lane_path_data_.size();
    if (size == 0) return false;
    const int search_start = forward_search ? 0 : (size - 1);
    const int search_end = forward_search ? size : -1;
    const int search_inc = forward_search ? 1 : -1;
    for (int i = search_start; i != search_end; i += search_inc) {
        if (lane_path_data_.lane_ids()[i] != point.lane_id()) continue;
        bool found = false;
        if (size == 1) {
            if ((point.fraction() > (start_fraction() - kEpsilon)) &&
                (point.fraction() < (end_fraction() + kEpsilon))) {
                found = true;
            }

        } else if ((i == 0) &&
                   (point.fraction() >= (start_fraction() - kEpsilon))) {
            found = true;

        } else if (((i + 1) == size) &&
                   (point.fraction() <= (end_fraction() + kEpsilon))) {
            found = true;

        } else if ((i != 0) && ((i + 1) != size)) {
            found = true;
        }
        if (found) {
            if (first_encountered_lane_index_point != nullptr) {
                *first_encountered_lane_index_point = {i, point.fraction()};
            }
            return true;
        }
    }
    return false;
}

LanePath LanePath::BeforeFirstOccurrenceOfLanePoint(LanePoint point) const {
    return BeforeLaneIndexPoint(
        FirstOccurrenceOfLanePointToLaneIndexPoint(point));
}

LanePath LanePath::BeforeLastOccurrenceOfLanePoint(LanePoint point) const {
    return BeforeLaneIndexPoint(
        LastOccurrenceOfLanePointToLaneIndexPoint(point));
}

LanePath LanePath::AfterFirstOccurrenceOfLanePoint(LanePoint point) const {
    return AfterLaneIndexPoint(
        FirstOccurrenceOfLanePointToLaneIndexPoint(point));
}

LanePath LanePath::AfterLastOccurrenceOfLanePoint(LanePoint point) const {
    return AfterLaneIndexPoint(
        LastOccurrenceOfLanePointToLaneIndexPoint(point));
}

LanePath LanePath::BeforeArclength(double s) const {
    return BeforeLaneIndexPoint(ArclengthToLaneIndexPoint(s));
}

LanePath LanePath::AfterArclength(double s) const {
    return AfterLaneIndexPoint(ArclengthToLaneIndexPoint(s));
}

LanePath LanePath::BeforeLaneIndexPoint(int lane_index,
                                        double lane_fraction) const {
    XCHECK_GE(lane_index, 0);
    XCHECK_LT(lane_index, lane_path_data_.size());
    std::vector<ElementId> ids = lane_path_data_.lane_ids();
    ids.erase(ids.begin() + lane_index + 1, ids.end());

    LanePathData lp_data(start_fraction(), lane_fraction, std::move(ids),
                         lane_path_data_.lane_path_in_forward_direction());
    std::vector<double> lane_lengths(lane_lengths_.begin(),
                                     lane_lengths_.begin() + lane_index + 1);
    std::vector<double> lane_end_s(lane_end_s_.begin(),
                                   lane_end_s_.begin() + lane_index + 1);
    lane_end_s.push_back(LaneIndexPointToArclength(lane_index, lane_fraction));
    XCHECK_EQ(lane_end_s.size(), lp_data.size() + 1);

    return LanePath(std::move(lp_data), std::move(lane_end_s),
                    std::move(lane_lengths));
}

LanePath LanePath::AfterLaneIndexPoint(int lane_index,
                                       double lane_fraction) const {
    XCHECK_GE(lane_index, 0);
    XCHECK_LT(lane_index, lane_path_data_.size());
    std::vector<ElementId> ids = lane_path_data_.lane_ids();

    ids.erase(ids.begin(), ids.begin() + lane_index);

    LanePathData lp_data(lane_fraction, end_fraction(), std::move(ids),
                         lane_path_data_.lane_path_in_forward_direction());
    std::vector<double> lane_lengths(lane_lengths_.begin() + lane_index,
                                     lane_lengths_.end());
    std::vector<double> lane_end_s;
    lane_end_s.reserve(lp_data.size() + 1);
    lane_end_s.push_back(0.0);
    const double length = LaneIndexPointToArclength(lane_index, lane_fraction);
    for (int i = lane_index + 1; i < lane_end_s_.size(); ++i) {
        lane_end_s.push_back(lane_end_s_[i] - length);
    }

    XCHECK_EQ(lane_end_s.size(), lp_data.size() + 1);
    return LanePath(std::move(lp_data), std::move(lane_end_s),
                    std::move(lane_lengths));
}

LanePath LanePath::BeforeLaneIndexPoint(
    const LaneIndexPoint &lane_index_pt) const {
    return BeforeLaneIndexPoint(lane_index_pt.first, lane_index_pt.second);
}

LanePath LanePath::AfterLaneIndexPoint(
    const LaneIndexPoint &lane_index_pt) const {
    return AfterLaneIndexPoint(lane_index_pt.first, lane_index_pt.second);
}

LanePath::LanePath(LanePathData lane_path_data,
                   std::vector<double> lane_end_s,
                   std::vector<double> lane_lengths)
    : lane_path_data_(std::move(lane_path_data)),
      lane_end_s_(std::move(lane_end_s)),
      lane_lengths_(std::move(lane_lengths)) {}

const LanePathData &LanePath::lane_path_data() const { return lane_path_data_; }

const ads_x::planning::LaneSequencePtr &LanePath::lane_seq() const {
    return lane_seq_;
}

void LanePath::set_lane_seq(const ads_x::planning::LaneSequencePtr &lane_seq) {
    lane_seq_ = lane_seq;
}

int LanePath::size() const { return lane_path_data_.size(); }
int LanePath::lane_ids_size() const { return lane_path_data_.size(); }

bool LanePath::IsEmpty() const { return lane_path_data_.empty(); }
bool LanePath::IsEqual(const LanePath &other) const {
    return lane_path_data_ == other.lane_path_data();
}
bool LanePath::operator==(const LanePath &other) const {
    return IsEqual(other);
}
bool LanePath::operator!=(const LanePath &other) const {
    return !IsEqual(other);
}

const std::vector<ElementId> &LanePath::lane_ids() const {
    return lane_path_data_.lane_ids();
}

ElementId LanePath::lane_id(int i) const { return lane_path_data_.lane_id(static_cast<size_t>(i)); }
double LanePath::start_fraction() const {
    return lane_path_data_.start_fraction();
}
double LanePath::end_fraction() const { return lane_path_data_.end_fraction(); }
double LanePath::start_s(int i) const { return lane_end_s_[static_cast<size_t>(i)]; }
double LanePath::end_s(int i) const { return lane_end_s_[static_cast<size_t>(i) + 1U]; }

LanePoint LanePath::front() const { return lane_path_data_.start_point(); }
LanePoint LanePath::back() const { return lane_path_data_.end_point(); }

double LanePath::length() const {
    if (!XCHECK(!lane_end_s_.empty())) {
        return 0.0;
    }
    return lane_end_s_.back();
}

LanePath::LaneSegment::LaneSegment(int lane_index,
                                   mapping::ElementId lane_id,
                                   double start_fraction,
                                   double end_fraction,
                                   double start_s,
                                   double end_s)
    : lane_index(lane_index),
      lane_id(lane_id),
      start_fraction(start_fraction),
      end_fraction(end_fraction),
      start_s(start_s),
      end_s(end_s) {}

double LanePath::LaneSegment::length() const { return end_s - start_s; }

LanePath::LaneSegmentIterator::LaneSegmentIterator(const LanePath *lane_path,
                                                   int lane_index)
    : lane_path_(*XCHECK_NOTNULL(lane_path)), lane_index_(lane_index) {}

const LanePath &LanePath::LaneSegmentIterator::lane_path() const {
    return lane_path_;
}
int LanePath::LaneSegmentIterator::lane_index() const { return lane_index_; }

LanePath::LaneSegment LanePath::LaneSegmentIterator::operator*() const {
    return lane_path_.lane_segment(lane_index_);
}

LanePath::LaneSegmentIterator &LanePath::LaneSegmentIterator::operator=(
    const LanePath::LaneSegmentIterator &other) {
    XCHECK(lane_path_ == other.lane_path_);
    lane_index_ = other.lane_index_;
    return *this;
}

bool LanePath::LaneSegmentIterator::operator==(
    const LanePath::LaneSegmentIterator &other) const {
    XCHECK(lane_path_ == other.lane_path_);
    return lane_index_ == other.lane_index_;
}
bool LanePath::LaneSegmentIterator::operator!=(
    const LanePath::LaneSegmentIterator &other) const {
    XCHECK(lane_path_ == other.lane_path_);
    return !(*this == other);
}
bool LanePath::LaneSegmentIterator::operator<(
    const LanePath::LaneSegmentIterator &other) const {
    XCHECK(lane_path_ == other.lane_path_);
    return lane_index_ < other.lane_index_;
}

LanePath::LaneSegmentIterator LanePath::LaneSegmentIterator::operator+(
    int inc) const {
    const int new_lane_index = lane_index_ + inc;
    XCHECK_GE(new_lane_index, 0);
    XCHECK_LE(new_lane_index, lane_path_.size());
    return LanePath::LaneSegmentIterator(&lane_path_, new_lane_index);
}
LanePath::LaneSegmentIterator LanePath::LaneSegmentIterator::operator-(
    int inc) const {
    const int new_lane_index = lane_index_ - inc;
    XCHECK_GE(new_lane_index, 0);
    XCHECK_LE(new_lane_index, lane_path_.size());
    return LanePath::LaneSegmentIterator(&lane_path_, new_lane_index);
}
int LanePath::LaneSegmentIterator::operator-(
    const LaneSegmentIterator &other) const {
    XCHECK(lane_path_ == other.lane_path_);
    return lane_index_ - other.lane_index_;
}

LanePath::LaneSegmentIterator LanePath::LaneSegmentIterator::operator++() {
    XCHECK_LT(lane_index_, lane_path_.size());
    const LanePath::LaneSegmentIterator old_it = *this;
    lane_index_++;
    return old_it;
}
const LanePath::LaneSegmentIterator &LanePath::LaneSegmentIterator::operator++(
    int) {
    XCHECK_LT(lane_index_, lane_path_.size());
    ++lane_index_;
    return *this;
}
LanePath::LaneSegmentIterator LanePath::LaneSegmentIterator::operator--() {
    XCHECK_GT(lane_index_, 0);
    const LanePath::LaneSegmentIterator old_it = *this;
    lane_index_--;
    return old_it;
}
const LanePath::LaneSegmentIterator &LanePath::LaneSegmentIterator::operator--(
    int) {
    XCHECK_GT(lane_index_, 0);
    --lane_index_;
    return *this;
}

LanePath::LaneSegmentIterator LanePath::begin() const {
    return LanePath::LaneSegmentIterator(this, 0);
}
LanePath::LaneSegmentIterator LanePath::end() const {
    return LanePath::LaneSegmentIterator(this, size());
}

LanePath::LaneSegmentIterator LanePath::GetIteratorAt(int lane_index) const {
    return LanePath::LaneSegmentIterator(this, lane_index);
}

LanePath::LaneSegment LanePath::lane_segment(int lane_index) const {
    XCHECK_GE(lane_index, 0);
    XCHECK_LT(lane_index, size());
    return {lane_index,
            lane_id(lane_index),
            (lane_index == 0 ? start_fraction() : 0.0),
            ((lane_index + 1) == size() ? end_fraction() : 1.0),
            lane_end_s_[static_cast<size_t>(lane_index)],
            lane_end_s_[static_cast<size_t>(lane_index) + 1U]};
}

LanePath::LaneSegmentIterator LanePath::LaneIndexPointToLaneSegmentIterator(
    LaneIndexPoint lane_index_point) const {
    return LanePath::LaneSegmentIterator(this, lane_index_point.first);
}

}  // namespace mapping
}  // namespace pnc_x
