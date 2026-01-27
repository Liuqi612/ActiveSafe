#include "cross_evaluator.h"
#include <cmath>
namespace senseAD {
namespace tap {
AsCrossEvaluator::AsCrossEvaluator() {}
AsCrossEvaluator::~AsCrossEvaluator() {}

void AsCrossEvaluator::ProcessScpEvaluator(const active_safety::AsObstacle &scp_obj,
                                           const active_safety::AsObstacleList &obj_list,
                                           const AsVseOut &vse_out,
                                           const AS_LaneMarkerInfo_T &lane) {
  CheckIsScpScene(scp_obj, vse_out);
  CheckObjectCorrectDirection(scp_obj, vse_out);
  CheckObjSpdLeanToStraight(scp_obj);
  CheckObjectNearSideScpObj(scp_obj, obj_list);
  CheckObjBoundaryInOppsiteSide(scp_obj, vse_out, lane);
  CheckHostTryToSteer(vse_out);
}

void AsCrossEvaluator::CheckIsScpScene(const active_safety::AsObstacle &scp_obj,
                                       const AsVseOut &vse_out) {
  // if (vse_out.host_state == AsHostState::AS_HOST_IN_HARD_CURVE) {
  //   scp_flag = false;
  // } else {
  //   bool validClass = (scp_obj.object_class == active_safety::ObjectClass::CAR ||
  //                      scp_obj.object_class == active_safety::ObjectClass::BICYCLE ||
  //                      scp_obj.object_class == active_safety::ObjectClass::ESCOOTER ||
  //                      scp_obj.object_class == active_safety::ObjectClass::MOTORCYCLE ||
  //                      scp_obj.object_class == active_safety::ObjectClass::TRUCK);
  //   bool validLatSpd = std::abs(scp_obj.long_vel) < 3.0f &&
  //                      (scp_obj.lat_vel * scp_obj.lat_posn < 0);
  //   scp_flag = validClass && validLatSpd;
  // }
}

void AsCrossEvaluator::CheckObjectCorrectDirection(const active_safety::AsObstacle &scp_obj,
                                                   const AsVseOut &vse_out) {
  // float probabilityLateralMoving = 0.0f;
  // float objHdg = M_PI_2;
  // float vel_heading = atan2(scp_obj.lat_vel, scp_obj.long_vel);
  // float scp_object_heading_factor = 0.5;
  // objHdg = scp_object_heading_factor * vel_heading +
  //          (1 - scp_object_heading_factor) * scp_obj.heading;

  // if (vse_out.aeb_active && scp_obj.f_is_aeb_active_tgt) {
  //   probabilityLateralMoving = 0.5;
  // } else {
  //   float tmp = fabsf(objHdg) - M_PI_2;
  //   probabilityLateralMoving = expf(-fabsf(tmp));
  // }
  // bool probaFlag = probabilityLateralMoving < 0.45;
  // Set(probaFlag && scp_flag, AsScenarioDiscInfo::AS_SCP_TURN_LONG_MOVING);
}

void AsCrossEvaluator::CheckObjSpdLeanToStraight(const active_safety::AsObstacle &scp_obj) {
  // int rate_up_cnt = 0;
  // float prev_moving_rate = 0.0f;
  // for (std::size_t i = 0; i < scp_obj.fus_vel.capacity(); i++) {
  //   float vel_y = scp_obj.fus_vel.get_frame(i).y();
  //   if (std::abs(vel_y) < 0.01) {
  //     vel_y = 0.01;
  //   }
  //   float moving_rate = std::abs(scp_obj.fus_vel.get_frame(i).x() / vel_y);
  //   if (i == 0) {
  //     prev_moving_rate = moving_rate;
  //   } else {
  //     if (moving_rate < prev_moving_rate) {
  //       rate_up_cnt++;
  //     } else {
  //       if (rate_up_cnt > 1) {
  //         rate_up_cnt--;
  //       } else {
  //         rate_up_cnt = 0;
  //       }
  //     }
  //   }
  // }
  // bool rateChange = rate_up_cnt > 15;
  // bool typeChk = scp_obj.f_is_vehicle;
  // Set(rateChange && scp_flag && typeChk,
  //     AsScenarioDiscInfo::AS_SCP_SPD_LEAN_TO_STRAIGHT);
}

void AsCrossEvaluator::CheckObjectNearSideScpObj(
    const active_safety::AsObstacle &scp_obj, const active_safety::AsObstacleList &obj_list) {
//  bool isObjectNearSideScpObj = false;
//  for (const active_safety::AsObstacle &trk : obj_list) {
//    if (trk.fus_trkID > 0) {
//      bool objClassValid =
//          (trk.object_class == active_safety::ObjectClass::CAR ||
//           trk.object_class == active_safety::ObjectClass::TRUCK ||
//           trk.object_class == active_safety::ObjectClass::THREEWHEEl_VEHICLE);
//      bool objHdgAngValid = fabsf(trk.heading) < M_1_PI;
//      bool objLongPosValid = (trk.long_posn + trk.length < scp_obj.long_posn &&
//                              trk.long_posn > 0.0f);
//      bool objLatPosValid = false;
//      if (fabsf(trk.lat_posn) - fabsf(scp_obj.lat_posn) < -3.0f) {
//        objLatPosValid = true;
//      }
//      if (objClassValid && objHdgAngValid && objLongPosValid &&
//          objLatPosValid) {
//        isObjectNearSideScpObj = true;
//        break;
//      }
//    }
//  }
//  Set(isObjectNearSideScpObj && scp_flag,
//      AsScenarioDiscInfo::AS_SCP_OBJ_NEARSIDE);
}

void AsCrossEvaluator::CheckObjBoundaryInOppsiteSide(
    const active_safety::AsObstacle &scp_obj, const AsVseOut &vse_out,
    const AS_LaneMarkerInfo_T &lane) {
  // check if there is boundary in scp obj's direction.
  bool scpObjTurnToFwd = false;
  if (lane.LeftRoadEdge.LineValid && scp_obj.lat_posn < -1.2f) {
    float dist = vse_out.host_dist_to_front;
    float dist_squard = dist * dist;
    float offset = lane.LeftRoadEdge.LinePolyC0 +
                   lane.LeftRoadEdge.LinePolyC1 * dist +
                   0.5 * lane.LeftRoadEdge.LinePolyC2 * dist_squard +
                   0.16667 * lane.LeftRoadEdge.LinePolyC3 * dist_squard * dist;
    bool boundaryLongPosValid =
        lane.LeftRoadEdge.LineViewRangeStart < scp_obj.long_posn &&
        lane.LeftRoadEdge.LineViewRangeEnd > scp_obj.long_posn;
    if (offset < 3.5f && boundaryLongPosValid) {
      scpObjTurnToFwd = true;
    }
  }
  if (lane.RightRoadEdge.LineValid && scp_obj.lat_posn > 1.2f) {
    float dist = vse_out.host_dist_to_front;
    float dist_squard = dist * dist;
    float offset = lane.RightRoadEdge.LinePolyC0 +
                   lane.RightRoadEdge.LinePolyC1 * dist +
                   0.5 * lane.RightRoadEdge.LinePolyC2 * dist_squard +
                   0.16667 * lane.RightRoadEdge.LinePolyC3 * dist_squard * dist;
    bool boundaryLongPosValid =
        lane.RightRoadEdge.LineViewRangeStart < scp_obj.long_posn &&
        lane.RightRoadEdge.LineViewRangeEnd > scp_obj.long_posn;
    if (offset > -3.5f && boundaryLongPosValid) {
      scpObjTurnToFwd = true;
    }
  }
  Set(scpObjTurnToFwd && scp_flag,
      AsScenarioDiscInfo::AS_SCP_BOUNDARY_IN_OPPOSITESIDE);
}

void AsCrossEvaluator::CheckHostTryToSteer(const AsVseOut &vse_out) {
  (void)(vse_out);
  // check Host direction with env info.
  // Host Lat Moving && FreeSpace
  // 原来是用车道线计算的自车横向速度，现在需考虑是否根据vse的yaw序列？
}

} // namespace tap
} // namespace senseAD
