#include "shpch.h"
#include "System.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"

namespace Shard::Ecs
{
    void System::Initialize(Scene* scene)
    {
        m_scene = scene;
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

    Entity System::GetCameraEntity()
    {
        if (!m_scene) assert(false);
        return m_scene->GetMainCameraEntity();
    }

    Camera& System::GetCamera()
    {
        return GetCameraEntity().Get<Camera>();
    }

    Entity System::GetEntityByHandler(entt::entity entityHandler)
    {
        if (!m_scene) assert(false);
        return m_scene->GetEntityByHandler(entityHandler);
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