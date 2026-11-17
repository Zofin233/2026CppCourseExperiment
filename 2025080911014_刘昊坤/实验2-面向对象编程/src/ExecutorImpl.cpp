#include "ExecutorImpl.hpp"

#include <memory>

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose& initialPose) noexcept : pose(initialPose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const char command : commands) {
        std::unique_ptr<ICommand> cmder;
        if (command == 'M') {
            cmder = std::make_unique<MoveCommand>();
        } else if (command == 'L') {
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (command == 'R') {
            cmder = std::make_unique<TurnRightCommand>();
        } else if (command == 'F') {
            cmder = std::make_unique<FastCommand>();
        }
        if (cmder) {
            cmder->DoOperate(*this);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}

void ExecutorImpl::Move() noexcept
{
    switch (pose.heading) {
    case 'E':
        ++pose.x;
        break;
    case 'W':
        --pose.x;
        break;
    case 'N':
        ++pose.y;
        break;
    case 'S':
        --pose.y;
        break;
    default:
        break;
    }
}

void ExecutorImpl::TurnLeft() noexcept
{
    switch (pose.heading) {
    case 'E':
        pose.heading = 'N';
        break;
    case 'N':
        pose.heading = 'W';
        break;
    case 'W':
        pose.heading = 'S';
        break;
    case 'S':
        pose.heading = 'E';
        break;
    default:
        break;
    }
}

void ExecutorImpl::TurnRight() noexcept
{
    switch (pose.heading) {
    case 'E':
        pose.heading = 'S';
        break;
    case 'S':
        pose.heading = 'W';
        break;
    case 'W':
        pose.heading = 'N';
        break;
    case 'N':
        pose.heading = 'E';
        break;
    default:
        break;
    }
}

void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}

bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

}  // namespace adas
