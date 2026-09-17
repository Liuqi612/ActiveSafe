

#include <algorithm>
#include <iterator>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>

#include "speed/speed_limit.h"

#include "common/throw_check.h"
#include "math/util.h"

namespace pnc_x {
namespace planning {
namespace {
using SpeedLimitRange = SpeedLimit::SpeedLimitRange;
using SpeedLimitInfo = SpeedLimit::SpeedLimitInfo;

void RemoveDuplicateRanges(
    std::vector<std::pair<SpeedLimitRange, int>> *ranges) {
    if (!XCHECK_NOTNULL(ranges)) {
        return;
    }
    ranges->erase(std::remove_if(ranges->begin(), ranges->end(),
                                 [](const auto &range) {
                                     return range.first.start_s >=
                                            range.first.end_s;
                                 }),
                  ranges->end());
    std::stable_sort(
        ranges->begin(), ranges->end(), [](const auto &lhs, const auto &rhs) {
            return ((lhs.first.start_s == rhs.first.start_s) &&
                    (lhs.first.end_s == rhs.first.end_s))
                       ? lhs.first.speed_limit < rhs.first.speed_limit
                       : lhs.first.start_s < rhs.first.start_s;
        });
    ranges->erase(std::unique(ranges->begin(), ranges->end(),
                              [](const auto &lhs, const auto &rhs) {
                                  return (lhs.first.start_s ==
                                             rhs.first.start_s) &&
                                         (lhs.first.end_s == rhs.first.end_s);
                              }),
                  ranges->end());
}

void MergeSpeedLimitRanges(const std::vector<SpeedLimitRange> &ranges,
                           std::vector<SpeedLimitRange> *speed_limit_ranges,
                           std::vector<int> *merged_range_indices) {
    if (!XCHECK(!ranges.empty()) || !XCHECK_NOTNULL(speed_limit_ranges)) {
        return;
    }

    speed_limit_ranges->clear();
    if (ranges.size() == 1) {
        speed_limit_ranges->push_back(ranges[0]);
        return;
    }
    if (merged_range_indices != nullptr) {
        merged_range_indices->clear();
    }

    std::vector<std::pair<SpeedLimitRange, int>> ranges_with_index;
    ranges_with_index.reserve(ranges.size());
    for (size_t i = 0; i < ranges.size(); ++i) {
        ranges_with_index.emplace_back(ranges[static_cast<std::size_t>(i)],
                                       static_cast<std::size_t>(i));
    }

    RemoveDuplicateRanges(&ranges_with_index);

    struct Node {
        double s = 0.0;
        double v = 0.0;
        int idx = 0;
        bool in = true;
    };
    std::vector<Node> nodes;
    nodes.reserve(ranges_with_index.size() * 2);
    for (size_t i = 0; i < ranges_with_index.size(); ++i) {
        const auto &range =
            ranges_with_index[static_cast<std::size_t>(i)].first;
        const int idx = ranges_with_index[static_cast<std::size_t>(i)].second;
        const double speed_limit = range.speed_limit;
        nodes.push_back(
            {.s = range.start_s, .v = speed_limit, .idx = idx, .in = true});
        nodes.push_back(
            {.s = range.end_s, .v = speed_limit, .idx = idx, .in = false});
    }
    std::stable_sort(
        nodes.begin(), nodes.end(),
        [](const auto &lhs, const auto &rhs) { return lhs.s < rhs.s; });

    std::multimap<double, std::pair<int, double>> active_nodes;
    for (size_t i = 0; i < nodes.size(); ++i) {
        const Node &curr_node = nodes[static_cast<std::size_t>(i)];
        if (curr_node.in) {
            const auto &node_begin = *active_nodes.begin();
            if (!active_nodes.empty() && (curr_node.v < node_begin.first) &&
                (curr_node.s != node_begin.second.second)) {
                const int range_idx = active_nodes.begin()->second.first;
                speed_limit_ranges->push_back(
                    {.start_s = node_begin.second.second,
                     .end_s = curr_node.s,
                     .speed_limit = node_begin.first,
                     .info = ranges[static_cast<std::size_t>(range_idx)].info});
                if (merged_range_indices != nullptr) {
                    merged_range_indices->push_back(range_idx);
                }
            }

            active_nodes.insert({curr_node.v, {curr_node.idx, curr_node.s}});
        } else {
            XCHECK(!active_nodes.empty());
            auto start_it = active_nodes.end();
            const auto range = active_nodes.equal_range(curr_node.v);

            for (auto it = range.first; it != range.second; ++it) {
                if (curr_node.idx == it->second.first) {
                    start_it = it;
                    break;
                }
            }
            XCHECK(start_it != active_nodes.end());
            XCHECK_EQ(curr_node.idx, start_it->second.first);

            if (start_it == active_nodes.begin()) {
                const int range_idx = active_nodes.begin()->second.first;
                speed_limit_ranges->push_back(
                    {.start_s = start_it->second.second,
                     .end_s = curr_node.s,
                     .speed_limit = curr_node.v,
                     .info = ranges[static_cast<std::size_t>(range_idx)].info});
                if (merged_range_indices != nullptr) {
                    merged_range_indices->push_back(range_idx);
                }
                const auto next = std::next(start_it);
                if (next != active_nodes.end()) {
                    next->second.second = curr_node.s;
                }
            }

            active_nodes.erase(start_it);
        }
    }
}
}  // namespace

SpeedLimit::SpeedLimit(
    const std::vector<SpeedLimitRange> &new_speed_limit_ranges) {
    XCHECK(!new_speed_limit_ranges.empty());
    MergeSpeedLimitRanges(new_speed_limit_ranges, &speed_limit_ranges_,
                          nullptr);
}

boost::optional<SpeedLimitInfo> SpeedLimit::GetSpeedLimitInfoByS(
    double s) const {
    XCHECK(!speed_limit_ranges_.empty());
    auto it = std::upper_bound(
        speed_limit_ranges_.begin(), speed_limit_ranges_.end(), s,
        [](double s, const auto &range) { return s < range.start_s; });
    if (it != speed_limit_ranges_.begin()) {
        --it;
    }
    return InRange(s, it->start_s, it->end_s)
               ? boost::optional<SpeedLimitInfo>(SpeedLimitInfo(*it))
               : boost::none;
}

boost::optional<double> SpeedLimit::GetSpeedLimitByS(double s) const {
    auto info = GetSpeedLimitInfoByS(s);
    return info ? boost::optional<double>(info->speed_limit) : boost::none;
}

}  // namespace planning
}  // namespace pnc_x
