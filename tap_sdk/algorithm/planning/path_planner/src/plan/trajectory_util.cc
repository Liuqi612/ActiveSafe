

#include "plan/trajectory_util.h"

#include <algorithm>
#include <boost/algorithm/clamp.hpp>

#include "math/vec.h"
#include "util/loop_guard.h"
namespace pnc_x {
namespace planning {

void LerpTrajPoint(const TrajectoryPointProto &p0,
                   const TrajectoryPointProto &p1,
                   double alpha,
                   TrajectoryPointProto *p) {
    p->mutable_pos()->set_x(Lerp(p0.pos().x(), p1.pos().x(), alpha));
    p->mutable_pos()->set_y(Lerp(p0.pos().y(), p1.pos().y(), alpha));
#define LERP_FIELD(field, lerp) \
    p->set_##field((lerp)(p0.field(), p1.field(), alpha));
    LERP_FIELD(s, Lerp)
    LERP_FIELD(theta, LerpAngle)
    LERP_FIELD(kappa, Lerp)
    LERP_FIELD(t, Lerp)
    LERP_FIELD(v, Lerp)
    LERP_FIELD(a, Lerp)
    LERP_FIELD(j, Lerp)
    LERP_FIELD(psi, Lerp)
    LERP_FIELD(chi, Lerp)
#undef LERP_FIELD
}

void LerpTrajPoint(const TrajectoryPoint &p0,
                   const TrajectoryPoint &p1,
                   double alpha,
                   TrajectoryPoint *p) {
    p->set_pos(Vec2d(Lerp(p0.pos().x(), p1.pos().x(), alpha),
                     Lerp(p0.pos().y(), p1.pos().y(), alpha)));
#define LERP_FIELD(field, lerp) \
    p->set_##field((lerp)(p0.field(), p1.field(), alpha));
    LERP_FIELD(s, Lerp)
    LERP_FIELD(theta, LerpAngle)
    LERP_FIELD(kappa, Lerp)
    LERP_FIELD(t, Lerp)
    LERP_FIELD(v, Lerp)
    LERP_FIELD(a, Lerp)
    LERP_FIELD(j, Lerp)
    LERP_FIELD(psi, Lerp)
    LERP_FIELD(chi, Lerp)
#undef LERP_FIELD
}

void LerpTrajPoint(const SecondOrderTrajectoryPoint &p0,
                   const SecondOrderTrajectoryPoint &p1,
                   double alpha,
                   SecondOrderTrajectoryPoint *p) {
    p->set_pos(Vec2d(Lerp(p0.pos().x(), p1.pos().x(), alpha),
                     Lerp(p0.pos().y(), p1.pos().y(), alpha)));
#define LERP_FIELD(field, lerp) \
    p->set_##field((lerp)(p0.field(), p1.field(), alpha));
    LERP_FIELD(s, Lerp)
    LERP_FIELD(theta, LerpAngle)
    LERP_FIELD(kappa, Lerp)
    LERP_FIELD(t, Lerp)
    LERP_FIELD(v, Lerp)
    LERP_FIELD(a, Lerp)
#undef LERP_FIELD
}

std::vector<ApolloTrajectoryPointProto> ToApolloTrajectoryPointProto(
    absl::Span<const TrajectoryPointProto> traj) {
    std::vector<ApolloTrajectoryPointProto> res;
    res.reserve(traj.size());
    for (int i = 0, n = traj.size(); i < n; ++i) {
        res.push_back(ToApolloTrajectoryPointProto(traj[i]));
    }

    return res;
}

std::vector<ApolloTrajectoryPointProto> ToApolloTrajectoryPointProto(
    absl::Span<const prediction::PredictedTrajectoryPoint> traj) {
    std::vector<ApolloTrajectoryPointProto> res;
    res.reserve(traj.size());
    for (int i = 0, n = traj.size(); i < n; ++i) {
        TrajectoryPointProto pt;
        traj[i].SecondOrderTrajectoryPoint::ToProto(&pt);
        res.push_back(ToApolloTrajectoryPointProto(pt));
    }
    return res;
}

std::vector<TrajectoryPointProto> ToTrajectoryPointProto(
    absl::Span<const ApolloTrajectoryPointProto> traj) {
    std::vector<TrajectoryPointProto> res;
    if (traj.empty()) return res;
    res.reserve(traj.size());
    for (std::size_t i = 0, n = traj.size(); i < n; ++i) {
        res.push_back(ToTrajectoryPointProto(traj[i]));
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_chi(
            (res[i + 1U].psi() - res[i].psi()) /
            (res[i + 1U].t() - res[i].t()));
    }
    if (traj.size() > 1) {
        res.back().set_chi((res.rbegin() + 1)->chi());
    }

    return res;
}

std::vector<TrajectoryPointProto> ToTrajectoryPointProtoFromSecondOrderApollo(
    absl::Span<const ApolloTrajectoryPointProto> traj) {
    std::vector<TrajectoryPointProto> res;
    if (traj.empty()) return res;
    res.reserve(traj.size());
    for (std::size_t i = 0, n = traj.size(); i < n; ++i) {
        res.push_back(ToTrajectoryPointProtoFromSecondOrderApollo(traj[i]));
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_j(
            (traj[i + 1U].a() - traj[i].a()) /
            (traj[i + 1U].relative_time() - traj[i].relative_time()));
        res[i].set_psi(
            (traj[i + 1U].path_point().kappa() - traj[i].path_point().kappa()) /
            (traj[i + 1U].relative_time() - traj[i].relative_time()));
    }
    if (traj.size() > 1) {
        res.back().set_j((res.rbegin() + 1)->j());
        res.back().set_psi((res.rbegin() + 1)->psi());
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_chi(
            (res[i + 1U].psi() - res[i].psi()) /
            (res[i + 1U].t() - res[i].t()));
    }
    res.back().set_chi(0.0);

    return res;
}

std::vector<TrajectoryPointProto> ToTrajectoryPointProto(
    absl::Span<const TrajectoryPoint> traj) {
    std::vector<TrajectoryPointProto> res;
    res.reserve(traj.size());
    for (int i = 0, n = traj.size(); i < n; ++i) {
        res.emplace_back();
        traj[i].ToProto(&res.back());
    }

    return res;
}

std::vector<TrajectoryPoint> ToTrajectoryPoint(
    absl::Span<const TrajectoryPointProto> traj) {
    std::vector<TrajectoryPoint> res;
    res.reserve(traj.size());
    for (int i = 0, n = traj.size(); i < n; ++i) res.emplace_back(traj[i]);

    return res;
}

std::vector<ApolloTrajectoryPointProto> ToApolloTrajectoryPointProto(
    absl::Span<const TrajectoryPoint> traj) {
    std::vector<ApolloTrajectoryPointProto> res;
    res.reserve(traj.size());
    for (int i = 0, n = traj.size(); i < n; ++i) {
        res.emplace_back();
        traj[i].ToProto(&res.back());
    }

    return res;
}

std::vector<TrajectoryPoint> ToTrajectoryPoint(
    absl::Span<const ApolloTrajectoryPointProto> traj) {
    std::vector<TrajectoryPoint> res;
    if (traj.empty()) return res;
    res.reserve(traj.size());
    for (std::size_t i = 0, n = traj.size(); i < n; ++i) {
        res.emplace_back(ToTrajectoryPointProto(traj[i]));
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_chi(
            (res[i + 1U].psi() - res[i].psi()) /
            (res[i + 1U].t() - res[i].t()));
    }
    if (traj.size() > 1) {
        res.back().set_chi((res.rbegin() + 1)->chi());
    }

    return res;
}

std::vector<TrajectoryPoint> ToTrajectoryPointFromSecondOrderApollo(
    absl::Span<const ApolloTrajectoryPointProto> traj) {
    std::vector<TrajectoryPoint> res;
    if (traj.empty()) return res;
    res.reserve(traj.size());
    for (std::size_t i = 0, n = traj.size(); i < n; ++i) {
        res.emplace_back(ToTrajectoryPointProtoFromSecondOrderApollo(traj[i]));
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_j(
            (traj[i + 1U].a() - traj[i].a()) /
            (traj[i + 1U].relative_time() - traj[i].relative_time()));
        res[i].set_psi(
            (traj[i + 1U].path_point().kappa() - traj[i].path_point().kappa()) /
            (traj[i + 1U].relative_time() - traj[i].relative_time()));
    }
    if (traj.size() > 1) {
        res.back().set_j((res.rbegin() + 1)->j());
        res.back().set_psi((res.rbegin() + 1)->psi());
    }

    for (std::size_t i = 0, n = traj.size() - 1U; i < n; ++i) {
        res[i].set_chi(
            (res[i + 1U].psi() - res[i].psi()) /
            (res[i + 1U].t() - res[i].t()));
    }
    res.back().set_chi(0.0);

    return res;
}

std::vector<ApolloTrajectoryPointProto> ShiftTrajectoryByTime(
    double shift_time,
    const std::vector<ApolloTrajectoryPointProto> &trajectory_points,
    double max_decel_jerk,
    double max_acc_jerk) {
    if (trajectory_points.empty()) {
        return {};
    }
    const double trajectory_time_step = trajectory_points[1].relative_time() -
                                        trajectory_points[0].relative_time();
    const int shift_index = RoundToInt(shift_time / trajectory_time_step);
    const int trajectory_size = trajectory_points.size();
    if (shift_index < 0 || shift_index >= trajectory_size) {
        return {};
    }
    if (shift_index == 0) {
        return trajectory_points;
    }
    const ApolloTrajectoryPointProto &start_point =
        trajectory_points[shift_index];
    const double start_s = start_point.path_point().s();
    const double start_t = start_point.relative_time();

    std::vector<ApolloTrajectoryPointProto> res_traj;
    res_traj.reserve(trajectory_size);

    for (size_t i = shift_index; i < trajectory_points.size(); ++i) {
        res_traj.push_back(trajectory_points[i]);
        auto &point = res_traj.back();
        point.set_relative_time(point.relative_time() - start_t);
        point.mutable_path_point()->set_s(point.path_point().s() - start_s);
    }

    constexpr double kMinSpeed = 1e-6;
    constexpr double kMinDist = 1e-6;
    auto loop_guard = DEFAULT_LOOP_GUARD_WITH_FUNC();
    while (res_traj.size() < trajectory_size && loop_guard) {
        auto &prev_point = res_traj.back();
        const double dist = std::max(
            kMinDist, prev_point.v() * trajectory_time_step +
                          0.5 * prev_point.a() * Sqr(trajectory_time_step));
        auto point = prev_point;
        point.set_relative_time(prev_point.relative_time() +
                                trajectory_time_step);
        *point.mutable_path_point() =
            GetPathPointAlongCircle(point.path_point(), dist);

        point.set_v(std::max(
            kMinSpeed, prev_point.v() + prev_point.a() * trajectory_time_step));
        point.set_a(
            std::max(prev_point.a(), -1.0 * point.v() / trajectory_time_step));
        prev_point.set_j(boost::algorithm::clamp(
            (point.a() - prev_point.a()) / trajectory_time_step, max_decel_jerk,
            max_acc_jerk));
        res_traj.push_back(point);
    }
    res_traj.back().set_j((res_traj.rbegin() + 1)->j());
    XCHECK_EQ(res_traj.size(), trajectory_size);

    return res_traj;
}

namespace {

PathPoint ConstKappaPathPointFromTrajectoryPoint(const TrajectoryPoint &x0) {
    PathPoint pp;
    pp.set_x(x0.pos().x());
    pp.set_y(x0.pos().y());
    pp.set_z(0.0);
    pp.set_theta(x0.theta());
    pp.set_kappa(x0.kappa());
    pp.set_lambda(0.0);
    pp.set_s(x0.s());
    return pp;
}

}  // namespace

void ShiftTrajectoryByTime(double shift_time,
                           std::vector<TrajectoryPoint> *trajectory_points) {
    if (!XCHECK_NOTNULL(trajectory_points)) {
        return;
    }
    const int trajectory_size = static_cast<int>(trajectory_points->size());
    XCHECK_GE(trajectory_size, 2);

    constexpr double kMinDt = 1e-3;
    const double dt = std::max(
        kMinDt, (*trajectory_points)[1].t() - (*trajectory_points)[0].t());
    const int shift_index = boost::algorithm::clamp(RoundToInt(shift_time / dt),
                                                    0, trajectory_size - 1);
    if (shift_index == 0) {
        return;
    }

    trajectory_points->erase(trajectory_points->begin(),
                             trajectory_points->begin() + shift_index);

    const double s0 = trajectory_points->begin()->s();
    const double t0 = trajectory_points->begin()->t();
    for (TrajectoryPoint &traj_point : (*trajectory_points)) {
        traj_point.set_s(traj_point.s() - s0);
        traj_point.set_t(traj_point.t() - t0);
    }

    constexpr double kMinSpeed = 1e-6;
    constexpr double kMinDist = 1e-6;
    for (int i = 0; i < shift_index; ++i) {
        TrajectoryPoint x0 = trajectory_points->back();
        TrajectoryPoint x1;

        const double ds =
            std::max(kMinDist, x0.v() * dt + 0.5 * x0.a() * Sqr(dt));
        const PathPoint x0_pp = ConstKappaPathPointFromTrajectoryPoint(x0);
        const PathPoint x1_pp = GetPathPointAlongCircle(x0_pp, ds);

        x1.set_pos({x1_pp.x(), x1_pp.y()});
        x1.set_v(std::max(kMinSpeed, x0.v() + dt * x0.a()));
        x1.set_s(x0.s() + ds);
        x1.set_t(x0.t() + dt);
        x1.set_kappa(x1_pp.kappa());
        x1.set_theta(x1_pp.theta());

        x1.set_a(std::max(x0.a(), -x1.v() / dt));

        trajectory_points->push_back(x1);
    }
    XCHECK_EQ(trajectory_points->size(), trajectory_size);

    const int extrapolation_first_control_index =
        trajectory_size - 1 - shift_index;
    for (int i = extrapolation_first_control_index; i < trajectory_size - 1;
         ++i) {
        (*trajectory_points)[static_cast<size_t>(i)].set_j(
            ((*trajectory_points)[static_cast<size_t>(i) + 1U].a() - (*trajectory_points)[static_cast<size_t>(i)].a()) /
            dt);

        (*trajectory_points)[i].set_chi(0.0);
        (*trajectory_points)[i].set_psi(0.0);
    }

    trajectory_points->back().set_j(0.0);
    trajectory_points->back().set_chi(0.0);
    trajectory_points->back().set_psi(0.0);
}

}  // namespace planning
}  // namespace pnc_x
