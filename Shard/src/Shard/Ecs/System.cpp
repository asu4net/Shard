#include "shpch.h"
#include "System.h"
#include "Scene/Scene.h"
#include "Entity.h"
#include "Components.h"
#include "Systems/CameraSystem.h"

namespace Shard
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

    Camera& System::GetCamera()
    {
        return CameraSystem::GetMainCameraEntity().Get<Camera>();
    }
    
    float System::GetWindowAspect() const
    {
        return m_scene->m_window->Aspect();
    }

    void System::OnEntityCreated(EntityArgs args)
    {
    }
    void System::OnEntityDestroyed(EntityArgs args)
    {
    }
    void System::OnComponentAdded(ComponentArgs args)
    {
    }
    void System::OnComponentRemoved(ComponentArgs args)
    {
    }
}
