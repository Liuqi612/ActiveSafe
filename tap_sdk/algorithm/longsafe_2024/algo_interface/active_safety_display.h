/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#pragma once
#include "active_safety_types.h"
#include "as_enum_type.h"
#include <cstddef>
#include <cstdint>

namespace senseAD {
namespace tap {

enum TargetObjColor {
  NONE = 0,
  YELLOW = 3,
  RED = 4,
};
enum class FcwDispStatus {
  FCW_OFF = 0,
  FCW_ON = 1,
  FCW_FAILURE = 2,
};
enum class AebDispStatus {
  AEB_OFF = 0,
  AEB_ON = 1,
  AEB_FAILURE = 2,
  AEB_INHIBITED = 3,
};
enum FcwWarnDist {
  NORMAL = 0,
  NEAR = 1,
  FAR = 2,
};
enum class FcwActiveStatus {
  FCW_NO_REQUEST = 0,
  FCW_LEVEL_1 = 1, // low
  FCW_LEVEL_2 = 2, // middle
  FCW_LEVEL_3 = 3, // high
};
enum AebActiveStatus {
  NO_ACTIVE = 0,
  PRE_FILL = 1,
  ACTIVE = 2,
};
enum FcwAebTextInfo {
  DEFAULT_TEXT = 0,
  FCW_IS_ACTIVE = 1,
  FCW_IS_SWITCHED_ON = 2,
  UNABLE_TO_SWITCH_ON_FCW = 3,
  FCW_IS_SWITCHED_OFF = 4,
  FCW_IS_IN_ERROR_MODE = 5,
  AEB_IS_ACTIVE = 6,
  AEB_IS_SWITCHED_ON = 7,
  UNABLE_TO_SWITCH_ON_AEB = 8,
  AEB_IS_SWITCHED_OFF = 9,
  AEB_IS_IN_ERROR_MODE = 10,
};

enum DrivingSoundWarn {
  DEFAULT_WARNING = 0,
  TIP_WARNING = 1,
  ACTIVE_WARNING = 2,
  FAILED_WARNING = 3,
  SAFETY_WARNING = 4,
  WARNING_SOUND = 5,
};

enum CtaWorkingStatus {
  DEFAULT = 0,
  OFF = 1,
  ONLY_WARING = 2,
  WARING_BRAKE = 3,
};

typedef struct {
  AsTargetInfo_T target_lgsf;
  TargetObjColor target_color;
  FcwDispStatus fcw_sts;
  AebDispStatus aeb_sts;
  FcwWarnDist fcw_warn_dist;
  FcwActiveStatus fcw_active_sts;
  AebActiveStatus aeb_active_sts;
  FcwAebTextInfo fcw_aeb_text_info;
  DrivingSoundWarn driving_sound_warn;
} AsDisplayLgSafe_T;

typedef struct {
  AsTargetInfo_T target_rcta;
  AsTargetInfo_T target_fcta;
  OnOffStatus rcta_sound;
  OnOffStatus rcta_left_warn;
  OnOffStatus rcta_right_warn;
  OnOffStatus fcta_sound;
  OnOffStatus fcta_left_warn;
  OnOffStatus fcta_right_warn;
  CtaWorkingStatus rcta_working_status;
  CtaWorkingStatus fcta_working_status;
} AsDiaplayCta_T;

typedef struct {
  AsTargetInfo_T target_bsd;
  AsTargetInfo_T target_lca;
  // 0:Default 1:灯光+声音 2: 关闭 3: 灯光
  uint32_t switch_req;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t bsd_warn_left;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t bsd_warn_right;
  OnOffStatus bsc_sound;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t lca_warn_left;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t lca_warn_right;
} AsDiaplayBsd_T;

typedef struct {
  AsTargetInfo_T target_rcw;
  // 0:reserve,1:On,2:Off,3:reserve
  uint32_t rcw_switch_req;
  // 0:default,1:Off,2:On
  uint32_t rcw_working_status;
  OnOffStatus rcw_collision_warn;
} AsDiaplayRcw_T;

typedef struct {
  AsTargetInfo_T target_dow;
  // 0:default,1:On,2:Off,3:reserve
  uint32_t dow_switch_req;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t dow_left_warn;
  // 0：Inactive,1：Warning_level_1,2：Warning_Level_2,3：Invalid
  uint32_t dow_right_warn;
} AsDiaplayDow_T;

typedef struct {
  // AEB/FCW
  AsDisplayLgSafe_T lgsf;
  // FCTA/RCTA
  AsDiaplayCta_T cta;
  // BSD/LCA
  AsDiaplayBsd_T bsd;
  // RCW
  AsDiaplayRcw_T rcw;
  // DOW
  AsDiaplayDow_T dow;
  uint32_t resv1;
  uint32_t resv2;
  uint32_t resv3;
  uint32_t resv4;
  uint32_t resv5;
  uint32_t resv6;
  float resv7;
  float resv8;
  float resv9;
  float resv10;
  float resv11;
  float resv12;
  float resv13;
  float resv14;
  float resv15;
} AsDisplay_T;

} // namespace tap
} // namespace senseAD
