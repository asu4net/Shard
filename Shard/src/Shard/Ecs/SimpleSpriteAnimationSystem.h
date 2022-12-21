#pragma once
#include "System.h"

namespace Shard
{
    class SimpleSpriteAnimationSystem : public System
    {
    public:
        void OnSceneUpdate() override;
    };
}
