#include "Point.hpp"

namespace adas {

Point::Point(const std::int32_t x, const std::int32_t y) noexcept : x(x), y(y)
{
}

Point& Point::operator+=(const Point& rhs) noexcept
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

std::int32_t Point::GetX() const noexcept
{
    return x;
}

std::int32_t Point::GetY() const noexcept
{
    return y;
}

}  // namespace adas
