#pragma once
#include <string>

namespace Shard
{
    class Object
    {
    public:
        virtual std::string ToString() const
        {
            return "Base Object";
        }
    };
}