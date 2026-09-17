

#include "prediction/prediction_util.h"

#include <algorithm>
#include <vector>

#include "pncx_constraint.pb.h"
#include "math/piecewise_linear_function.h"
#include "object/spacetime_object_trajectory.h"
#include "pncx_prediction.pb.h"
#include "prediction/predicted_trajectory.h"
#include "prediction/prediction.h"
#include "prediction/prediction_defs.h"
#include "pncx_prediction_common.pb.h"
#include "pncx_vehicle.pb.h"
#include "math/linear_interpolation.h"

namespace pnc_x {
namespace prediction {

bool IsStationaryTrajectory(const PredictedTrajectoryProto &traj) {
    return traj.type() == PredictionType::PT_STATIONARY;
}

bool IsStationaryTrajectory(const prediction::PredictedTrajectory &traj) {
    return traj.type() == PredictionType::PT_STATIONARY;
}

bool IsStationaryPrediction(const ObjectPredictionProto &pred) {
    return (pred.trajectories().size() == static_cast<size_t>(1)) &&
           (IsStationaryTrajectory(pred.trajectories(0)));
}

bool IsStationaryPrediction(const ObjectPrediction &pred) {
    return (pred.trajectories().size() == static_cast<size_t>(1)) &&
           (IsStationaryTrajectory(pred.trajectories()[0]));
}

void InitTraj(PredictedTrajectory *const trajectory,
              const double curr_acc,
              std::vector<double> *const split_s) {
    const auto &pts = trajectory->points();
    split_s->emplace_back(0.0);
    double s = 0.0;

    for (size_t i = 0; i < pts.size(); i++) {
        if (i < (pts.size() - 1)) {
            double dis = (pts.at(i + 1).pos() - pts.at(i).pos()).Length();
            s = s + dis;
            split_s->emplace_back(s);
        }
    }
}

bool RefineTrajByAcc(PredictedTrajectory *const trajectory,
                     const double curr_acc,
                     const double acc_ts_sec) {
    const auto &pts = trajectory->points();
    if (trajectory->points().empty()) return false;
    const double cv_ts_sec = std::max(0.0, kPredictionDuration - acc_ts_sec);

    PredictedTrajectory refined_traj;
    refined_traj.set_probability(trajectory->probability());
    refined_traj.set_index(trajectory->index());
    refined_traj.set_type(trajectory->type());
    refined_traj.set_intention(trajectory->intention());
    refined_traj.mutable_points()->emplace_back(std::move(pts.at(0)));
    std::vector<double> split_s;
    constexpr double t = kPredictionTimeStep;
    InitTraj(trajectory, curr_acc, &split_s);
    Vec2d prev_pos = pts.at(0).pos();
    double prev_s = 0.0;
    double prev_theta = pts.at(0).theta();
    double prev_kappa = pts.at(0).kappa();
    double prev_t = 0.0;
    double prev_v = pts.at(0).v();
    double prev_a = curr_acc;
    double ds = 0.0;
    const int acc_point_num =
        static_cast<int>(acc_ts_sec / kPredictionTimeStep) - 1;
    // AD_LINFO(PP) << "refine init state " << prev_s << " " << prev_theta << "
    // "
    //           << prev_kappa << " " << prev_t << " " << prev_v << " " <<
    //           prev_a;
    size_t si = 1UL;
    for (size_t i = 1UL; i < static_cast<unsigned long>(kPredictionPointNum);
         ++i) {
        prev_t = i * t;
        double rest_s = split_s.back() - prev_s;
        double tmp_a = prev_a;
        const size_t acc_point_limit = static_cast<size_t>(acc_point_num) + 1U;
        if (i < acc_point_limit) {
            tmp_a = std::min(
                prev_a,
                std::max(0.0, (rest_s - (prev_v * (acc_ts_sec - prev_t)) -
                               (prev_v * cv_ts_sec)) /
                                  ((0.5 * (acc_ts_sec - prev_t) *
                                    (acc_ts_sec - prev_t)) +
                                   (acc_ts_sec - prev_t))));
            if ((prev_v + (prev_a * t)) < 0.0) {
                tmp_a = -prev_v / t;
            }
            ds = (prev_v * t) + (0.5 * tmp_a * t * t);
        } else {
            tmp_a = 0.0;
            ds = prev_v * t;
        }
        if ((prev_s + ds) > split_s.at(si)) {
            si = std::min(split_s.size() - 1, si + 1);
        }
        prev_a = tmp_a;
        prev_v += prev_a * t;
        prev_s += ds;

        PredictedTrajectoryPoint refined_pt;
        Vec2d new_pos = (pts.at(si).pos() - pts.at(si - 1).pos()) *
                            (prev_s - split_s.at(si - 1)) /
                            std::max(0.1, split_s.at(si) - split_s.at(si - 1)) +
                        pts.at(si - 1).pos();

        refined_pt.set_pos(new_pos);
        refined_pt.set_s(prev_s);
        refined_pt.set_theta(pts.at(si - 1).theta());
        refined_pt.set_kappa(pts.at(si - 1).kappa());
        refined_pt.set_t(pts.at(0).t() + prev_t);
        refined_pt.set_v(prev_v);
        refined_pt.set_a(prev_a);
        refined_traj.mutable_points()->emplace_back(std::move(refined_pt));
    }
    *trajectory = refined_traj;
    return true;
}

void ExtendPredictionTraj(
    const planning::SpacetimeObjectTrajectory &traj,
    planning::ConstraintProto::LeadingObjectProto *leading_obj) {
    const auto &obj_cur_pos = traj.planner_object().pose().pos();

    PredictedTrajectory extend_traj;
    extend_traj.set_probability(traj.trajectory().probability());
    extend_traj.set_index(traj.trajectory().index());
    extend_traj.set_type(traj.trajectory().type());
    extend_traj.set_intention(traj.trajectory().intention());
    bool current_state_insert = false;
    constexpr double kStationaryVecNorm = 0.01;
    for (size_t i = 0; i < (traj.states().size() - 1); ++i) {
        Vec2d base_vec = traj.states().at(i + 1).traj_point->pos() -
                         traj.states().at(i).traj_point->pos();
        Vec2d tgt_vec = obj_cur_pos - traj.states().at(i).traj_point->pos();

        const double pj_length = tgt_vec.Dot(base_vec.normalized());
        if (!current_state_insert) {
            if (pj_length < 0) {
                extend_traj.mutable_points()->emplace_back(
                    std::move(*(traj.states().at(i).traj_point)));
                current_state_insert = true;
            } else if ((pj_length > 0) && (pj_length < base_vec.Length())) {
                PredictedTrajectoryPoint pt(traj.planner_object().pose());
                extend_traj.mutable_points()->emplace_back(std::move(pt));
                current_state_insert = true;
            } else if (base_vec.norm() < kStationaryVecNorm) {
                PredictedTrajectoryPoint pt(traj.planner_object().pose());
                extend_traj.mutable_points()->emplace_back(std::move(pt));
                current_state_insert = true;
            } else {
                continue;
            }
        } else {
            extend_traj.mutable_points()->emplace_back(
                std::move(*(traj.states().at(i).traj_point)));
        }
    }
    extend_traj.mutable_points()->emplace_back(
        std::move(*(traj.states().back().traj_point)));

    const int origin_traj_size = extend_traj.points().size();
    const int extend_pt_num = kPredictionPointNum - origin_traj_size;
    if (extend_pt_num > 0) {
        Vec2d cv_pos_t(0.0, 0.0);
        if (extend_traj.points().size() > 10) {
            Vec2d dpos =
                extend_traj.points().back().pos() -
                extend_traj.points().at(extend_traj.points().size() - 10).pos();
            double dt =
                extend_traj.points().back().t() -
                extend_traj.points().at(extend_traj.points().size() - 10).t();
            cv_pos_t = kPredictionTimeStep * dpos / std::max(0.1, dt);

        } else {
            Vec2d dpos = extend_traj.points().back().pos() -
                         extend_traj.points().front().pos();
            double dt = extend_traj.points().back().t() -
                        extend_traj.points().front().t();
            cv_pos_t = kPredictionTimeStep * dpos / std::max(0.1, dt);
        }
        double cv_v = cv_pos_t.Length() / kPredictionTimeStep;
        for (int i = 0; i < extend_pt_num; ++i) {
            PredictedTrajectoryPoint traj_pt;
            double theta = pnc_x::fast_math::Atan2(cv_pos_t.x(), cv_pos_t.y());
            if ((cv_pos_t.Length() < kStationaryVecNorm) &&
                !extend_traj.points().empty()) {
                theta = extend_traj.points().back().theta();
            }
            traj_pt.set_pos(extend_traj.points().back().pos() + cv_pos_t);
            traj_pt.set_s(extend_traj.points().back().s() + cv_pos_t.Length());
            traj_pt.set_theta(extend_traj.points().back().theta());
            traj_pt.set_kappa(0.0);
            traj_pt.set_t(extend_traj.points().back().t() +
                          kPredictionTimeStep);
            traj_pt.set_v(cv_v);
            traj_pt.set_a(0.0);
            extend_traj.mutable_points()->emplace_back(std::move(traj_pt));
        }
    }

    planning::SpacetimeObjectTrajectory st_obj_traj(
        traj.planner_object(), std::move(extend_traj), traj.traj_index(),
        traj.required_lateral_gap());
    for (const auto &state : st_obj_traj.states()) {
        state.traj_point->ToProto(leading_obj->add_modified_trajectory());
    }
}

void ExtendPredictionTraj(planning::SpacetimeObjectTrajectory &traj) {
    const auto &obj_cur_pos = traj.planner_object().pose().pos();

    PredictedTrajectory extend_traj;
    extend_traj.set_probability(traj.trajectory().probability());
    extend_traj.set_index(traj.trajectory().index());
    extend_traj.set_type(traj.trajectory().type());
    extend_traj.set_intention(traj.trajectory().intention());
    bool current_state_insert = false;
    constexpr double kStationaryVecNorm = 0.01;
    for (size_t i = 0; i + 1 < traj.states().size(); ++i) {
        Vec2d base_vec = traj.states().at(i + 1).traj_point->pos() -
                         traj.states().at(i).traj_point->pos();
        Vec2d tgt_vec = obj_cur_pos - traj.states().at(i).traj_point->pos();

        const double pj_length = tgt_vec.Dot(base_vec.normalized());
        if (!current_state_insert) {
            if (pj_length < 0) {
                extend_traj.mutable_points()->emplace_back(
                    std::move(*(traj.states().at(i).traj_point)));
                current_state_insert = true;
            } else if ((pj_length > 0) && (pj_length < base_vec.Length())) {
                PredictedTrajectoryPoint pt(traj.planner_object().pose());
                extend_traj.mutable_points()->emplace_back(std::move(pt));
                current_state_insert = true;
            } else if (base_vec.norm() < kStationaryVecNorm) {
                PredictedTrajectoryPoint pt(traj.planner_object().pose());
                extend_traj.mutable_points()->emplace_back(std::move(pt));
                current_state_insert = true;
            } else {
                continue;
            }
        } else {
            extend_traj.mutable_points()->emplace_back(
                std::move(*(traj.states().at(i).traj_point)));
        }
    }
    extend_traj.mutable_points()->emplace_back(
        std::move(*(traj.states().back().traj_point)));

    const int origin_traj_size = extend_traj.points().size();
    const int extend_pt_num = kPredictionPointNum - origin_traj_size;
    if (extend_pt_num > 0) {
        Vec2d cv_pos_t(0.0, 0.0);
        if (extend_traj.points().size() > 10) {
            Vec2d dpos =
                extend_traj.points().back().pos() -
                extend_traj.points().at(extend_traj.points().size() - 10).pos();
            double dt =
                extend_traj.points().back().t() -
                extend_traj.points().at(extend_traj.points().size() - 10).t();
            cv_pos_t = kPredictionTimeStep * dpos / std::max(0.1, dt);

        } else {
            Vec2d dpos = extend_traj.points().back().pos() -
                         extend_traj.points().front().pos();
            double dt = extend_traj.points().back().t() -
                        extend_traj.points().front().t();
            cv_pos_t = kPredictionTimeStep * dpos / std::max(0.1, dt);
        }
        double cv_v = cv_pos_t.Length() / kPredictionTimeStep;
        for (int i = 0; i < extend_pt_num; ++i) {
            PredictedTrajectoryPoint traj_pt;
            traj_pt.set_pos(extend_traj.points().back().pos() + cv_pos_t);
            traj_pt.set_s(extend_traj.points().back().s() + cv_pos_t.Length());
            traj_pt.set_theta(extend_traj.points().back().theta());
            traj_pt.set_kappa(0.0);
            traj_pt.set_t(extend_traj.points().back().t() +
                          kPredictionTimeStep);
            traj_pt.set_v(cv_v);
            traj_pt.set_a(0.0);
            extend_traj.mutable_points()->emplace_back(std::move(traj_pt));
        }
    }

    planning::SpacetimeObjectTrajectory timespatial_obj_traj(
        traj.planner_object(), std::move(extend_traj), traj.traj_index(),
        traj.required_lateral_gap());
    traj = timespatial_obj_traj;
}

bool CheckTrajValidity(const planning::SpacetimeObjectTrajectory &traj,
                       std::string &invalidity_info) {
    if (traj.is_stationary()) {
        return true;
    }
    std::stringstream ss;
    ss << traj.traj_id() << "-invalidinfo-t-";
    constexpr double kMinSpeed = 1.0;
    constexpr double kMinDt = 0.001;

    const auto &traj_points = traj.trajectory().points();
    for (size_t i = 1; i < traj_points.size(); ++i) {
        const double ave_speed =
            (traj_points[i].v() + traj_points[i - 1].v()) / 2.0;

        if (ave_speed < kMinSpeed) {
            continue;
        }
        const double delta_t = traj_points[i].t() - traj_points[i - 1].t();

        if (delta_t < kMinDt) {
            ss << traj_points[i - 1].t() << "-" << traj_points[i].t()
               << "[t-diff too small];";
            invalidity_info += ss.str();
            return false;
        }

        const Vec2d pos_diff = traj_points[i].pos() - traj_points[i - 1].pos();
        const double disp = pos_diff.norm();
        if (std::fabs((disp / delta_t) - ave_speed) >
            std::fmin(ave_speed * 0.2, 1.0)) {
            ss << traj_points[i - 1].t() << "-" << traj_points[i].t()
               << ",pos diff v:" << disp / delta_t << ",ave speed:" << ave_speed
               << "[v pos-diff not match];";
            invalidity_info += ss.str();
            return false;
        }
    }
    return true;
}

void RefineTrajByTrajAcc(PredictedTrajectory *const trajectory,
                         double acc_confidence) {
    const auto &pts = trajectory->points();
    if (pts.size() < 2) {
        return;
    }

    PredictedTrajectory refined_traj;
    refined_traj.set_probability(trajectory->probability());
    refined_traj.set_index(trajectory->index());
    refined_traj.set_type(trajectory->type());
    refined_traj.set_intention(trajectory->intention());
    refined_traj.mutable_points()->emplace_back(std::move(pts.at(0)));
    constexpr double t = kPredictionTimeStep;
    Vec2d prev_pos = pts.at(0).pos();
    double prev_s = 0.0;
    double prev_theta = pts.at(0).theta();
    double prev_kappa = pts.at(0).kappa();
    double prev_t = 0.0;
    double prev_v = pts.at(0).v();
    double prev_a = pts.at(0).a() * acc_confidence;
    double ds = 0.0;

    const double target_speed = std::fmax(0.0, prev_v + (2.5 * prev_a));
    const bool is_keep_larger_than_target_speed = prev_a < 0 ? true : false;

    std::vector<double> split_s;
    InitTraj(trajectory, 0.0, &split_s);

    std::vector<double> raw_time_seq;
    for (size_t i = 0; i < pts.size(); i++) {
        raw_time_seq.push_back(pts[i].t());
    }

    size_t si = 1UL;
    for (size_t i = 1UL; i < static_cast<unsigned long>(kPredictionPointNum);
         ++i) {
        prev_t = i * t;
        double tmp_a = prev_a;
        int raw_point_idx = std::distance(
            raw_time_seq.begin(),
            std::lower_bound(raw_time_seq.begin(), raw_time_seq.end(), prev_t));
        if (((raw_point_idx + 1) <= raw_time_seq.size()) &&
            (raw_point_idx >= 1)) {
            tmp_a = ads_x::planning::math::lerp(
                pts.at(raw_point_idx - 1).a(), pts.at(raw_point_idx - 1).t(),
                pts.at(raw_point_idx).a(), pts.at(raw_point_idx).t(), prev_t,
                true);
        } else {
            tmp_a = 0.0;
        }

        if ((((prev_v + (prev_a * t)) < target_speed) &&
             is_keep_larger_than_target_speed) ||
            (((prev_v + (prev_a * t)) > target_speed) &&
             !is_keep_larger_than_target_speed)) {
            tmp_a = (target_speed - prev_v) / t;
        }

        ds = (prev_v * t) + (0.5 * tmp_a * t * t);

        if ((si < split_s.size()) && ((prev_s + ds) > split_s.at(si))) {
            si = si + 1UL;
        }
        prev_a = tmp_a;
        prev_v += prev_a * t;
        prev_s += ds;

        PredictedTrajectoryPoint refined_pt;
        Vec2d new_pos;
        if (si < split_s.size()) {
            new_pos = (pts.at(si).pos() - pts.at(si - 1).pos()) *
                          (prev_s - split_s.at(si - 1)) /
                          std::max(0.1, split_s.at(si) - split_s.at(si - 1)) +
                      pts.at(si - 1).pos();
        } else {
            const Vec2d last_pos_diff =
                pts.at(pts.size() - 1).pos() - pts.at(pts.size() - 2).pos();
            const double last_ds =
                std::max(0.1, split_s.at(split_s.size() - 1) -
                                  split_s.at(split_s.size() - 2));
            new_pos = last_pos_diff * (prev_s - split_s.back()) / last_ds +
                      pts.at(pts.size() - 1).pos();
        }

        refined_pt.set_pos(new_pos);
        refined_pt.set_s(prev_s);
        refined_pt.set_theta((si < (pts.size() + 1)) ? pts.at(si - 1).theta()
                                                     : pts.back().theta());
        refined_pt.set_kappa((si < (pts.size() + 1)) ? pts.at(si - 1).kappa()
                                                     : pts.back().kappa());
        refined_pt.set_t(pts.at(0).t() + prev_t);
        refined_pt.set_v(prev_v);
        refined_pt.set_a(prev_a);
        refined_traj.mutable_points()->emplace_back(std::move(refined_pt));
    }
    *trajectory = refined_traj;
    return;
}

}  // namespace prediction
}  // namespace pnc_x
