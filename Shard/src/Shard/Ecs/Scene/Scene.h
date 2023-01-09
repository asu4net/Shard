#pragma once
#include "entt.hpp"
#include "Rendering/Window.h"

namespace Shard
{
    class System;
    class Entity;

    struct ComponentArgs { entt::entity entityHandler; const Type* componentType; };
    struct EntityArgs { entt::entity entityHandler; };
    
    class Scene
    {
    public:
        Event<EntityArgs> OnEntityCreated;
        Event<EntityArgs> OnEntityDestroyed;
        Event<ComponentArgs> OnComponentAdded;
        Event<ComponentArgs> OnComponentRemoved;
        std::function<void()> OnFixedUpdateCalled;
        
        Scene() = default;
        Scene(Window* window);
        ~Scene();

        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        static Entity GetEntityByHandler(const entt::entity handler);
        Window* GetWindow() { return m_window; }
        
    private:
        entt::registry m_registry;
        Window* m_window = nullptr;
        std::vector<System*> m_systems;

        template<class T>
        void AddSystem()
        {
            T* system = new T();
            system->Initialize(this);
            m_systems.push_back(system);
        }
        
        void OnRenderReady(RenderReadyArgs args);
        void OnRenderFrame(RenderFrameArgs args);
        void OnFixedUpdate();
        
        friend class Entity;
        friend class System;
    };
}
