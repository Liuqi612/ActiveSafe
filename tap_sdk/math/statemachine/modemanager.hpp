/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_MATH_STATEMACHINE_MODEMANAGER_HPP_
#define TAP_SDK_MATH_STATEMACHINE_MODEMANAGER_HPP_
#include "compositestate.hpp"
#include "simplestate.hpp"
namespace active_safety {
namespace math {
// Mode状态机所包含的状态
enum class ModeState { OFF, FAULT, ON, INHIBIT, STANDBY, ACTIVE };
// Mode状态机所包含的跳转条件
enum class ModeCondition {
  Off2Inhibit,
  On2Off,
  On2Fault,
  Fault2Inhibit,
  Inhibit2Standby,
  Inhibit2Active,
  Standby2Inhibit,
  Standby2Active,
  Active2Standby,
  Active2Inhibit
};
struct ModeStateCondition {
  // 功能是否关闭
  bool state_off;
  // 功能是否故障
  bool state_fault;
  // 功能是否被抑制
  bool state_inhibit;
  // 功能是否激活
  bool state_active;
  // 状态机跳转条件
  bool off2inhibit;
  bool fault2inhibit;
  bool inhibit2standby;
  bool inhibit2active;
  bool standby2active;
  bool active2standby;
};
//状态机的输入:所有状态跳转条件是否满足
class ModeConditionContext : public IConditionContext<ModeCondition> {
  std::unordered_map<ModeCondition, bool> conditions;

public:
  void setCondition(ModeStateCondition cond) {
    conditions[ModeCondition::Inhibit2Standby] = cond.inhibit2standby;
    conditions[ModeCondition::Standby2Inhibit] = cond.state_inhibit;
    conditions[ModeCondition::Inhibit2Active] = cond.inhibit2active;
    conditions[ModeCondition::Active2Inhibit] = cond.state_inhibit;
    conditions[ModeCondition::Standby2Active] = cond.standby2active;
    conditions[ModeCondition::Active2Standby] = cond.active2standby;
    conditions[ModeCondition::Off2Inhibit] = cond.off2inhibit;
    conditions[ModeCondition::On2Off] = cond.state_off;
    conditions[ModeCondition::On2Fault] = cond.state_fault;
    conditions[ModeCondition::Fault2Inhibit] = cond.fault2inhibit;
  }

  bool isConditionActive(ModeCondition condition) const override {
    auto it = conditions.find(condition);
    return it != conditions.end() ? it->second : false;
  }
};

class ModeManager : public StateMachine<ModeState, ModeCondition> {
public:
  ModeManager() {
    // 创建顶层状态
    addState(std::make_unique<SimpleState<ModeState, ModeCondition>>(
        ModeState::OFF));
    addState(std::make_unique<SimpleState<ModeState, ModeCondition>>(
        ModeState::FAULT));
    //创建复合状态:包含子状态
    auto onState = std::make_unique<CompositeState<ModeState, ModeCondition>>(
        ModeState::ON);
    onState->setInitialState(ModeState::INHIBIT);

    onState->addState(std::make_unique<SimpleState<ModeState, ModeCondition>>(
        ModeState::INHIBIT));
    onState->addState(std::make_unique<SimpleState<ModeState, ModeCondition>>(
        ModeState::STANDBY));
    onState->addState(std::make_unique<SimpleState<ModeState, ModeCondition>>(
        ModeState::ACTIVE));

    // 添加On状态的内部转换
    onState->addTransition(ModeState::INHIBIT, ModeState::STANDBY,
                           ModeCondition::Inhibit2Standby);
    onState->addTransition(ModeState::INHIBIT, ModeState::ACTIVE,
                           ModeCondition::Inhibit2Active);
    onState->addTransition(ModeState::STANDBY, ModeState::INHIBIT,
                           ModeCondition::Standby2Inhibit);
    onState->addTransition(ModeState::STANDBY, ModeState::ACTIVE,
                           ModeCondition::Standby2Active);
    onState->addTransition(ModeState::ACTIVE, ModeState::STANDBY,
                           ModeCondition::Active2Standby);
    onState->addTransition(ModeState::ACTIVE, ModeState::INHIBIT,
                           ModeCondition::Active2Inhibit);

    addState(std::move(onState));

    // 添加顶层转换
    addTransition(ModeState::OFF, ModeState::ON, ModeCondition::Off2Inhibit);
    addTransition(ModeState::ON, ModeState::OFF, ModeCondition::On2Off);
    addTransition(ModeState::ON, ModeState::FAULT, ModeCondition::On2Fault);
    addTransition(ModeState::FAULT, ModeState::ON,
                  ModeCondition::Fault2Inhibit);

    // 初始化状态机
    ModeConditionContext ctx;
    initialize(ModeState::ON, ctx);
  }

  ModeState getCurrentSubState() const {
    if (getCurrentStateId() == ModeState::ON) {
      if (auto composite =
              dynamic_cast<const CompositeState<ModeState, ModeCondition> *>(
                  currentState)) {
        return composite->getCurrentStateId();
      }
    }
    return ModeState::OFF;
  }
};
} // namespace math
} // namespace active_safety
#endif // TAP_SDK_MATH_STATEMACHINE_MODEMANAGER_HPP_
