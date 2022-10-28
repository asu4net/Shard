#pragma once
#include <string>

namespace Shard
{
    class SHARD_API Object
    {
    public:
        virtual std::string ToString() const
        {
            return "Base Object";
        }
    };
}