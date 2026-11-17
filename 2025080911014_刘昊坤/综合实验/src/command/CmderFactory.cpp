#include "CmderFactory.hpp"

namespace adas {

CmderList CmderFactory::GetCmders(const std::string& commands) const noexcept
{
    CmderList cmders;
    for (const char command : ParseCommandString(commands)) {
        const auto it = cmderMap.find(command);
        if (it != cmderMap.end()) {
            cmders.push_back(it->second);
        }
    }
    return cmders;
}

std::string CmderFactory::ParseCommandString(const std::string_view commands) const noexcept
{
    std::string result(commands);
    ReplaceAll(result, "TR", "Z");
    return result;
}

void CmderFactory::ReplaceAll(std::string& inout, const std::string_view what,
                              const std::string_view with) const noexcept
{
    for (std::string::size_type pos{}; (pos = inout.find(what.data(), pos, what.length())) != std::string::npos;
         pos += with.length()) {
        inout.replace(pos, what.length(), with.data(), with.length());
    }
}

}  // namespace adas
