/*
 * Copyright (C) 2024 by SenseTime Group Limited. All rights reserved.
 * Liuyong3 <liuyong3@senseauto.com>
 */

#ifndef TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_COMMAND_H_
#define TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_COMMAND_H_
#include <cstddef>
#include <cstdint>

#include "active_safety_types.h"
#include "as_enum_type.h"
namespace senseAD {
namespace tap {

enum class AebStatus : uint8_t {
  AEB_OFF = 0,
  AEB_Init = 1,
  AEB_Inhibit = 2,
  AEB_Standby = 3,
  AEB_NotUse1 = 4,
  AEB_NotUse2 = 5,
  AEB_ACTIVE = 6,
  AEB_Fault = 7,
};

enum class FcwStatus : uint8_t {
  FCW_NO_REQUEST = 0,
  FCW_LEVEL_1 = 1,  // low
  FCW_LEVEL_2 = 2,  // middle
  FCW_LEVEL_3 = 3,  // high
};

enum class FcwMode : uint8_t {
  FCW_OFF = 0,
  FCW_Init = 1,
  FCW_Inhibit = 2,
  FCW_Standby = 3,
  FCW_NotUse1 = 4,
  FCW_NotUse2 = 5,
  FCW_ACTIVE = 6,
  FCW_Fault = 7,
};

enum CtbCollisionDir {
  No_Collsion = 0,
  LEFT = 1,
  RIGHT = 2,
  LEFT_RIGHT = 3,
};

typedef struct {
  AsTargetInfo_T lgsf_target;
  float aeb_tar_dec;
  uint32_t hold_type;
  OnOffStatus aeb_req;
  OnOffStatus awb_req;
  OnOffStatus prefill_req;
  OnOffStatus aba_req;
  OnOffStatus belt_req;
  AebStatus aeb_status;
  FcwStatus fcw_status;
  FcwMode fcw_mode;
  // 0:No Level,1:Level_1,2:Level_2,3:Level_3
  uint8_t aba_level;
  // 0: NoRequest, 1:Level_1; 2:Level_2; 3:Level_3
  uint8_t awb_level;
  uint8_t aeb_req_valid;
  // Bit0: 是否为影子模式
  // Bit1: AEB
  // Bit2: EBA
  // Bit3: FCW
  // Bit4: DW
  // Bit5: AWB
  uint8_t shadow_mode;
  uint32_t resv1;
  float resv2;
  float resv3;
} AsCmdLgSafe_T;

typedef struct {
  OnOffStatus rctb_req;
  OnOffStatus rctb_valid;
  OnOffStatus fctb_req;
  OnOffStatus fctb_valid;
  float rctb_dec_req;
  float fctb_dec_req;
  CtbCollisionDir rctb_collision_dir;
  CtbCollisionDir fctb_collision_dir;
  uint32_t shadow_mode;
  uint32_t resv1;
  float resv2;
  float resv3;
} AsCmdCtb_T;
//
enum class AsShadowMode {
  AEB = (1 << 1),
  EBA = (1 << 2),
  FCW = (1 << 3),
  DW = (1 << 4),
  AWB = (1 << 5),
  DOW = (1 << 6),
  RCW = (1 << 7),
  FCTA = (1 << 8),
  FCTB = (1 << 9),
  RCTA = (1 << 10),
  RCTB = (1 << 11),
  BSD = (1 << 12),
  LCA = (1 << 13)
};
//
typedef struct {
  // AEB/FCW
  AsCmdLgSafe_T lgsf;
  // FCTB/RCTB
  AsCmdCtb_T ctb;
  // Bit0: LongSafe || SideFeature任一功能打开
  // Bit1: AEB
  // Bit2: EBA
  // Bit3: FCW
  // Bit4: DW
  // Bit5: AWB
  // Bit6: DOW
  // Bit7: RCW
  // Bit8: FCTA
  // Bit9: FCTB
  // Bit10: RCTA
  // Bit11: RCTB
  // Bit12: BSD
  // Bit13: LCA
  uint32_t shadow_mode;
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
} AsCommand_T;

}  // namespace tap
}  // namespace senseAD
#endif // TAP_SDK_ALGORITHM_LONGSAFE_2024_ALGO_INTERFACE_ACTIVE_SAFETY_COMMAND_H_
