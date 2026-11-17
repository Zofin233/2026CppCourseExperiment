#include "Executor.hpp"
#include "ExecutorImpl.hpp"

#include <new>

namespace adas {

Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}

}  // namespace adas
