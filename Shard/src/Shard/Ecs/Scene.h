#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class Entity;
    
    class Scene
    {
    public:
        Entity CreateEntity(const std::string& name = "");
        void DestroyEntity(const Entity& entity);
        
    private:
        entt::registry m_registry;

        friend class Entity;
    };
}
