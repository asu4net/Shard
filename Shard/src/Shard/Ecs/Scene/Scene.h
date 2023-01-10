#pragma once
#include "entt.hpp"
#include "Rendering/Window.h"

namespace Shard
{
    class System;
    class Entity;
    class SceneScript;

    struct ComponentArgs { entt::entity entityHandler; const Type* componentType; };
    struct EntityArgs { entt::entity entityHandler; };
    
    class Scene
    {
    public:
        Event<EntityArgs> OnEntityCreated;
        Event<EntityArgs> OnEntityDestroyed;
        Event<ComponentArgs> OnComponentAdded;
        Event<ComponentArgs> OnComponentRemoved;
        
        Scene() = default;
        Scene(Window* window);
        ~Scene();

        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(const Entity& entity);
        static Entity GetEntityByHandler(const entt::entity handler);
        Window* GetWindow() { return m_window; }

        template<class T>
        T& AddScript()
        {
            if (m_sceneScript)
            {
                assert(false);
                return T();
            }
            T* script = new T();
            script->m_scene = this;
            script->Awake();
            m_sceneScript = script;
            return *script;
        }
        
    private:
        entt::registry m_registry;
        Window* m_window = nullptr;
        std::vector<System*> m_systems;
        SceneScript* m_sceneScript = nullptr;
        bool m_firstFrame = true;
        
        template<class T>
        void AddSystem()
        {
            T* system = new T();
            system->Initialize(this);
            m_systems.push_back(system);
        }
        
        void OnRenderReady(RenderReadyArgs args);
        void OnRenderFrame(RenderFrameArgs args);
        
        void FixedUpdateSceneScript();
        void UpdateSceneScript();
        
        friend class Entity;
        friend class System;
    };
}