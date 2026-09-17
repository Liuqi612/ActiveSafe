

#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>

#include "initializer/collision_checker.h"
#include "common/log.h"

#include "math/geometry/polygon2d.h"
#include "math/util.h"
#include "prediction/prediction_defs.h"

namespace pnc_x {
namespace planning {

namespace {

template <typename StateType>
std::vector<Box2d> StatesToBoxes(absl::Span<const Box2d> boxes_by_angles,
                                 double inv_angle_sample_step,
                                 absl::Span<const StateType> states) {
    std::vector<Box2d> av_boxes(states.size());
    for (int i = 0; i < states.size(); ++i) {
        const auto &state = states[i];
        const int angle_idx =
            RoundToInt((state.h + M_PI) * inv_angle_sample_step);
        if (!XCHECK_LT(angle_idx, boxes_by_angles.size())) {
            break;
        }
        av_boxes[i] = boxes_by_angles[angle_idx].Transform(state.xy);
    }
    return av_boxes;
}

struct AvBoxGroup {
    int first_ix;
    int last_ix;
    AABox2d aabox;
};

std::vector<AvBoxGroup> ComputeAvBoxGroups(const int time_offset,
                                           absl::Span<const Box2d> av_boxes,
                                           const int group_size) {
    std::vector<AvBoxGroup> av_box_groups;
    av_box_groups.reserve(
        static_cast<size_t>(av_boxes.size() / group_size + 1));

    for (int i = 0, n = av_boxes.size(); i < n; ++i) {
        if (av_box_groups.empty() || (i + time_offset) % group_size == 0) {
            av_box_groups.push_back(
                {.first_ix = i, .last_ix = i, .aabox = av_boxes[static_cast<size_t>(i)].GetAABox()});
        } else {
            av_box_groups.back().last_ix = i;
            av_box_groups.back().aabox.MergeFrom(av_boxes[static_cast<size_t>(i)].GetAABox());
        }
    }
    return av_box_groups;
}

void CheckTrajectoryCollision(
    int time_offset,
    absl::Span<const Box2d> av_boxes,
    absl::Span<const AvBoxGroup> av_box_groups,
    int sample_step,
    absl::Span<const BoxGroupCollisionChecker::ObjectBoxGroup> traj_box_groups,
    int group_size,
    const IgnoreTrajMap &ignored_trajs,
    CollisionInfo *info) {
    const int group_offset = time_offset / group_size;

    for (const auto &obj_boxes : traj_box_groups) {
        if (ignored_trajs.contains(obj_boxes.sampled_traj->traj->traj_id())) {
            continue;
        }

        for (int av_gix = 0, n = av_box_groups.size(); av_gix < n; ++av_gix) {
            const int obj_gix = group_offset + av_gix;
            const auto &av_box_group = av_box_groups[static_cast<size_t>(av_gix)];

            bool found_collision = false;
            if (obj_gix < obj_boxes.aaboxes.size() &&
                obj_boxes.aaboxes[obj_gix].HasOverlap(av_box_group.aabox)) {
                const auto &obj_states = obj_boxes.sampled_traj->states;
                for (int av_ix = av_box_group.first_ix,
                         t = av_box_group.first_ix + time_offset;
                     av_ix <= av_box_group.last_ix && t < obj_states.size();
                     ++av_ix, ++t) {
                    if (obj_states[static_cast<size_t>(t)].box.HasOverlap(av_boxes[static_cast<size_t>(av_ix)])) {
                        boost::optional<CollisionConfiguration> config =
                            boost::none;
                        if (t > 0) {
                            config = DetermineConfiguration(
                                av_boxes[static_cast<size_t>(av_ix)], obj_states[static_cast<size_t>(t - 1)].box);
                        }
                        info->collision_objects.push_back({
                            .time = t * sample_step,
                            .traj = obj_boxes.sampled_traj->traj,
                            .collision_configuration = config,
                        });
                        found_collision = true;
                        break;
                    }
                }
            }
            if (found_collision) break;
        }
    }
}

void CheckStationaryObjectCollision(
    absl::Span<const Box2d> av_boxes,
    absl::Span<const AvBoxGroup> av_box_groups,
    int sample_step,
    absl::Span<const SpacetimeObjectTrajectory *const>
        considered_stationary_trajs,
    absl::Span<const SpacetimeObjectState> stationary_obj_states,
    CollisionInfo *info) {
    if (!XCHECK_EQ(considered_stationary_trajs.size(),
                   stationary_obj_states.size())) {
        return;
    }
    for (int traj_idx = 0; traj_idx < considered_stationary_trajs.size();
         ++traj_idx) {
        const auto &state = stationary_obj_states[static_cast<size_t>(traj_idx)];

        for (int i = 0, n = av_box_groups.size(); i < n; ++i) {
            const auto &sdc_box = av_box_groups[static_cast<size_t>(i)];
            bool found_collision = false;

            const auto &obj_aabox = state.contour.AABoundingBox();
            if (obj_aabox.HasOverlap(sdc_box.aabox)) {
                for (int j = sdc_box.first_ix; j <= sdc_box.last_ix; ++j) {
                    if (av_boxes[j].HasOverlap(obj_aabox) &&
                        state.contour.HasOverlap(av_boxes[j])) {
                        info->collision_objects.push_back(
                            {.time = j * sample_step,
                             .traj = considered_stationary_trajs[static_cast<size_t>(traj_idx)]});
                        found_collision = true;
                        break;
                    }
                }
            }
            if (found_collision) break;
        }
    }
}

}  // namespace

void CollisionInfo::Clear() { collision_objects.clear(); }

CollisionConfiguration DetermineConfiguration(const Box2d &av_box,
                                              const Box2d &obj_box) {
    int front = 0;
    int back = 0;
    int left = 0;
    int right = 0;
    const auto &pts = obj_box.GetCornersCounterClockwise();
    const int pts_size = pts.size();
    const auto &av_seg =
        Segment2d(av_box.RearCenterPoint(), av_box.FrontCenterPoint());
    double seg_length = av_seg.length();
    for (const auto &pt : pts) {
        const double proj = av_seg.ProjectOntoUnit(pt);
        if (proj < 0.0) {
            back++;
        } else if (proj > seg_length) {
            front++;
        }
        const double product = av_seg.ProductOntoUnit(pt);
        if (product > 0.0) {
            left++;
            continue;
        } else {
            right++;
        }
    }
    if (front == pts_size) {
        return CollisionConfiguration::FRONT;
    }
    if (back == pts_size) {
        return CollisionConfiguration::BACK;
    }
    if (left > 0) {
        return CollisionConfiguration::LEFT;
    }
    return CollisionConfiguration::RIGHT;
}

std::vector<SampledTrajectory> SampleTrajectory(
    absl::Span<const SpacetimeObjectTrajectory *const> trajs, int sample_step) {
    std::vector<SampledTrajectory> sampled_trajs;
    sampled_trajs.reserve(trajs.size());
    for (const auto traj : trajs) {
        const auto states = traj->states();
        std::vector<SpacetimeObjectState> sampled_states;
        sampled_states.reserve(states.size() / static_cast<size_t>(sample_step) +
                               1U);
        for (int i = 0; i < states.size(); i += sample_step) {
            sampled_states.push_back(states[static_cast<size_t>(i)]);
        }
        sampled_trajs.push_back({
            .states = std::move(sampled_states),
            .traj = traj,
        });
    }
    return sampled_trajs;
}
void BoxGroupCollisionChecker::UpdateStationaryObjectBuffer(
    double stationary_obj_buffer) {
    stationary_obj_states_.clear();

    for (auto &traj : considered_stationary_trajs_) {
        auto state = traj->states().front();
        state.contour = state.contour.ExpandByDistance(stationary_obj_buffer);
        stationary_obj_states_.push_back(std::move(state));
    }
}

void BoxGroupCollisionChecker::UpdateMovingObjectBuffer(
    double moving_obj_buffer) {
    const double moving_extend_len = moving_obj_buffer * 2.0;

    sampled_trajs_ = SampleTrajectory(considered_moving_trajs_, sample_step_);

    for (auto &sampled_traj : sampled_trajs_) {
        for (auto &sample_state : sampled_traj.states) {
            sample_state.box.LongitudinalExtend(moving_extend_len);
            sample_state.box.LateralExtend(moving_extend_len);
        }
    }

    traj_box_groups_.clear();
    traj_box_groups_.reserve(static_cast<size_t>(sampled_trajs_.size()));
    for (auto &sampled_traj : sampled_trajs_) {
        auto &sampled_states = sampled_traj.states;
        ObjectBoxGroup box_group;
        box_group.sampled_traj = &sampled_traj;
        box_group.aaboxes.reserve((sampled_states.size() + 1U) / static_cast<size_t>(kGroupSize));

        for (int i = 0, n = sampled_states.size(); i < n; i += kGroupSize) {
            AABox2d aabox =
                sampled_states[static_cast<size_t>(i)].box.GetAABox();
            for (int j = i + 1; (j < i + kGroupSize) && (j < n); ++j) {
                aabox.MergeFrom(sampled_states[static_cast<size_t>(j)].box.GetAABox());
            }
            box_group.aaboxes.push_back(aabox);
        }
        traj_box_groups_.emplace_back(std::move(box_group));
    }
}

BoxGroupCollisionChecker::BoxGroupCollisionChecker(
    const SpacetimePlannerObjectTrajectories *st_planner_obj_traj,
    const VehicleGeometryParamsProto *params,
    int sample_step,
    double stationary_obj_buffer,
    double moving_obj_buffer,
    const ApolloTrajectoryPointProto &start_point,
    bool delete_reverse)
    : sample_step_(sample_step) {
    XCHECK_GE(sample_step, 1);
    for (const auto &traj : *st_planner_obj_traj->trajectories) {
        const double ego_heading_angle = start_point.path_point().theta();
        const double obj_theta = traj.pose().theta();
        const double angle_diff =
            std::abs(NormalizeAngle(ego_heading_angle - obj_theta));
        if (traj.is_stationary()) {
            considered_stationary_trajs_.push_back(&traj);
        } else if (!delete_reverse || angle_diff < M_PI / 2.0) {
            considered_moving_trajs_.push_back(&traj);
        }
    }
    UpdateStationaryObjectBuffer(stationary_obj_buffer);
    UpdateMovingObjectBuffer(moving_obj_buffer);

    const double ra_to_center =
        params->front_edge_to_center() - 0.5 * params->length();
    constexpr double kMaxErrorByAngleSampling = 0.05;
    const int half_sample_num =
        CeilToInt(M_PI / kMaxErrorByAngleSampling * ra_to_center);
    angle_sample_step_ = M_PI / half_sample_num;
    inv_angle_sample_step_ = 1.0 / angle_sample_step_;
    Box2d zero_pos_box({ra_to_center, 0.0}, {1.0, 0.0}, params->length(),
                       params->width());
    boxes_by_angles_.reserve(static_cast<size_t>(2 * half_sample_num + 1));

    for (int i = 0; i < half_sample_num; ++i) {
        const double angle = i * angle_sample_step_;
        boxes_by_angles_.push_back(zero_pos_box.AffineTransform(angle - M_PI));
    }

    boxes_by_angles_.push_back(zero_pos_box);

    for (int i = half_sample_num - 1; i >= 0; --i) {
        auto box(boxes_by_angles_[static_cast<size_t>(i)]);
        box.MirrorByX();
        boxes_by_angles_.push_back(std::move(box));
    }
}

void BoxGroupCollisionChecker::CheckCollisionWithTrajectories(
    double init_t,
    absl::Span<const MotionState> states,
    const IgnoreTrajMap &ignored_trajs,
    CollisionInfo *info) const {
    const std::vector<Box2d> av_boxes =
        StatesToBoxes(boxes_by_angles_, inv_angle_sample_step_, states);
    const int time_offset =
        RoundToInt(init_t / (static_cast<double>(sample_step_) * prediction::kPredictionTimeStep));
    std::vector<AvBoxGroup> av_box_groups =
        ComputeAvBoxGroups(time_offset, av_boxes, kGroupSize);

    CheckTrajectoryCollision(time_offset, av_boxes, av_box_groups, sample_step_,
                             traj_box_groups_, kGroupSize, ignored_trajs, info);
}

void BoxGroupCollisionChecker::CheckCollisionWithStationaryObjects(
    absl::Span<const GeometryState> states, CollisionInfo *info) const {
    const std::vector<Box2d> av_boxes =
        StatesToBoxes(boxes_by_angles_, inv_angle_sample_step_, states);
    const std::vector<AvBoxGroup> av_box_groups =
        ComputeAvBoxGroups(0, av_boxes, kGroupSize);
    CheckStationaryObjectCollision(av_boxes, av_box_groups, 1,
                                   considered_stationary_trajs_,
                                   stationary_obj_states_, info);
}

int BoxGroupCollisionChecker::sample_step() const { return sample_step_; }

}  // namespace planning
}  // namespace pnc_x
