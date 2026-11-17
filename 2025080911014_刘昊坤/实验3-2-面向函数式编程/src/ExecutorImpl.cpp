#include "ExecutorImpl.hpp"
#include "Command.hpp"

#include <unordered_map>

namespace adas {

ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}

void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    const std::unordered_map<char, Command> cmderMap{
        {'M', MoveCommand()},
        {'L', TurnLeftCommand()},
        {'R', TurnRightCommand()},
        {'F', FastCommand()},
        {'B', ReverseCommand()},
    };

    for (const char command : commands) {
        const auto it = cmderMap.find(command);
        if (it != cmderMap.end()) {
            it->second(poseHandler);
        }
    }
}

Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}

}  // namespace adas
