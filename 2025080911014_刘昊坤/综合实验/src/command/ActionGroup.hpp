#pragma once

#include "core/PoseHandler.hpp"

#include <cstdint>
#include <initializer_list>
#include <vector>

namespace adas {

enum class ActionType : std::uint16_t {
    FORWARD_1_STEP_ACTION = 0,
    BACKWARD_1_STEP_ACTION,
    TURNLEFT_ACTION,
    REVERSE_TURNLEFT_ACTION,
    TURNRIGHT_ACTION,
    REVERSE_TURNRIGHT_ACTION,
    BE_FAST_ACTION,
    BE_REVERSE_ACTION,
};

class ActionGroup final {
public:
    ActionGroup() = default;
    explicit ActionGroup(std::initializer_list<ActionType> actions) noexcept;

    void PushAction(ActionType action) noexcept;
    void DoOperate(PoseHandler& poseHandler) const noexcept;

private:
    std::vector<ActionType> actions;
};

}  // namespace adas
