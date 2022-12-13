#include "shpch.h"
#include "Scene.h"
#include "Entity.h"
#include "Ecs/Components.h"
#include "Ecs/System.h"
#include "CollisionSystem.h"

namespace Shard::Ecs
{
    std::map<entt::entity, Entity> Entity::m_entities;
    
    Scene::Scene(Rendering::Window& window)
    {
        window.OnRenderReady.ADD_LISTENER(Scene, OnRenderReady);
        window.OnRenderFrame.ADD_LISTENER(Scene, OnRenderFrame);
        OnComponentAdded.ADD_LISTENER(Scene, OnComponentAddedListener);

        AddSystem<CollisionSystem>();
    }

    Scene::~Scene()
    {
        for (System* system : m_systems)
        {
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

        for (System* system : m_systems) system->OnEngineStart();
    }

    void Scene::OnRenderFrame(Rendering::RenderFrameArgs args)
    {
        m_transformSystem.CalculateTransforms(m_registry);
        m_cameraSystem.CalculateCameraMatrices(m_registry, args.window->Aspect());
        m_spriteSystem.DrawSprites(m_registry);
        m_basicShapesSystem.DrawBasicShapes(m_registry);
        m_textSystem.RenderTexts(m_registry);
        m_spriteAnimationSystem.HandleSpriteAnimations(m_registry);
        m_physics2DSystem.HandlePhysics(m_registry);

        for (System* system : m_systems) system->OnEngineUpdate();
    }

    void Scene::OnComponentAddedListener(EntityArgs args)
    {
        Entity entity = GetEntityByHandler(args.entityHandler);

        if (entity.Has<TextRenderer>())
        {
            TextRenderer& textRenderer = entity.Get<TextRenderer>();
            TextSystem::SetText(textRenderer, textRenderer.Text());
        }

        if (entity.Has<Physicbody2D>())
        {
            m_physics2DSystem.Physicbody2DAdded(entity);
        }
    }
}
