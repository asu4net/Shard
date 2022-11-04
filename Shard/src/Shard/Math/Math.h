#pragma once

#include "Color.h"
#include "Vector2.h"
#include "Vector3.h"

constexpr float g_Radians = 0.0174533f;

namespace Shard::Math
{
    template <typename T>
    int Sign(T val)
    {
        return (T(0) < val) - (val < T(0));
    }
}