#pragma once

namespace Shard::Math
{
    struct CharUv
    {
        float xPos, yPos;
        float s0, s1, t0, t1, x0, x1, y0, y1;
    };
    
    struct MvpData
    {
        glm::mat4 model{1}, view{1}, projection{1};
    };
}
