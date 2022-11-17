#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class SimpleSpriteAnimationSystem
    {
    public:
        SimpleSpriteAnimationSystem() = default;
        void HandleSpriteAnimations(entt::registry& registry);
    };
}
