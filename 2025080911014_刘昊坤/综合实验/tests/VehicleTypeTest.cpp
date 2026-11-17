#include "Executor.hpp"
#include "PoseEq.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace adas {
namespace {

void ExpectVehicleResult(const VehicleType type, const std::string& commands, const Pose& expected)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, type));
    ASSERT_NE(executor, nullptr);
    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}

TEST(VehicleTypeTest, sport_should_move_two_steps)
{
    ExpectVehicleResult(VehicleType::Sport, "M", {2, 0, 'E'});
}

TEST(VehicleTypeTest, sport_should_turn_left_then_move)
{
    ExpectVehicleResult(VehicleType::Sport, "L", {0, 1, 'N'});
}

TEST(VehicleTypeTest, sport_should_turn_right_then_move)
{
    ExpectVehicleResult(VehicleType::Sport, "R", {0, -1, 'S'});
}

TEST(VehicleTypeTest, sport_should_reverse_two_steps)
{
    ExpectVehicleResult(VehicleType::Sport, "BM", {-2, 0, 'E'});
}

TEST(VehicleTypeTest, sport_should_turn_right_then_reverse_for_left_command)
{
    ExpectVehicleResult(VehicleType::Sport, "BL", {0, 1, 'S'});
}

TEST(VehicleTypeTest, sport_should_turn_left_then_reverse_for_right_command)
{
    ExpectVehicleResult(VehicleType::Sport, "BR", {0, -1, 'N'});
}

TEST(VehicleTypeTest, sport_should_move_four_steps_when_fast)
{
    ExpectVehicleResult(VehicleType::Sport, "FM", {4, 0, 'E'});
}

TEST(VehicleTypeTest, sport_should_move_turn_move_when_fast_left)
{
    ExpectVehicleResult(VehicleType::Sport, "FL", {1, 1, 'N'});
}

TEST(VehicleTypeTest, sport_should_move_turn_move_when_fast_right)
{
    ExpectVehicleResult(VehicleType::Sport, "FR", {1, -1, 'S'});
}

TEST(VehicleTypeTest, sport_should_reverse_four_steps_when_fast_and_reversing)
{
    ExpectVehicleResult(VehicleType::Sport, "BFM", {-4, 0, 'E'});
}

TEST(VehicleTypeTest, sport_should_reverse_turn_reverse_when_fast_and_reversing_left)
{
    ExpectVehicleResult(VehicleType::Sport, "BFL", {-1, 1, 'S'});
}

TEST(VehicleTypeTest, sport_should_reverse_turn_reverse_when_fast_and_reversing_right)
{
    ExpectVehicleResult(VehicleType::Sport, "BFR", {-1, -1, 'N'});
}

TEST(VehicleTypeTest, bus_should_move_one_step)
{
    ExpectVehicleResult(VehicleType::Bus, "M", {1, 0, 'E'});
}

TEST(VehicleTypeTest, bus_should_move_then_turn_left)
{
    ExpectVehicleResult(VehicleType::Bus, "L", {1, 0, 'N'});
}

TEST(VehicleTypeTest, bus_should_move_then_turn_right)
{
    ExpectVehicleResult(VehicleType::Bus, "R", {1, 0, 'S'});
}

TEST(VehicleTypeTest, bus_should_reverse_one_step)
{
    ExpectVehicleResult(VehicleType::Bus, "BM", {-1, 0, 'E'});
}

TEST(VehicleTypeTest, bus_should_reverse_then_turn_right_for_left_command)
{
    ExpectVehicleResult(VehicleType::Bus, "BL", {-1, 0, 'S'});
}

TEST(VehicleTypeTest, bus_should_reverse_then_turn_left_for_right_command)
{
    ExpectVehicleResult(VehicleType::Bus, "BR", {-1, 0, 'N'});
}

TEST(VehicleTypeTest, bus_should_move_two_steps_when_fast)
{
    ExpectVehicleResult(VehicleType::Bus, "FM", {2, 0, 'E'});
}

TEST(VehicleTypeTest, bus_should_move_two_steps_then_turn_left_when_fast)
{
    ExpectVehicleResult(VehicleType::Bus, "FL", {2, 0, 'N'});
}

TEST(VehicleTypeTest, bus_should_move_two_steps_then_turn_right_when_fast)
{
    ExpectVehicleResult(VehicleType::Bus, "FR", {2, 0, 'S'});
}

TEST(VehicleTypeTest, bus_should_reverse_two_steps_when_fast_and_reversing)
{
    ExpectVehicleResult(VehicleType::Bus, "BFM", {-2, 0, 'E'});
}

TEST(VehicleTypeTest, bus_should_reverse_two_steps_then_turn_right_when_fast_and_reversing_left)
{
    ExpectVehicleResult(VehicleType::Bus, "BFL", {-2, 0, 'S'});
}

TEST(VehicleTypeTest, bus_should_reverse_two_steps_then_turn_left_when_fast_and_reversing_right)
{
    ExpectVehicleResult(VehicleType::Bus, "BFR", {-2, 0, 'N'});
}

}  // namespace
}  // namespace adas
