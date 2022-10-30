#pragma once
#include "Core.h"

#define DELTA_TIME Time::DeltaTime();

namespace Shard
{
    namespace Rendering
    {
        class Window;
    }

    class SHARD_API Time
    {
    public:
        static float DeltaTime();

    private:
        static float s_DeltaTime;
        static float s_LastTime;

        static void CalculateDeltaTime(float _currentTime);
        friend class Rendering::Window;
    };
}
