#include "Executor.hpp"
#include "PoseEq.hpp"

#include <gtest/gtest.h>
#include <memory>

namespace adas {
namespace {

void ExpectFastCommandResult(const Pose& initial, const std::string& commands, const Pose& expected)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor(initial));
    ASSERT_NE(executor, nullptr);
    executor->Execute(commands);
    ASSERT_EQ(expected, executor->Query());
}

TEST(ExecutorFastTest, should_move_two_steps_when_fast)
{
    ExpectFastCommandResult({0, 0, 'E'}, "FM", {2, 0, 'E'});
}

TEST(ExecutorFastTest, should_move_before_fast_left_turn)
{
    ExpectFastCommandResult({0, 0, 'E'}, "FL", {1, 0, 'N'});
}

TEST(ExecutorFastTest, should_move_before_fast_right_turn)
{
    ExpectFastCommandResult({0, 0, 'E'}, "FR", {1, 0, 'S'});
}

TEST(ExecutorFastTest, should_cancel_fast_state)
{
    ExpectFastCommandResult({0, 0, 'N'}, "FFM", {0, 1, 'N'});
}

TEST(ExecutorFastTest, should_keep_fast_state_across_calls)
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));
    ASSERT_NE(executor, nullptr);
    executor->Execute("F");
    executor->Execute("M");
    ASSERT_EQ((Pose{2, 0, 'E'}), executor->Query());
}

}  // namespace
}  // namespace adas
