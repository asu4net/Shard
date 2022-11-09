#pragma once

#define DELTA_TIME Time::DeltaTime();

namespace Shard
{
    namespace Rendering
    {
        class Window;
    }

    class Time
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
