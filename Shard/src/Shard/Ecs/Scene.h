#pragma once
#include "CameraSystem.h"
#include "entt.hpp"
#include "TransformSystem.h"
#include "BasicShapesSystem.h"
#include "SimpleSpriteAnimationSystem.h"
#include "SpriteSystem.h"
#include "TextSystem.h"
#include "Rendering/Window.h"
#include "Ecs/Physics2DSystem.h"

namespace Shard::Ecs
{
    class Entity;
    class System;

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
        ~Scene();

        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        Entity GetEntityByHandler(const entt::entity handler);
        Entity GetMainCameraEntity();
        
    private:
        entt::registry m_registry;
        CameraSystem m_cameraSystem;
        TransformSystem m_transformSystem;
        BasicShapesSystem m_basicShapesSystem;
        SpriteSystem m_spriteSystem;
        TextSystem m_textSystem;
        SimpleSpriteAnimationSystem m_spriteAnimationSystem;
        Physics2DSystem m_physics2DSystem;

        std::vector<System*> m_systems;

        template<class T>
        void AddSystem()
        {
            T* system = new T();
            system->Initialize(this);
            m_systems.push_back(system);
        }
        
        void OnRenderReady(Rendering::RenderReadyArgs args);
        void OnRenderFrame(Rendering::RenderFrameArgs args);
        void OnComponentAddedListener(EntityArgs args);
        
        friend class Entity;
        friend class System;
    };
}
