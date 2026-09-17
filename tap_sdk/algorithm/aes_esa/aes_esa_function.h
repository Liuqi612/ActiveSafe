#pragma once

// AES_ESA_SWC.h 必须最先包含，使 Simulink 生成的全局命名空间类型先于业务层头文件注册。
// 用 extern "C" 块包裹，防止 C++ 编译器对 C 函数名做名字修饰。
extern "C" {
#include "algorithm/aes_esa/aes/AES_ESA_SWC_ert_rtw/AES_ESA_SWC.h"
}

// Simulink 生成代码有时会把 true/false 重定义为整数宏，与 C++ bool 字面量冲突，在此撤销。
#ifdef true
#undef true
#endif
#ifdef false
#undef false
#endif

#include "interface/active_safety_coreout.h"
#include "interface/active_safety_vse.h"
#include "interface/fusion_object.h"
#include "interface/lane_marker.h"
#include "common/global_config.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_command.h"
#include "algorithm/longsafe_2024/algo_interface/active_safety_types.h"

#include <cstdint>
#include <cstring>

namespace active_safety {
namespace aes_esa {

// AES/ESA 对外精简指令（每帧从 AES_ESA_T 抽取，供 AsCommand 预留字段发布）
// 与 Simulink 类型对应：EvasionDirection / ActiveFlag / Mode 为 uint8，StrWhlAngReq 为 real32
struct AesEsaCmd_T {
    uint8_t evasion_direction;  // AES_ESA_EvasionDirection：避让方向请求
    uint8_t active_flag;        // AES_ESA_ActiveFlag：是否激活（0/1）
    uint8_t mode;               // AES_ESA_Mode：状态机
    float   str_whl_ang_req;    // AES_ESA_StrWhlAngReq：方向盘转角请求（单位与模型一致）
};

// AES/ESA 模型桥接类
// 封装 Simulink ERT 生成的 AES_ESA_SWC 模型的生命周期（初始化、逐帧推进、终止），
// 并负责业务层数据类型与模型原生 C 类型之间的双向映射。
class AesEsaFunction {
  public:
    AesEsaFunction();
    ~AesEsaFunction();

    // 调用 Simulink 初始化函数，绑定输入/输出缓冲区
    void Init();

    // 每帧推进模型：先做输入映射，再调用 AES_ESA_SWC_step
    // aeb_length / aeb_width：来自 lgsf_2024_.GetSelectOut().longsafe_aeb，
    // 用于填充 AsTarget 的目标长宽
    // global_config：由 wrapper 透传全局标定，供后续影子模式/开关逻辑统一接入
    void Update(const FusionInfo&                   fusioninfo,
                const LanesInfo&                    road_info,
                const AsVseOut&                     vse_out,
                const AsOnComingOut&                oncom_out,
                const AsOverTakingOut&              overtake_out,
                const senseAD::tap::AsCmdLgSafe_T&  cmd_output,
                const GlobalConfig&                 global_config,
                const Reserved_Input&               reseverved_input,
                float                               aeb_length,
                float                               aeb_width);

    // 获取本帧模型输出，供外部（as_debug.hpp）直接读取
    const AES_ESA_T& GetOutput() const { return aes_esa_out_; }

    // 获取本帧精简指令（避障方向 / 激活 / 状态机 / 转角请求），供 AsCommand 等发布
    const AesEsaCmd_T& GetAesEsaCmd() const { return aes_esa_cmd_; }
    void  AbortAesEsaCmd();

  private:
    // 将业务层各路入参转换为模型原生 C 类型，写入 u_* 成员缓冲区
    void MapToSimulinkInput(const FusionInfo&                   fusioninfo,
                            const LanesInfo&                    road_info,
                            const AsVseOut&                     vse_out,
                            const AsOnComingOut&                oncom_out,
                            const AsOverTakingOut&              overtake_out,
                            const Reserved_Input&              reseverved_input,
                            const senseAD::tap::AsCmdLgSafe_T&  cmd_output,
                            float                               aeb_length,
                            float                               aeb_width);

    // Simulink 实时模型句柄，由构造函数静态分配后赋值
    RT_MODEL_AES_ESA_SWC_T* rtm_{nullptr};

    // 模型原生类型的输入缓冲区（全局命名空间，与 Simulink 接口完全匹配）
    ::LanesInfo      u_lanes_info_{};
    ::AsVseOut       u_vse_out_{};
    ::ElkInfo        u_elk_info_{};
    ::AsTarget       u_as_target_{};
    ::AS_FusionInfo  u_fus_info_{};
    ::Reserved_Input u_reseverved_input_{};

    // 模型输出，AES_ESA_SWC_step 每帧覆写，GetOutput() 直接返回引用
    AES_ESA_T aes_esa_out_{};

    // 从 aes_esa_out_ 每帧刷新，供 GetAesEsaCmd() 读取
    AesEsaCmd_T aes_esa_cmd_{};
};

} // namespace aes_esa
} // namespace active_safety
