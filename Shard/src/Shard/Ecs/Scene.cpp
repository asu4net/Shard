#include "shpch.h"
#include "Scene.h"
#include "Entity.h"

namespace Shard::Ecs
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        const Entity entity = m_registry.create();
        //add tag component
        return entity;
    }

    void Scene::DestroyEntity(const Entity& entity)
    {
        if (entity.IsValid())
            m_registry.destroy(entity.GetHandler());
    }
}
