#pragma once

#include "PoseHandler.hpp"

#include <functional>

namespace adas {

using Command = std::function<void(PoseHandler&)>;

inline void MoveOnce(PoseHandler& poseHandler) noexcept
{
    if (poseHandler.IsReverse()) {
        poseHandler.Backward();
    } else {
        poseHandler.Forward();
    }
}

class MoveCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            MoveOnce(poseHandler);
        }
        MoveOnce(poseHandler);
    }
};

class TurnLeftCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            MoveOnce(poseHandler);
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();
        } else {
            poseHandler.TurnLeft();
        }
    }
};

class TurnRightCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        if (poseHandler.IsFast()) {
            MoveOnce(poseHandler);
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnLeft();
        } else {
            poseHandler.TurnRight();
        }
    }
};

class FastCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};

class ReverseCommand final {
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};

}  // namespace adas
