/*
 * Copyright (C) 2020 by SenseTime Group Limited. All rights reserved.
 */
#ifndef TAP_SDK_MATH_STATEMACHINE_STATEMACHINE_HPP_
#define TAP_SDK_MATH_STATEMACHINE_STATEMACHINE_HPP_
#include "state.hpp"
#include <unordered_map>
#include <map>
#include <vector>
namespace active_safety {
namespace math {

/*基础状态机类实现*/

template <typename StateEnum, typename ConditionEnum>
class StateMachine : public IStateMachine<StateEnum, ConditionEnum> {
 protected:
    struct Transition {
        StateEnum targetState;
        ConditionEnum condition;
        std::function<void(IConditionContext<ConditionEnum>&)> action;
    };

    std::unordered_map<StateEnum,
                       std::unique_ptr<IState<StateEnum, ConditionEnum>>>
        states;
    std::unordered_map<StateEnum, std::vector<Transition>> transitions;
    IState<StateEnum, ConditionEnum>* currentState = nullptr;
    StateEnum currentStateId;

 public:
    virtual ~StateMachine() = default;

    void initialize(StateEnum initialState,
                    IConditionContext<ConditionEnum>& context) override {
        auto it = states.find(initialState);
        if (it != states.end()) {
            currentStateId = initialState;
            currentState = it->second.get();
            currentState->enter(context);
        }
    }

    void update(IConditionContext<ConditionEnum>& context) override {
        if (!currentState) return;

        currentState->update(context);

        auto transIt = transitions.find(currentStateId);
        if (transIt != transitions.end()) {
            for (const auto& trans : transIt->second) {
                if (context.isConditionActive(trans.condition)) {
                    auto targetIt = states.find(trans.targetState);
                    if (targetIt != states.end()) {
                        currentState->exit(context);

                        if (trans.action) {
                            trans.action(context);
                        }

                        currentStateId = trans.targetState;
                        currentState = targetIt->second.get();
                        currentState->enter(context);
                        break;
                    }
                }
            }
        }
    }

    StateEnum getCurrentStateId() const override { return currentStateId; }

    void addState(
        std::unique_ptr<IState<StateEnum, ConditionEnum>> state) override {
        states[state->getStateId()] = std::move(state);
    }

    bool hasState(StateEnum stateId) const override {
        return states.find(stateId) != states.end();
    }

    void addTransition(StateEnum from,
                       StateEnum to,
                       ConditionEnum condition,
                       std::function<void(IConditionContext<ConditionEnum>&)>
                           action = nullptr) override {
        if (!hasState(from)) {
            std::cout << "Warning: Source state not found for transition!"
                      << std::endl;
            return;
        }

        if (!hasState(to)) {
            std::cout << "Warning: Target state not found for transition!"
                      << std::endl;
            return;
        }

        transitions[from].push_back({to, condition, action});
    }
};
}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_STATEMACHINE_STATEMACHINE_HPP_
