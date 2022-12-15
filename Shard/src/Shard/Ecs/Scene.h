#pragma once
#include "entt.hpp"
#include "Rendering/Window.h"

namespace Shard::Rendering { class Window; }

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
        std::function<void()> OnFixedUpdateCalled;

        Scene() = default;
        Scene(Rendering::Window* window);
        ~Scene();

        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        Entity GetEntityByHandler(const entt::entity handler);
        Entity GetMainCameraEntity();
        
    private:
        entt::registry m_registry;
        Rendering::Window* m_window = nullptr;
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
        void OnFixedUpdate();
        
        friend class Entity;
        friend class System;
    };
}
