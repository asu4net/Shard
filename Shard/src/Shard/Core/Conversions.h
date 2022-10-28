#pragma once
#include <string>
#include <sstream>

namespace Shard
{
    template <typename T>
    std::string StringFromNumber(T _value) {
        std::ostringstream stream;
        stream << std::fixed << _value;
        return stream.str();
    }
}