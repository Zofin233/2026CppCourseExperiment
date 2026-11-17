#include "Executor.hpp"
#include "PoseEq.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace adas {
namespace {

void ExpectCommandResult(const Pose& initial, const std::string& commands, const Pose& expected)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor(initial));
    ASSERT_NE(executor, nullptr);
    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorReverseTest, should_move_backward_without_changing_heading)
{
    ExpectCommandResult({0, 0, 'E'}, "BM", {-1, 0, 'E'});
}

TEST(ExecutorReverseTest, should_turn_right_for_left_command_when_reversing)
{
    ExpectCommandResult({0, 0, 'E'}, "BL", {0, 0, 'S'});
}

TEST(ExecutorReverseTest, should_turn_left_for_right_command_when_reversing)
{
    ExpectCommandResult({0, 0, 'E'}, "BR", {0, 0, 'N'});
}

TEST(ExecutorReverseTest, should_move_backward_two_steps_when_fast_and_reversing)
{
    ExpectCommandResult({0, 0, 'E'}, "BFM", {-2, 0, 'E'});
}

TEST(ExecutorReverseTest, should_move_backward_before_right_turn_when_fast_and_reversing)
{
    ExpectCommandResult({0, 0, 'E'}, "BFL", {-1, 0, 'S'});
}

TEST(ExecutorReverseTest, should_move_backward_before_left_turn_when_fast_and_reversing)
{
    ExpectCommandResult({0, 0, 'E'}, "BFR", {-1, 0, 'N'});
}

TEST(ExecutorReverseTest, should_cancel_reverse_state)
{
    ExpectCommandResult({0, 0, 'N'}, "BBM", {0, 1, 'N'});
}

TEST(ExecutorReverseTest, should_cancel_reverse_without_cancelling_fast)
{
    ExpectCommandResult({0, 0, 'E'}, "BFBM", {2, 0, 'E'});
}

TEST(ExecutorReverseTest, should_cancel_fast_without_cancelling_reverse)
{
    ExpectCommandResult({0, 0, 'E'}, "BFFM", {-1, 0, 'E'});
}

TEST(ExecutorReverseTest, should_keep_reverse_state_across_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}));
    ASSERT_NE(executor, nullptr);
    executor->Execute("B");
    executor->Execute("M");
    ASSERT_EQ((Pose{0, -1, 'N'}), executor->Query());
}

}  // namespace
}  // namespace adas
