#pragma once

namespace Shard::Math
{
    struct UvCoords
    {
        float xPos{0}, yPos{0};
        float s0{0}, s1{0}, t0{0}, t1{0}, x0{0}, x1{0}, y0{0}, y1{0};
    };
    
    struct MvpData
    {
        glm::mat4 model{1}, view{1}, projection{1};
    };
}
