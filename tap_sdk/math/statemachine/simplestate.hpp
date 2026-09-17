/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_MATH_STATEMACHINE_SIMPLESTATE_HPP_
#define TAP_SDK_MATH_STATEMACHINE_SIMPLESTATE_HPP_
#include "statemachine.hpp"
namespace active_safety {
namespace math {
/*此状态机里支持单一状态，并且由StateEnum定义状态名，ConditionEnum定义跳转条件*/
template <typename StateEnum, typename ConditionEnum>
class SimpleState : public IState<StateEnum, ConditionEnum> {
    StateEnum stateId;

 public:
    SimpleState(StateEnum id) : stateId(id) {}

    void enter(IConditionContext<ConditionEnum>& context) override {
        (void)context;
    }

    void exit(IConditionContext<ConditionEnum>& context) override {
        (void)context;
    }

    void update(IConditionContext<ConditionEnum>& context) override {
        (void)context;
    }

    StateEnum getStateId() const override { return stateId; }

    bool isComposite() const override { return false; }

    IState<StateEnum, ConditionEnum>* getCurrentSubState() override {
        //此状态不包含子状态，所以返回空指针
        return nullptr;
    }
    const IState<StateEnum, ConditionEnum>* getCurrentSubState()
        const override {
        //此状态不包含子状态，所以返回空指针
        return nullptr;
    }
};
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_STATEMACHINE_SIMPLESTATE_HPP_
