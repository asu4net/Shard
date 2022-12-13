#include "shpch.h"
#include "System.h"
#include "Scene.h"
#include "Entity.h"

namespace Shard::Ecs
{
    System::System(Scene* scene)
    {
        if (!m_scene) assert(false);

        scene->OnEntityCreated.ADD_LISTENER(System, OnEntityCreated);
        scene->OnEntityDestroyed.ADD_LISTENER(System, OnEntityDestroyed);
        scene->OnComponentAdded.ADD_LISTENER(System, OnComponentAdded);
        scene->OnComponentRemoved.ADD_LISTENER(System, OnComponentRemoved);
    }

    entt::registry& System::Registry()
    {
        if (!m_scene) assert(false);
        return m_scene->m_registry;
    }

    Entity System::Camera()
    {
        if (!m_scene) assert(false);
        return m_scene->GetMainCameraEntity();
    }

    void System::OnEntityCreated(EntityArgs args)
    {
    }
    void System::OnEntityDestroyed(EntityArgs args)
    {
    }
    void System::OnComponentAdded(EntityArgs args)
    {
    }
    void System::OnComponentRemoved(EntityArgs args)
    {
    }
}