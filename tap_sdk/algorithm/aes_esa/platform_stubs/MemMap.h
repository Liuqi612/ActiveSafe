/* MemMap.h — x86 平台空桩文件
 *
 * 背景：Simulink ERT 为 AUTOSAR 目标生成的 CAL 文件中会 #include "MemMap.h"，
 * 该文件由 AUTOSAR BSW/OS 层提供，不在 Simulink 代码生成产物中。
 * 在 x86 CI 环境中不存在 AUTOSAR 中间件，故提供此空桩以满足编译器查找。
 * 本文件必须放在 aes 代码产物目录 *之外*，防止替换代码包时被误删。
 */
