#pragma once
#include "Ecs/Entity.h"

namespace Shard
{
    class Script : public Object
    {
        SHARD_OBJECT(Script, Object)
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
            return m_entity.Has<T>();
        }

        template<typename T, typename... Args>
        T& Add(Args&&... args) const
        {
            return m_entity.Add<T>(std::forward<Args>(args)...);
        }

        template<typename T>
        T& Get() const
        {
            return m_entity.Get<T>();
        }

        template<typename T>
        void Remove() const
        {
            m_entity.Remove<T>();
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
