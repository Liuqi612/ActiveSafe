#ifndef TAP_SDK_MATH_STATEMACHINE_STATE_HPP_
#define TAP_SDK_MATH_STATEMACHINE_STATE_HPP_
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <type_traits>
namespace active_safety {
namespace math {

// 统一标识模板接口
template <typename T>
class IIdentifier {
 public:
    virtual ~IIdentifier() = default;
    virtual T getValue() const = 0;
    virtual bool equals(const IIdentifier &other) const = 0;
    virtual bool lessThan(const IIdentifier &other) const = 0;

    bool operator==(const IIdentifier &other) const { return equals(other); }
    bool operator<(const IIdentifier &other) const { return lessThan(other); }
};

// 枚举标识实现:可根据此自定义状态和事件
template <typename T>
class EnumIdentifier : public IIdentifier<T> {
    T value;

 public:
    EnumIdentifier(T val) : value(val) {}
    //获取状态/事件值
    T getValue() const override { return value; }
    //判断是否相等
    bool equals(const IIdentifier<T> &other) const override {
        auto derived = dynamic_cast<const EnumIdentifier *>(&other);
        return derived && value == derived->value;
    }
    bool lessThan(const IIdentifier<T> &other) const override {
        auto derived = dynamic_cast<const EnumIdentifier *>(&other);
        return derived && value < derived->value;
    }
};

// 前向声明
template <typename StateEnum, typename ConditionEnum>
class IState;

// 条件上下文
template <typename ConditionEnum>
class IConditionContext {
 public:
    virtual ~IConditionContext() = default;
    virtual bool isConditionActive(ConditionEnum condition) const = 0;
};

// 状态接口
template <typename StateEnum, typename ConditionEnum>
class IState {
 public:
    virtual ~IState() = default;
    virtual void enter(IConditionContext<ConditionEnum> &context) = 0;
    virtual void exit(IConditionContext<ConditionEnum> &context) = 0;
    virtual void update(IConditionContext<ConditionEnum> &context) = 0;
    virtual StateEnum getStateId() const = 0;
    virtual bool isComposite() const = 0;
    virtual IState<StateEnum, ConditionEnum> *getCurrentSubState() = 0;
    virtual const IState<StateEnum, ConditionEnum> *getCurrentSubState()
        const = 0;
};

// 状态机接口
template <typename StateEnum, typename ConditionEnum>
class IStateMachine {
 public:
    virtual ~IStateMachine() = default;

    virtual void initialize(StateEnum initialState,
                            IConditionContext<ConditionEnum> &context) = 0;
    virtual void update(IConditionContext<ConditionEnum> &context) = 0;

    virtual StateEnum getCurrentStateId() const = 0;

    virtual void addState(
        std::unique_ptr<IState<StateEnum, ConditionEnum>> state) = 0;
    virtual bool hasState(StateEnum stateId) const = 0;

    virtual void addTransition(
        StateEnum from,
        StateEnum to,
        ConditionEnum condition,
        std::function<void(IConditionContext<ConditionEnum> &)> action =
            nullptr) = 0;
};

}  // namespace math
}  // namespace active_safety
#endif // TAP_SDK_MATH_STATEMACHINE_STATE_HPP_
