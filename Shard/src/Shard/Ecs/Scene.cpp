#include "shpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Ecs/Components.h"

namespace Shard::Ecs
{
    std::map<entt::entity, Entity> Entity::m_entities;
    
    Scene::Scene(Rendering::Window& window)
    {
        window.OnRenderReady.ADD_LISTENER(Scene, OnRenderReady);
        window.OnRenderFrame.ADD_LISTENER(Scene, OnRenderFrame);

        m_cameraSystem = std::make_shared<CameraSystem>();
        m_transformSystem = std::make_shared<TransformSystem>();
        m_basicShapesSystem = std::make_shared<BasicShapesSystem>();
    }

    Entity Scene::CreateEntity(const std::string& name, const std::string& tag)
    {
        const Entity entity{this, m_registry.create()};
        Entity::m_entities[entity.GetHandler()] = entity;
        entity.Add<String>(name, tag);
        entity.Add<Transform>();
        return entity;
    }

    void Scene::DestroyEntity(const Entity& entity)
    {
        if (entity.IsValid())
        {
            const entt::entity entityId = entity.GetHandler();
            Entity::m_entities.erase(entityId);
            m_registry.destroy(entityId);
        }
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
    }

    void Scene::OnRenderFrame(Rendering::RenderFrameArgs args)
    {
        m_transformSystem->CalculateTransforms(m_registry);
        m_cameraSystem->CalculateCameraMatrices(m_registry, args.window->Aspect());
        m_basicShapesSystem->DrawBasicShapes(m_registry);
    }
}