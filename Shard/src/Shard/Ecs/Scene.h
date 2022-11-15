#pragma once
#include "CameraSystem.h"
#include "entt.hpp"
#include "TransformSystem.h"
#include "BasicShapesSystem.h"
#include "Rendering/Window.h"

namespace Shard::Ecs
{
    class Entity;
    
    class Scene
    {
    public:
        Scene() = default;
        Scene(Rendering::Window& window);
        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        
    private:
        entt::registry m_registry;
        std::shared_ptr<CameraSystem> m_cameraSystem;
        std::shared_ptr<TransformSystem> m_transformSystem;
        std::shared_ptr<BasicShapesSystem> m_basicShapesSystem;
        
        void OnRenderReady(Rendering::RenderReadyArgs args);
        void OnRenderFrame(Rendering::RenderFrameArgs args);
        
        friend class Entity;
    };
}
