#pragma once
#include "Core.h"

namespace Shard::Math
{
    struct SHARD_API Color
    {
        float r, g, b, a;

        Color()
            : r(0)
            , g(0)
            , b(0)
            , a(1)
        {}

        Color(float _r, float _g, float _b, float _a = 1)
            : r(_r)
            , g(_g)
            , b(_b)
            , a(_a)
        {}
    };
}
