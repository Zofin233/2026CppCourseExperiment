#include "PoseHandler.hpp"

namespace adas {

PoseHandler::PoseHandler(const Pose& pose, const VehicleType type) noexcept
    : point(pose.x, pose.y), facing(&Direction::GetDirection(pose.heading)), type(type)
{
}

void PoseHandler::Forward() noexcept
{
    point += facing->Move();
}

void PoseHandler::Backward() noexcept
{
    point -= facing->Move();
}

void PoseHandler::TurnLeft() noexcept
{
    facing = &facing->LeftOne();
}

void PoseHandler::TurnRight() noexcept
{
    facing = &facing->RightOne();
}

void PoseHandler::Fast() noexcept
{
    fast = !fast;
}

void PoseHandler::Reverse() noexcept
{
    reverse = !reverse;
}

bool PoseHandler::IsFast() const noexcept
{
    return fast;
}

bool PoseHandler::IsReverse() const noexcept
{
    return reverse;
}

VehicleType PoseHandler::GetVehicleType() const noexcept
{
    return type;
}

Pose PoseHandler::Query() const noexcept
{
    return {point.GetX(), point.GetY(), facing->GetHeading()};
}

}  // namespace adas
