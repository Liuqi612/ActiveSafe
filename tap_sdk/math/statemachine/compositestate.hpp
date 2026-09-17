/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_MATH_STATEMACHINE_COMPOSITESTATE_HPP_
#define TAP_SDK_MATH_STATEMACHINE_COMPOSITESTATE_HPP_
#include "statemachine.hpp"
namespace active_safety {
namespace math {
/*此类支持状态里包含子状态*/
template <typename StateEnum, typename ConditionEnum>
class CompositeState : public IState<StateEnum, ConditionEnum>,
                       public StateMachine<StateEnum, ConditionEnum> {
    StateEnum stateId;
    StateEnum initialStateId;

 public:
    CompositeState(StateEnum id) : stateId(id) {}

    void setInitialState(StateEnum id) { initialStateId = id; }

    void enter(IConditionContext<ConditionEnum>& context) override {
        StateMachine<StateEnum, ConditionEnum>::initialize(initialStateId,
                                                           context);
    }

    void exit(IConditionContext<ConditionEnum>& context) override {
        if (this->currentState) {
            this->currentState->exit(context);
            this->currentState = nullptr;
        }
    }

    void update(IConditionContext<ConditionEnum>& context) override {
        StateMachine<StateEnum, ConditionEnum>::update(context);
    }

    StateEnum getStateId() const override { return stateId; }

    bool isComposite() const override { return true; }

    IState<StateEnum, ConditionEnum>* getCurrentSubState() override {
        return this->currentState;
    }
    const IState<StateEnum, ConditionEnum>* getCurrentSubState()
        const override {
        return this->currentState;
    }
};
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_STATEMACHINE_COMPOSITESTATE_HPP_
