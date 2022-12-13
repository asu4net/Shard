#pragma once
#include "System.h"

namespace Shard::Ecs
{
    class SimpleSpriteAnimationSystem : public System
    {
    public:
        void OnSceneUpdate() override;
    };
}
