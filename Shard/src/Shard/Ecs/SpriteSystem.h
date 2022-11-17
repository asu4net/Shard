#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class SpriteSystem
    {
    public:
        SpriteSystem() = default;
        
    private:
        void DrawSprites(entt::registry& registry);

        friend class Scene;
    };
}
