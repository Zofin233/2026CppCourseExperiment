#include "Executor.hpp"
#include "PoseEq.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace adas {
namespace {

void ExpectTurnRoundResult(const std::string& commands, const Pose& expected,
                           const VehicleType type = VehicleType::Normal)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}, type));
    ASSERT_NE(executor, nullptr);
    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorTurnRoundTest, should_turn_left_move_left_in_normal_state)
{
    ExpectTurnRoundResult("TR", {0, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, should_move_left_move_left_in_fast_state)
{
    ExpectTurnRoundResult("FTR", {1, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, should_ignore_reverse_state)
{
    ExpectTurnRoundResult("BTR", {0, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, should_use_fast_sequence_when_fast_and_reversing)
{
    ExpectTurnRoundResult("BFTR", {1, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, should_support_batch_and_multiple_turn_rounds)
{
    ExpectTurnRoundResult("TRTRM", {1, 0, 'E'});
}

TEST(ExecutorTurnRoundTest, should_preserve_reverse_state_after_turn_round)
{
    ExpectTurnRoundResult("BTRM", {1, 1, 'W'});
}

TEST(ExecutorTurnRoundTest, should_use_same_turn_round_for_sport_and_bus)
{
    ExpectTurnRoundResult("TR", {0, 1, 'W'}, VehicleType::Sport);
    ExpectTurnRoundResult("FTR", {1, 1, 'W'}, VehicleType::Bus);
}

}  // namespace
}  // namespace adas
