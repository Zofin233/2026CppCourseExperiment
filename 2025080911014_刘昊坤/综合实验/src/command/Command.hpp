#pragma once

#include "ActionGroup.hpp"

namespace adas {

inline ActionType MoveAction(const PoseHandler& poseHandler) noexcept
{
    return poseHandler.IsReverse() ? ActionType::BACKWARD_1_STEP_ACTION
                                   : ActionType::FORWARD_1_STEP_ACTION;
}

inline ActionType LeftAction(const PoseHandler& poseHandler) noexcept
{
    return poseHandler.IsReverse() ? ActionType::REVERSE_TURNLEFT_ACTION : ActionType::TURNLEFT_ACTION;
}

inline ActionType RightAction(const PoseHandler& poseHandler) noexcept
{
    return poseHandler.IsReverse() ? ActionType::REVERSE_TURNRIGHT_ACTION : ActionType::TURNRIGHT_ACTION;
}

inline void PushMove(ActionGroup& group, const PoseHandler& poseHandler) noexcept
{
    group.PushAction(MoveAction(poseHandler));
}

class MoveCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        const int baseSteps = poseHandler.GetVehicleType() == VehicleType::Sport ? 2 : 1;
        const int steps = poseHandler.IsFast() ? baseSteps * 2 : baseSteps;
        for (int i = 0; i < steps; ++i) {
            PushMove(group, poseHandler);
        }
        return group;
    }
};

class TurnLeftCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        switch (poseHandler.GetVehicleType()) {
        case VehicleType::Sport:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            group.PushAction(LeftAction(poseHandler));
            PushMove(group, poseHandler);
            break;
        case VehicleType::Bus:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            PushMove(group, poseHandler);
            group.PushAction(LeftAction(poseHandler));
            break;
        case VehicleType::Normal:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            group.PushAction(LeftAction(poseHandler));
            break;
        }
        return group;
    }
};

class TurnRightCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        ActionGroup group;
        switch (poseHandler.GetVehicleType()) {
        case VehicleType::Sport:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            group.PushAction(RightAction(poseHandler));
            PushMove(group, poseHandler);
            break;
        case VehicleType::Bus:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            PushMove(group, poseHandler);
            group.PushAction(RightAction(poseHandler));
            break;
        case VehicleType::Normal:
            if (poseHandler.IsFast()) {
                PushMove(group, poseHandler);
            }
            group.PushAction(RightAction(poseHandler));
            break;
        }
        return group;
    }
};

class FastCommand final {
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        return ActionGroup{ActionType::BE_FAST_ACTION};
    }
};

class ReverseCommand final {
public:
    ActionGroup operator()(PoseHandler&) const noexcept
    {
        return ActionGroup{ActionType::BE_REVERSE_ACTION};
    }
};

class TurnRoundCommand final {
public:
    ActionGroup operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            return ActionGroup{ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION,
                               ActionType::FORWARD_1_STEP_ACTION, ActionType::TURNLEFT_ACTION};
        }
        return ActionGroup{ActionType::TURNLEFT_ACTION, ActionType::FORWARD_1_STEP_ACTION,
                           ActionType::TURNLEFT_ACTION};
    }
};

}  // namespace adas
