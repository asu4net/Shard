#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class Scene;
    class BasicShapesSystem
    {
    public:
        BasicShapesSystem() = default;
        
    private:
        void DrawBasicShapes(entt::registry& registry);
        friend class Scene;
    };
}
