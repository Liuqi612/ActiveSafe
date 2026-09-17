

#include "initializer/motion_search_util.h"

#include <algorithm>

#include "math/vec.h"
#include "plan/planner_defs.h"
#include "util/status_macros.h"

namespace pnc_x {
namespace planning {

constexpr double kEpsilon = 1e-6;

ApolloTrajectoryPointProto MotionState2TrajPoint(
    const MotionState &motion_state, double s, double current_t) {
    PathPoint point;
    point.set_x(motion_state.xy.x());
    point.set_y(motion_state.xy.y());
    point.set_z(0);
    point.set_theta(motion_state.h);
    point.set_kappa(motion_state.k);
    point.set_s(s);

    ApolloTrajectoryPointProto traj_point;
    *(traj_point.mutable_path_point()) = point;
    traj_point.set_v(motion_state.v);
    traj_point.set_a(motion_state.a);
    traj_point.set_relative_time(current_t);

    return traj_point;
}

void ResampleTrajectoryPoints(
    const std::vector<const MotionForm *> &motions,
    std::vector<ApolloTrajectoryPointProto> &traj_points) {
    traj_points.reserve(static_cast<std::size_t>(kInitializerTrajectorySteps));

    double s = 0.0;
    auto motion_it = motions.begin();
    double current_motion_start_time = 0.0,
           current_motion_end_time = (*motion_it)->duration();
    traj_points.emplace_back(
        MotionState2TrajPoint((*motion_it)->GetStartMotionState(), 0, 0));
    for (int i = 1; i < kInitializerTrajectorySteps; ++i) {
        const double current_t = static_cast<double>(i) * kTrajectoryTimeStep;
        if (current_t > current_motion_end_time) {
            ++motion_it;

            if (motion_it == motions.end()) {
                break;
            }
            current_motion_start_time = current_motion_end_time;
            current_motion_end_time += (*motion_it)->duration();
        }
        const auto motion_state =
            (*motion_it)->State(current_t - current_motion_start_time);

        s += motion_state.xy.DistanceTo(
            Vec2d(traj_points[static_cast<std::size_t>(i - 1)].path_point().x(),
                  traj_points[static_cast<std::size_t>(i - 1)].path_point().y()));
        traj_points.emplace_back(
            MotionState2TrajPoint(motion_state, s, current_t));
    }
}

std::vector<ApolloTrajectoryPointProto> ConstructStationaryTraj(
    const MotionState &sdc_motion) {
    const MotionState state{.xy = sdc_motion.xy,
                            .h = sdc_motion.h,
                            .k = sdc_motion.k,
                            .v = 0.0,
                            .a = 0.0};

    std::vector<ApolloTrajectoryPointProto> stationary_traj;
    stationary_traj.reserve(static_cast<std::size_t>(kInitializerTrajectorySteps));
    for (int i = 0; i < kInitializerTrajectorySteps; ++i) {
        const double current_t = static_cast<double>(i) * kTrajectoryTimeStep;
        stationary_traj.emplace_back(
            MotionState2TrajPoint(state, 0.0, current_t));
    }

    return stationary_traj;
}

std::vector<double> AddCost(absl::Span<const double> vec1,
                            absl::Span<const double> vec2) {
    const int vec1_size = vec1.size();
    std::vector<double> res(static_cast<std::size_t>(vec1_size));
    if (!XCHECK_EQ(vec1_size, vec2.size())) {
        return res;
    }
    for (std::size_t i = 0; i < static_cast<std::size_t>(vec1_size); ++i) {
        res[i] = vec1[i] + vec2[i];
    }
    return res;
}

MotionState PrepareStartMotionNode(
    const GeometryGraph &geometry,
    const std::vector<GeometryNodeIndex> &first_layer,
    const ApolloTrajectoryPointProto &start_point,
    int *start_node_idx_on_first_layer) {
    for (int i = static_cast<int>(first_layer.size()) - 1; i >= 0; --i) {
        const auto &node = geometry.GetNode(first_layer[static_cast<std::size_t>(i)]);
        if (node.reachable) {
            *start_node_idx_on_first_layer = i;
            return MotionState{.xy = node.xy,
                               .h = start_point.path_point().theta(),
                               .k = node.k,
                               .t = 0.0,
                               .v = start_point.v(),
                               .a = start_point.a()};
        }
    }
    return MotionState();
}

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>> ResampleDenseTrajectory(
    const std::vector<ApolloTrajectoryPointProto> &trajectory,
    double time_step) {
    if (trajectory.empty()) {
        return absl::InvalidArgumentError("Selected trajectory empty.");
    }

    if (trajectory.size() < 2) {
        return trajectory;
    }

    double cur_s = 0.0;
    std::vector<ApolloTrajectoryPointProto> dense_trajectory;
    dense_trajectory.reserve(trajectory.size() * 5);
    for (size_t i = 0; i < trajectory.size() - 1; ++i) {
        const auto &start_point = trajectory[i];
        const auto &end_point = trajectory[i + 1];
        const double delta_t =
            end_point.relative_time() - start_point.relative_time();
        const double num_points = std::ceil(delta_t / time_step);
        const double delta_x =
            (end_point.path_point().x() - start_point.path_point().x()) /
            num_points;
        const double delta_y =
            (end_point.path_point().y() - start_point.path_point().y()) /
            num_points;
        const double delta_theta =
            NormalizeAngle(end_point.path_point().theta() -
                           start_point.path_point().theta()) /
            num_points;
        const double delta_s = std::hypot(delta_x, delta_y);
        const double delta_v = (end_point.v() - start_point.v()) / num_points;
        const double delta_a = (end_point.a() - start_point.a()) / num_points;
        const double delta_relative_time =
            (end_point.relative_time() - start_point.relative_time()) /
            num_points;
        const double ref_s = start_point.path_point().s();
        const double ref_end_s = end_point.path_point().s();
        const double delta_ref_s = (ref_end_s - ref_s) / num_points;
        for (int j = 0; j < num_points; ++j) {
            ApolloTrajectoryPointProto point;
            point.mutable_path_point()->set_x(start_point.path_point().x() +
                                              j * delta_x);
            point.mutable_path_point()->set_y(start_point.path_point().y() +
                                              j * delta_y);
            point.mutable_path_point()->set_theta(NormalizeAngle(
                start_point.path_point().theta() + j * delta_theta));
            point.mutable_path_point()->set_s(cur_s);
            point.mutable_path_point()->set_ref_s(ref_s + j * delta_ref_s);
            point.set_v(start_point.v() + j * delta_v);
            point.set_a(start_point.a() + j * delta_a);
            point.set_relative_time(start_point.relative_time() +
                                    j * delta_relative_time);
            cur_s += delta_s;
            dense_trajectory.emplace_back(point);
        }
    }

    if (!dense_trajectory.empty()) {
        const double last_delta_x = trajectory.back().path_point().x() -
                                    dense_trajectory.back().path_point().x();
        const double last_delta_y = trajectory.back().path_point().y() -
                                    dense_trajectory.back().path_point().y();

        ApolloTrajectoryPointProto point;
        point.mutable_path_point()->set_x(trajectory.back().path_point().x());
        point.mutable_path_point()->set_y(trajectory.back().path_point().y());
        point.mutable_path_point()->set_theta(
            trajectory.back().path_point().theta());
        point.mutable_path_point()->set_s(cur_s);
        point.mutable_path_point()->set_ref_s(
            trajectory.back().path_point().s());
        point.set_v(trajectory.back().v());
        point.set_a(trajectory.back().a());
        point.set_relative_time(trajectory.back().relative_time());
        dense_trajectory.emplace_back(point);
    }

    return dense_trajectory;
}

void ConstructTrajResult(std::vector<ApolloTrajectoryPointProto> *traj,
                         double time_step,
                         int min_traj_size) {
    if (traj->size() >= min_traj_size) {
        return;
    }

    const auto back_pt = traj->back();
    double ref_v = back_pt.v();
    while (traj->size() < min_traj_size) {
        ApolloTrajectoryPointProto point;
        double delta_x = ref_v * time_step *
                         pnc_x::fast_math::Cos(back_pt.path_point().theta());
        double delta_y = ref_v * time_step *
                         pnc_x::fast_math::Sin(back_pt.path_point().theta());
        double x = traj->back().path_point().x() + delta_x;
        double y = traj->back().path_point().y() + delta_y;
        double s = traj->back().path_point().s() + std::hypot(delta_x, delta_y);
        double ref_s =
            traj->back().path_point().ref_s() + std::hypot(delta_x, delta_y);
        point.mutable_path_point()->set_x(x);
        point.mutable_path_point()->set_y(y);
        point.mutable_path_point()->set_theta(back_pt.path_point().theta());
        point.mutable_path_point()->set_s(s);
        point.mutable_path_point()->set_ref_s(ref_s);
        point.set_v(ref_v);
        point.set_a(0.0);
        point.set_relative_time(traj->back().relative_time() + time_step);
        traj->emplace_back(point);
    }
}

absl::StatusOr<std::vector<ApolloTrajectoryPointProto>> ConstructTrajResult(
    const std::vector<ApolloTrajectoryPointProto> &selected_traj,
    double time_step,
    int min_traj_size) {
    ASSIGN_OR_RETURN(
        auto resampled_traj,
        ResampleDenseTrajectory(selected_traj, kTrajectoryTimeStep));

    auto &traj_result = resampled_traj;
    const auto back_pt = traj_result.back();
    double ref_v = back_pt.v();
    while (traj_result.size() < min_traj_size) {
        ApolloTrajectoryPointProto point;
        double delta_x = ref_v * time_step *
                         pnc_x::fast_math::Cos(back_pt.path_point().theta());
        double delta_y = ref_v * time_step *
                         pnc_x::fast_math::Sin(back_pt.path_point().theta());
        double x = traj_result.back().path_point().x() + delta_x;
        double y = traj_result.back().path_point().y() + delta_y;
        double s =
            traj_result.back().path_point().s() + std::hypot(delta_x, delta_y);
        double ref_s = traj_result.back().path_point().ref_s() +
                       std::hypot(delta_x, delta_y);
        point.mutable_path_point()->set_x(x);
        point.mutable_path_point()->set_y(y);
        point.mutable_path_point()->set_theta(back_pt.path_point().theta());
        point.mutable_path_point()->set_s(s);
        point.mutable_path_point()->set_ref_s(ref_s);
        point.set_v(ref_v);
        point.set_a(0.0);
        point.set_relative_time(traj_result.back().relative_time() + time_step);
        traj_result.emplace_back(point);
    }
    return traj_result;
}

void VisualizeTrajResult(const std::vector<ApolloTrajectoryPointProto> &traj,
                         const std::string &prefix) {}

void VisualizeObsTrajs(
    const std::vector<ObstacleDecisionGroup> &decision_groups,
    const std::string &prefix) {}

}  // namespace planning
}  // namespace pnc_x
