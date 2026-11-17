#include "Executor.hpp"
#include "ExecutorImpl.hpp"

#include <new>

namespace adas {

Executor* Executor::NewExecutor(const Pose& pose, const VehicleType type) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose, type);
}

}  // namespace adas
