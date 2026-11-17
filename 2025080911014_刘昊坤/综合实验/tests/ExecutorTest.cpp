#include "Executor.hpp"
#include "PoseEq.hpp"

#include <gtest/gtest.h>
#include <memory>
#include <string>

namespace adas {
namespace {

std::unique_ptr<Executor> MakeExecutor(const Pose& pose = {0, 0, 'N'})
{
    std::unique_ptr<Executor> executor(Executor::NewExecutor(pose));
    EXPECT_NE(executor, nullptr);
    return executor;
}

void ExpectPose(Executor& executor, const Pose& expected)
{
    ASSERT_EQ(expected, executor.Query());
}

TEST(ExecutorTest, should_return_default_pose)
{
    auto executor = MakeExecutor();
    ASSERT_NE(executor, nullptr);
    ExpectPose(*executor, {0, 0, 'N'});
}

TEST(ExecutorTest, should_return_initial_pose_without_command)
{
    auto executor = MakeExecutor({3, -2, 'W'});
    ASSERT_NE(executor, nullptr);
    ExpectPose(*executor, {3, -2, 'W'});
}

TEST(ExecutorTest, should_keep_pose_for_empty_command)
{
    auto executor = MakeExecutor({1, 2, 'S'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("");
    ExpectPose(*executor, {1, 2, 'S'});
}

TEST(ExecutorTest, should_move_east)
{
    auto executor = MakeExecutor({0, 0, 'E'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("M");
    ExpectPose(*executor, {1, 0, 'E'});
}

TEST(ExecutorTest, should_move_west)
{
    auto executor = MakeExecutor({0, 0, 'W'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("M");
    ExpectPose(*executor, {-1, 0, 'W'});
}

TEST(ExecutorTest, should_move_north)
{
    auto executor = MakeExecutor({0, 0, 'N'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("M");
    ExpectPose(*executor, {0, 1, 'N'});
}

TEST(ExecutorTest, should_move_south)
{
    auto executor = MakeExecutor({0, 0, 'S'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("M");
    ExpectPose(*executor, {0, -1, 'S'});
}

TEST(ExecutorTest, should_turn_left_from_east)
{
    auto executor = MakeExecutor({0, 0, 'E'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("L");
    ExpectPose(*executor, {0, 0, 'N'});
}

TEST(ExecutorTest, should_turn_left_from_north)
{
    auto executor = MakeExecutor({0, 0, 'N'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("L");
    ExpectPose(*executor, {0, 0, 'W'});
}

TEST(ExecutorTest, should_turn_left_from_west)
{
    auto executor = MakeExecutor({0, 0, 'W'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("L");
    ExpectPose(*executor, {0, 0, 'S'});
}

TEST(ExecutorTest, should_turn_left_from_south)
{
    auto executor = MakeExecutor({0, 0, 'S'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("L");
    ExpectPose(*executor, {0, 0, 'E'});
}

TEST(ExecutorTest, should_turn_right_from_east)
{
    auto executor = MakeExecutor({0, 0, 'E'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("R");
    ExpectPose(*executor, {0, 0, 'S'});
}

TEST(ExecutorTest, should_turn_right_from_south)
{
    auto executor = MakeExecutor({0, 0, 'S'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("R");
    ExpectPose(*executor, {0, 0, 'W'});
}

TEST(ExecutorTest, should_turn_right_from_west)
{
    auto executor = MakeExecutor({0, 0, 'W'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("R");
    ExpectPose(*executor, {0, 0, 'N'});
}

TEST(ExecutorTest, should_turn_right_from_north)
{
    auto executor = MakeExecutor({0, 0, 'N'});
    ASSERT_NE(executor, nullptr);
    executor->Execute("R");
    ExpectPose(*executor, {0, 0, 'E'});
}

TEST(ExecutorTest, should_execute_batch_commands)
{
    auto executor = MakeExecutor();
    ASSERT_NE(executor, nullptr);
    executor->Execute("MLMMRM");
    ExpectPose(*executor, {-2, 2, 'N'});
}

TEST(ExecutorTest, should_execute_commands_across_multiple_calls)
{
    auto executor = MakeExecutor();
    ASSERT_NE(executor, nullptr);
    executor->Execute("MM");
    executor->Execute("RM");
    ExpectPose(*executor, {1, 2, 'E'});
}

}  // namespace
}  // namespace adas
