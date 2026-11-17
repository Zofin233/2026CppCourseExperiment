#include "Direction.hpp"

namespace adas {
namespace {

const Direction directions[4] = {{0, 'E'}, {1, 'S'}, {2, 'W'}, {3, 'N'}};
const Point moveVectors[4] = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};

}  // namespace

const Direction& Direction::GetDirection(const char heading) noexcept
{
    for (const auto& direction : directions) {
        if (direction.heading == heading) {
            return direction;
        }
    }
    return directions[3];
}

Direction::Direction(const unsigned index, const char heading) noexcept : index(index), heading(heading)
{
}

const Point& Direction::Move() const noexcept
{
    return moveVectors[index];
}

const Direction& Direction::LeftOne() const noexcept
{
    return directions[(index + 3) % 4];
}

const Direction& Direction::RightOne() const noexcept
{
    return directions[(index + 1) % 4];
}

char Direction::GetHeading() const noexcept
{
    return heading;
}

}  // namespace adas
