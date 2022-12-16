#pragma once

#define DELTA_TIME Time::DeltaTime();
#define FIXED_DELTA_TIME Time::FixedDeltaTime();

namespace Shard
{
    namespace Rendering
    {
        class Window;
    }

    namespace Ecs
    {
        class Scene;
    }

    class Time
    {
    public:
        static float maxDeltaTime;
        static float fixedDeltaTime;
        static float timeScale;

        static float DeltaTime();
        static float FixedDeltaTime();

    private:
        static float m_deltaTime;
        static float m_lastTime;
        static float m_elapsed;
        
        static void CalculateDeltaTime(float currentTime);
        static void CheckFixedUpdate(std::function<void()> fixedUpdate = []{});

        friend class Rendering::Window;
        friend class Ecs::Scene;
    };
}
