#pragma once
#include "CameraSystem.h"
#include "entt.hpp"
#include "TransformSystem.h"
#include "BasicShapesSystem.h"
#include "Rendering/Window.h"

namespace Shard::Ecs
{
    class Entity;

    struct EntityArgs { entt::entity entityHandler; };
    
    class Scene
    {
    public:
        Event<EntityArgs> OnEntityCreated;
        Event<EntityArgs> OnEntityDestroyed;
        Event<EntityArgs> OnComponentAdded;
        Event<EntityArgs> OnComponentRemoved;
        
        Scene() = default;
        Scene(Rendering::Window& window);
        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        Entity GetEntityByHandler(const entt::entity handler);
        Entity GetMainCameraEntity();
        
    private:
        entt::registry m_registry;
        CameraSystem m_cameraSystem;
        TransformSystem m_transformSystem;
        BasicShapesSystem m_basicShapesSystem;
        
        void OnRenderReady(Rendering::RenderReadyArgs args);
        void OnRenderFrame(Rendering::RenderFrameArgs args);
        
        friend class Entity;
    };
}
