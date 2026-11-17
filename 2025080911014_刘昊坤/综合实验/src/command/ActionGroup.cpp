#include "ActionGroup.hpp"

#include <array>
#include <functional>

namespace adas {
namespace {

using Action = std::function<void(PoseHandler&)>;

class ForwardAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Forward(); }
};

class BackwardAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Backward(); }
};

class TurnLeftAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.TurnLeft(); }
};

class ReverseTurnLeftAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.TurnRight(); }
};

class TurnRightAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.TurnRight(); }
};

class ReverseTurnRightAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.TurnLeft(); }
};

class BeFastAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Fast(); }
};

class BeReverseAction final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept { poseHandler.Reverse(); }
};

}  // namespace

ActionGroup::ActionGroup(std::initializer_list<ActionType> actions) noexcept : actions(actions)
{
}

void ActionGroup::PushAction(const ActionType action) noexcept
{
    actions.push_back(action);
}

void ActionGroup::DoOperate(PoseHandler& poseHandler) const noexcept
{
    static const std::array<Action, 8> actionTable = {
        ForwardAction(),          BackwardAction(),     TurnLeftAction(), ReverseTurnLeftAction(),
        TurnRightAction(),        ReverseTurnRightAction(), BeFastAction(), BeReverseAction(),
    };

    for (const ActionType action : actions) {
        actionTable.at(static_cast<std::uint16_t>(action))(poseHandler);
    }
}

}  // namespace adas
