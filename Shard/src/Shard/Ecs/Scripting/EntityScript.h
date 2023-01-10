#pragma once
#include "Script.h"
#include "Ecs/Entity.h"

namespace Shard
{
    class EntityScript : public Script
    {
        SHARD_OBJECT(EntityScript, Script)
    public:
        EntityScript() = default;
        
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
        
    private:
        Entity m_entity;

        friend struct Logic;
        friend class LogicSystem;
    };
}