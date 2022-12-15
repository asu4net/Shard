﻿#include "shpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Components.h"
#include "System.h"
#include "Physics2DSystem.h"
#include "CollisionSystem.h"
#include "TextSystem.h"
#include "SimpleSpriteAnimationSystem.h"
#include "BasicShapesSystem.h"
#include "SpriteSystem.h"
#include "CameraSystem.h"
#include "TransformSystem.h"
#include "TimeData.h"

namespace Shard::Ecs
{
    std::map<entt::entity, Entity> Entity::m_entities;
    
    Scene::Scene(Rendering::Window* window)
        : m_window(window)
    {
        window->OnRenderReady.ADD_LISTENER(Scene, OnRenderReady);
        window->OnRenderFrame.ADD_LISTENER(Scene, OnRenderFrame);

        AddSystem<TransformSystem>();
        AddSystem<CameraSystem>();
        AddSystem<SpriteSystem>();
        AddSystem<BasicShapesSystem>();
        AddSystem<SimpleSpriteAnimationSystem>();
        AddSystem<CollisionSystem>();
        AddSystem<Physics2DSystem>();
        AddSystem<TextSystem>();
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
        entity.Add<String>(name, tag);
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
    
    void Scene::OnRenderReady(Rendering::RenderReadyArgs args)
    {
        const Entity mainCamera = CreateEntity("Main Camera");
        mainCamera.Add<Camera>();       

        for (System* system : m_systems) system->OnSceneStart();
    }

    void Scene::OnRenderFrame(Rendering::RenderFrameArgs args)
    {
        for (System* system : m_systems) system->OnSceneUpdate();
        Time::CalculateFixedDeltaTime([&] { OnFixedUpdate(); });
    }

    void Scene::OnFixedUpdate()
    {
        OnFixedUpdateCalled();
        for (System* system : m_systems) system->OnSceneFixedUpdate();
    }
}