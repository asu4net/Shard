#include "shpch.h"
#include "TimeData.h"

namespace Shard
{
    float Time::maxDeltaTime = 0.016f;
    float Time::fixedDeltaTime = 0.02f;
    float Time::timeScale = 1.f;

    float Time::m_deltaTime = 0;
    float Time::m_lastTime = 0;

    float Time::m_elapsed = 0;

    std::function<void()> Time::fixedUpdateFunction;

    float Time::DeltaTime() { return m_deltaTime; }
    float Time::FixedDeltaTime() { return fixedDeltaTime; }

    void Time::CalculateDeltaTime(const float currentTime)
    {
        m_deltaTime = (currentTime - m_lastTime) * timeScale;
        if (m_deltaTime > maxDeltaTime) m_deltaTime = maxDeltaTime;
        m_lastTime = currentTime;
    }

    void Time::CheckFixedUpdate()
    {
        m_elapsed += m_deltaTime;
        
        while (m_elapsed >= fixedDeltaTime)
        {
            fixedUpdateFunction();
            m_elapsed -= fixedDeltaTime;
        }
    }
}