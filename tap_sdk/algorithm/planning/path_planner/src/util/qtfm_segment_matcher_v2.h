
#pragma once

#include <algorithm>
#include <array>
#include <boost/optional.hpp>
#include <string>
#include <utility>
#include <vector>

#include <sys/types.h>

#include "math/geometry/aabox2d.h"
#include "math/geometry/grid_frame.h"
#include "math/geometry/segment2d.h"
#include "math/vec.h"
#include "util/quad_tree_field_map.h"
#include "common/log.h"

namespace pnc_x {
namespace planning {

class QtfmSegmentMatcherV2 {
 public:
    static constexpr double kMinSegmentLength = 1e-5;
    static constexpr double kLengthEpsilon = 1e-6;
    static constexpr double kMaxSameDirCrossProdError = 1e-6;
    struct Config {
        double x_min = 0.0;
        double x_max = 0.0;
        double y_min = 0.0;
        double y_max = 0.0;

        double resolution = 0.0;

        int qtfm_depth = 1;

        int cutoff_num_range = 1;
        int cutoff_max_num_candidate = 16;

        double cutoff_distance = 0.0;

        bool IsValid() const;

        std::string DebugStringFullPrecision() const;
    };

    QtfmSegmentMatcherV2(Config config,
                         std::vector<Segment2d> raw_segments,
                         std::vector<int> raw_start_segment_ids);

    bool GetNearestSegmentIndex(double x, double y, int *index) const;

    QtfmSegmentMatcherV2(const QtfmSegmentMatcherV2 &other);
    QtfmSegmentMatcherV2 &operator=(const QtfmSegmentMatcherV2 &other);

    const Config &config() const;

    std::string DebugStringFullPrecision() const;

 private:
    static constexpr double kCutoffComplexity = 2.0;
    static constexpr double kCutoff = 1.0;
    static constexpr double kKeepDivide = 3.0;
    using Range = std::pair<int, int>;
    using Bool = u_char;

    struct IdField {
        int range_id_begin;
        int range_id_end;

        QtfmSegmentMatcherV2 *matcher_ptr = nullptr;
        bool is_simple_enough = false;

        double Complexity() const;

        void SuperPose(const IdField &other);

        void Simplify(const AABox2d &box);

        constexpr bool IsVoid() const;

        constexpr int size() const;
    };

    bool IsFieldValid(const IdField &field) const;

    std::string FieldDebugString(const IdField &field) const;

    void StitchField(const AABox2d &box, IdField *field);

    void PurgeField(const AABox2d &box, IdField *field);

    void ClampField(const AABox2d &box, IdField *field);

    void DownClampRange(const std::array<Vec2d, 4> &box_points,
                        Range *range) const;

    void UpClampRange(const std::array<Vec2d, 4> &box_points,
                      Range *range) const;

    constexpr int GetNearestSegmentIndexFromRange(const Vec2d &point,
                                                  const Range &range) const;

    void SuperposeField(const IdField &other, IdField *field);

    bool IsFieldSimpleEnough(const IdField &field) const;

    IdField CreateIdFieldFromSortedVector(
        const std::vector<int> &sorted_segment_ids);

    constexpr int GridIndexToVectorIndex(int xid, int yid) const;

    void CalculateGridsAffectedBySegment(
        int segment_id, std::vector<std::pair<int, int>> *result);

    static bool IsDivisible(const Segment2d &prev_seg,
                            const Segment2d &cur_seg);

    static Segment2d GetDivisionLine(const Segment2d &prev_seg,
                                     const Segment2d &cur_seg);

    static void MakeSegmentsDivisible(
        const std::vector<Segment2d> &raw_segments,
        const std::vector<int> &raw_start_segment_ids,
        std::vector<Segment2d> *divisible_segments,
        std::vector<int> *divisible_start_segment_ids,
        std::vector<int> *raw_segment_index_of_divisible_segments);

    using SegmentMap = QuadTreeFieldMap<IdField>;

    Config config_;
    std::vector<Segment2d> raw_segments_;
    std::vector<int> raw_start_segment_ids_;

    std::vector<Segment2d> segments_;
    std::vector<Bool> is_start_segment_;
    std::vector<int> segment_id_to_raw_id_;

    std::vector<Segment2d> division_line_with_prev_;

    std::vector<std::pair<int, int>> all_ranges_;

    int x_dim_ = 0;
    int y_dim_ = 0;
    boost::optional<GridFrame2d> grid_frame_;

    std::vector<int> grid_;
    std::vector<SegmentMap> segment_field_maps_;

    std::vector<double> center_distance_sqr_cache_;
    std::vector<int> single_object_grid_cache_;
};

}  // namespace planning
}  // namespace pnc_x
