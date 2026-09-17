

#include <algorithm>
#include <ostream>

#include "math/segment_matcher/segment_matcher_kdtree.h"
#include <absl/types/span.h>

namespace pnc_x {
namespace {

bool IsSegmentInAABox(const AABoxInfo *aabox_info, const AABox2d &aabox) {
    return aabox.HasOverlap(aabox_info->segment());
}

AABoxKDTreeParams GetDefaultAABoxKDTreeParams() {
    return AABoxKDTreeParams{.max_leaf_size = 4};
}

}  // namespace

SegmentMatcherKdtree::SegmentMatcherKdtree(const std::vector<Vec2d> &points)
    : SegmentMatcher(points),
      segments_tree_(aa_boxes_info_, GetDefaultAABoxKDTreeParams()) {}

SegmentMatcherKdtree::SegmentMatcherKdtree(
    const std::vector<Segment2d> &segments)
    : SegmentMatcher(segments),
      segments_tree_(aa_boxes_info_, GetDefaultAABoxKDTreeParams()) {}

SegmentMatcherKdtree::SegmentMatcherKdtree(
    const std::vector<std::pair<std::string, Segment2d>> &named_segments)
    : SegmentMatcher(named_segments),
      segments_tree_(aa_boxes_info_, GetDefaultAABoxKDTreeParams()) {}

bool SegmentMatcherKdtree::GetNearestSegmentId(double x,
                                               double y,
                                               std::string *id) const {
    if (!XCHECK(named_flag_) || !XCHECK_NOTNULL(id)) {
        return false;
    }
    const auto &object = segments_tree_.GetNearestObject({x, y});
    if (object == nullptr) {
        return false;
    }
    const auto idx = object->index();
    if (idx >= 0 && idx < segment_names_.size()) {
        *id = *segment_names_[static_cast<size_t>(idx)];
        return true;
    }
    return false;
}

std::vector<std::string> SegmentMatcherKdtree::GetSegmentIdInRadius(
    double x, double y, double r) const {
    XCHECK(named_flag_);
    const auto &aabox_in_radius = segments_tree_.GetObjects({x, y}, r);
    std::vector<std::string> names;
    names.reserve(aabox_in_radius.size());
    for (const auto &aabox : aabox_in_radius) {
        const auto idx = aabox->index();
        if (idx >= 0 && idx < segment_names_.size()) {
            names.push_back(*segment_names_[static_cast<size_t>(idx)]);
        }
    }
    return names;
}

bool SegmentMatcherKdtree::GetNearestSegmentIndex(double x,
                                                  double y,
                                                  int *index) const {
    if (!XCHECK(index_flag_) || !XCHECK_NOTNULL(index)) {
        return false;
    }
    const auto &object = segments_tree_.GetNearestObject({x, y});
    if (object == nullptr) {
        return false;
    }
    *index = static_cast<int>(object->index());
    return true;
}

std::vector<int> SegmentMatcherKdtree::GetSegmentIndexInRadius(double x,
                                                               double y,
                                                               double r) const {
    XCHECK(index_flag_);
    const auto &aabox_in_radius = segments_tree_.GetObjects({x, y}, r);
    std::vector<int> indexes;
    indexes.reserve(aabox_in_radius.size());
    for (const auto &aabox : aabox_in_radius) {
        indexes.emplace_back(aabox->index());
    }
    return indexes;
}

const Segment2d *SegmentMatcherKdtree::GetNearestSegment(double x,
                                                         double y) const {
    const auto &object = segments_tree_.GetNearestObject({x, y});
    if (object == nullptr) {
        return nullptr;
    }
    return &object->segment();
}

std::vector<const Segment2d *> SegmentMatcherKdtree::GetSegmentInRadius(
    double x, double y, double r) const {
    const auto &aabox_in_radius = segments_tree_.GetObjects({x, y}, r);
    std::vector<const Segment2d *> segments_ptr;
    segments_ptr.reserve(aabox_in_radius.size());
    for (const auto &aabox : aabox_in_radius) {
        segments_ptr.emplace_back(&aabox->segment());
    }
    return segments_ptr;
}

bool SegmentMatcherKdtree::GetNearestNamedSegment(double x,
                                                  double y,
                                                  pnc_x::Segment2d *seg,
                                                  std::string *id) const {
    if (!XCHECK(named_flag_) || !XCHECK_NOTNULL(seg) || !XCHECK_NOTNULL(id)) {
        return false;
    }
    const auto &object = segments_tree_.GetNearestObject({x, y});
    if (object == nullptr) {
        return false;
    }

    const auto idx = object->index();
    if (idx >= 0 && idx < segment_names_.size()) {
        *seg = object->segment();
        *id = *segment_names_[static_cast<size_t>(idx)];
        return true;
    }

    return false;
}

std::vector<std::pair<const Segment2d *, std::string>>
SegmentMatcherKdtree::GetNamedSegmentsInRadius(double x,
                                               double y,
                                               double r) const {
    XCHECK(named_flag_);
    const auto &aabox_in_radius = segments_tree_.GetObjects({x, y}, r);
    std::vector<std::pair<const Segment2d *, std::string>> named_segments;
    named_segments.reserve(aabox_in_radius.size());
    for (const auto &aabox : aabox_in_radius) {
        const auto idx = aabox->index();
        if (idx >= 0 && idx < segment_names_.size()) {
            named_segments.emplace_back(&aabox->segment(),
                                        *segment_names_[static_cast<size_t>(idx)]);
        }
    }
    return named_segments;
}

std::vector<std::string> SegmentMatcherKdtree::GetSegmentIdInAABox(
    const AABox2d &aabox) const {
    XCHECK(named_flag_);
    const auto &aabox_results =
        segments_tree_.GetObjectsWithinAABox(aabox, IsSegmentInAABox);
    std::vector<std::string> names;
    names.reserve(aabox_results.size());
    for (const auto &aabox : aabox_results) {
        const auto idx = aabox->index();
        if (idx >= 0 && idx < segment_names_.size()) {
            names.push_back(*segment_names_[static_cast<size_t>(idx)]);
        }
    }
    return names;
}

std::vector<int> SegmentMatcherKdtree::GetSegmentIndexInAABox(
    const AABox2d &aabox) const {
    XCHECK(named_flag_);
    const auto &aabox_results =
        segments_tree_.GetObjectsWithinAABox(aabox, IsSegmentInAABox);
    std::vector<int> indexes;
    indexes.reserve(aabox_results.size());
    for (const auto &aabox : aabox_results) {
        indexes.push_back(static_cast<int>(aabox->index()));
    }
    return indexes;
}

std::vector<const Segment2d *> SegmentMatcherKdtree::GetSegmentInAABox(
    const AABox2d &aabox) const {
    const auto &aabox_results =
        segments_tree_.GetObjectsWithinAABox(aabox, IsSegmentInAABox);
    std::vector<const Segment2d *> segments_ptr;
    segments_ptr.reserve(aabox_results.size());
    for (const auto &aabox : aabox_results) {
        segments_ptr.push_back(&aabox->segment());
    }
    return segments_ptr;
}

std::vector<std::pair<const Segment2d *, std::string>>
SegmentMatcherKdtree::GetNamedSegmentsInAABox(const AABox2d &aabox) const {
    XCHECK(named_flag_);
    const auto &aabox_results =
        segments_tree_.GetObjectsWithinAABox(aabox, IsSegmentInAABox);
    std::vector<std::pair<const Segment2d *, std::string>> named_segments;
    named_segments.reserve(aabox_results.size());
    for (const auto &aabox : aabox_results) {
        const auto idx = aabox->index();
        if (idx >= 0 && idx < segment_names_.size()) {
            named_segments.emplace_back(&aabox->segment(),
                                        *segment_names_[static_cast<size_t>(idx)]);
        }
    }
    return named_segments;
}

}  // namespace pnc_x
