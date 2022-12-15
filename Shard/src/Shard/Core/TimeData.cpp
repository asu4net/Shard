#include "shpch.h"
#include "TimeData.h"

namespace Shard
{
    float Time::maxDeltaTime = 0.016f;
    float Time::maxFixedDeltaTime = 0.02f;
    float Time::timeScale = 1.f;

    float Time::m_deltaTime = 0;
    float Time::m_lastTime = 0;

    float Time::m_currentFixedDeltaTime = 0;
    float Time::m_fixedDeltaTime = 0;

    float Time::DeltaTime() { return m_deltaTime; }
    float Time::FixedDeltaTime() { return m_fixedDeltaTime; }

    void Time::CalculateDeltaTime(float currentTime)
    {
        m_deltaTime = (currentTime - m_lastTime) * timeScale;
        if (m_deltaTime > maxDeltaTime) m_deltaTime = maxDeltaTime;
        m_lastTime = currentTime;
    }

    void Time::CalculateFixedDeltaTime(std::function<void()> fixedUpdate)
    {
        m_currentFixedDeltaTime += m_deltaTime;
        
        if (m_currentFixedDeltaTime < maxFixedDeltaTime) return;

        m_fixedDeltaTime = m_currentFixedDeltaTime;
        int bufferedFixedUpdates = static_cast<int>(m_currentFixedDeltaTime / maxFixedDeltaTime);
        
        for (int i = 0; i < bufferedFixedUpdates; i++) 
            fixedUpdate();
        
        m_currentFixedDeltaTime = 0;
    }
}