#include "dow_function.h"

#include <cmath>

namespace active_safety {
namespace dow {

void DowFunction::InitZone(const VehicleConfig &vehcfg) {
  m_rear_left_zone.clear();
  m_rear_left_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[0],
                                           m_dow_cal.k_dow_warning_zone_lat[0] + vehcfg.k_host_width / 2.0f);
  m_rear_left_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[1],
                                           m_dow_cal.k_dow_warning_zone_lat[1] + vehcfg.k_host_width / 2.0f);
  m_rear_left_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[2],
                                           m_dow_cal.k_dow_warning_zone_lat[2]);
  m_rear_left_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[3],
                                           m_dow_cal.k_dow_warning_zone_lat[3]);

  m_rear_right_zone.clear();
  m_rear_right_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[3],
                                            -m_dow_cal.k_dow_warning_zone_lat[3]);
  m_rear_right_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[2],
                                            -m_dow_cal.k_dow_warning_zone_lat[2]);
  m_rear_right_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[1],
                                            -m_dow_cal.k_dow_warning_zone_lat[1] - vehcfg.k_host_width / 2.0f);
  m_rear_right_zone.point_list.emplace_back(m_dow_cal.k_dow_warning_zone_long[0],
                                            -m_dow_cal.k_dow_warning_zone_lat[0] - vehcfg.k_host_width / 2.0f);

  m_front_left_zone.clear();
  m_front_left_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[1],
                                            m_dow_cal.k_dow_ftm_warning_zone_lat[1]);
  m_front_left_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[0],
                                            m_dow_cal.k_dow_ftm_warning_zone_lat[0]);
  m_front_left_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[3],
                                            m_dow_cal.k_dow_ftm_warning_zone_lat[3]);
  m_front_left_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[2],
                                            m_dow_cal.k_dow_ftm_warning_zone_lat[2]);

  m_front_right_zone.clear();
  m_front_right_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[2],
                                             -m_dow_cal.k_dow_ftm_warning_zone_lat[2]);
  m_front_right_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[3],
                                             -m_dow_cal.k_dow_ftm_warning_zone_lat[3]);
  m_front_right_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[1],
                                             -m_dow_cal.k_dow_ftm_warning_zone_lat[1]);
  m_front_right_zone.point_list.emplace_back(m_dow_cal.k_dow_ftm_warning_zone_long[0],
                                             -m_dow_cal.k_dow_ftm_warning_zone_lat[0]);
}

} // namespace dow
} // namespace active_safety
