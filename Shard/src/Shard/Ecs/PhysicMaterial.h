#pragma once

namespace Shard::Ecs
{
    struct PhysicMaterial
    {
        float density = 1.0f;
        float friction = 0.5f;
        float bounciness = 0.0f;
        float bouncinessThreshold = 0.5f; //velocity to stop calculating bouncing 
    };
}
