#pragma once
#include "Ecs/Entity.h"

namespace Shard
{
    class Script
    {
    public:
        Script() = default;

        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}
        virtual void OnCollision(Entity other) {}

        template<typename T>
        bool Has() const
        {
            return entity.Has<T>();
        }

        template<typename T, typename... Args>
        T& Add(Args&&... args) const
        {
            return entity.Add<T>(args);
        }

        template<typename T>
        T& Get() const
        {
            return entity.Get<T>();
        }

        template<typename T>
        void Remove() const
        {
            entity.Remove<T>();
        }

        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default")
        {
            return m_scene->CreateEntity();
        }

        void DestroyEntity(Entity entity) { m_scene->DestroyEntity(entity); }

        Entity GetOwner() const 
        {
            return m_entity;
        }
        
    private:
        Entity m_entity;
        Scene* m_scene;

        friend struct Logic;
        friend class LogicSystem;
    };
}
