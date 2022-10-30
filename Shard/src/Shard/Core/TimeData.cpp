#include "TimeData.h"

namespace Shard
{
    float Time::s_DeltaTime = 0;
    float Time::s_LastTime = 0;

    float Time::DeltaTime() { return s_DeltaTime; }

    void Time::CalculateDeltaTime(float _currentTime)
    {
        float currentTime = _currentTime;
        s_DeltaTime = currentTime - s_LastTime;
        s_LastTime = currentTime;
    }
}