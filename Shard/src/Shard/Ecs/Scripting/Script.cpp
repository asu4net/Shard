#include "shpch.h"
#include "Script.h"

#include "Ecs/Entity.h"

namespace Shard
{
    Entity Script::CreateEntity(const std::string& name, const std::string& tag)
    {
        return m_scene->CreateEntity(name, tag);
    }

    void Script::DestroyEntity(Entity entity)
    {
        m_scene->DestroyEntity(entity);
    }
}
