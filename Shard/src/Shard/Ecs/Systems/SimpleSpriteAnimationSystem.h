#pragma once
#include "Ecs/System.h"

namespace Shard
{
    class SimpleSpriteAnimationSystem : public System
    {
    public:
        void OnSceneUpdate() override;
    };
}
