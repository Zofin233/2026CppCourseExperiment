#pragma once

#include <cstdint>

namespace adas {

class Point final {
public:
    Point(std::int32_t x, std::int32_t y) noexcept;
    Point(const Point& rhs) noexcept = default;
    Point& operator=(const Point& rhs) noexcept = default;
    Point& operator+=(const Point& rhs) noexcept;
    Point& operator-=(const Point& rhs) noexcept;

    std::int32_t GetX() const noexcept;
    std::int32_t GetY() const noexcept;

private:
    std::int32_t x;
    std::int32_t y;
};

}  // namespace adas
