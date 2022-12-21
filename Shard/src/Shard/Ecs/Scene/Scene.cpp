#include "shpch.h"
#include "TimeData.h"
#include "Scene.h"
#include "Ecs/Entity.h"
#include "Ecs/Components.h"
#include "Ecs/Systems/Physics2DSystem.h"
#include "Ecs/Systems/TextSystem.h"
#include "Ecs/Systems/SimpleSpriteAnimationSystem.h"
#include "Ecs/Systems/BasicShapesSystem.h"
#include "Ecs/Systems/SpriteSystem.h"
#include "Ecs/Systems/CameraSystem.h"
#include "Ecs/Systems/GizmosSystem.h"
#include "Ecs/Systems/TransformSystem.h"
#include "Ecs/Systems/LogicSystem.h"

namespace Shard
{
    std::map<entt::entity, Entity> Entity::m_entities;
    
    Scene::Scene(Window* window)
        : m_window(window)
    {
        window->OnRenderReady.ADD_LISTENER(Scene, OnRenderReady);
        window->OnRenderFrame.ADD_LISTENER(Scene, OnRenderFrame);

        AddSystem<LogicSystem>();
        AddSystem<Physics2DSystem>();

        AddSystem<TransformSystem>();
        AddSystem<CameraSystem>();

        //Rendering
        AddSystem<SpriteSystem>();
        AddSystem<BasicShapesSystem>();
        AddSystem<SimpleSpriteAnimationSystem>();
        AddSystem<TextSystem>();
        AddSystem<GizmosSystem>();
    }

    Scene::~Scene()
    {
        for (System* system : m_systems)
        {
            system->OnSceneFinish();
            delete system;
            system = nullptr;
        }

        m_systems.clear();
    }
    
    Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
    {
        const Entity entity{this, m_registry.create()};
        Entity::m_entities[entity.GetHandler()] = entity;
        entity.Add<Tag>(name, tag);
        entity.Add<Transform>();
        OnEntityCreated.Invoke({entity.GetHandler()});
        return entity;
    }

    void Scene::DestroyEntity(const Entity& entity)
    {
        if (!entity.IsValid()) return;
        const entt::entity entityId = entity.GetHandler();
        OnEntityDestroyed.Invoke({entity.GetHandler()});
        Entity::m_entities.erase(entityId);
        m_registry.destroy(entityId);
    }

    Entity Scene::GetEntityByHandler(const entt::entity handler)
    {
        if (!m_registry.valid(handler)) return {};
        return Entity::m_entities[handler];
    }

    Entity Scene::GetMainCameraEntity()
    {
        return GetEntityByHandler(CameraSystem::MainCameraEntityHandler());
    }
    
    void Scene::OnRenderReady(RenderReadyArgs args)
    {
        const Entity mainCamera = CreateEntity("Main Camera");
        mainCamera.Add<Camera>();
        for (System* system : m_systems) system->OnSceneStart();
    }

    void Scene::OnRenderFrame(RenderFrameArgs args)
    {
        for (System* system : m_systems) system->OnSceneUpdate();
        Time::CheckFixedUpdate([&] { OnFixedUpdate(); });
    }

    void Scene::OnFixedUpdate()
    {
        OnFixedUpdateCalled();
        for (System* system : m_systems) system->OnSceneFixedUpdate();
    }
}