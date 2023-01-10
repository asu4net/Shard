#pragma once

#define DELTA_TIME Time::DeltaTime();
#define FIXED_DELTA_TIME Time::FixedDeltaTime();

namespace Shard
{
    class Window;
    class Scene;

    class Time
    {
    public:
        static float maxDeltaTime;
        static float fixedDeltaTime;
        static float timeScale;
        
        static void SubscribeToFixedUpdate(const std::function<void()>& function) { fixedUpdateFunction = function; }

        static float DeltaTime();
        static float FixedDeltaTime();

    private:
        static float m_deltaTime;
        static float m_lastTime;
        static float m_elapsed;

        static std::function<void()> fixedUpdateFunction;
        
        static void CalculateDeltaTime(const float currentTime);
        static void CheckFixedUpdate();

        friend class Window;
        friend class Scene;
    };
}
