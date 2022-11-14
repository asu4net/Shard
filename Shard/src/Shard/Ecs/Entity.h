#pragma once
#include "Scene.h"
#include "entt.hpp"

namespace Shard::Ecs
{
    class Entity
    {
    public:
        Entity() = default;
        Entity(const entt::entity entityHandler)
            : m_entityHandler(entityHandler)
        {}
        Entity(const Entity& other) = default;
        
        entt::entity GetHandler() const { return m_entityHandler; }
        
        bool operator==(const Entity& other)
        {
            return m_entityHandler == other.m_entityHandler;
        }

        bool IsValid() const
        {
            return m_scene->m_registry.valid(m_entityHandler);
        }
        
        template<typename T>
        bool Has() const
        {
            return m_scene->m_registry.try_get<T>(m_entityHandler);
        }

        template<typename T, typename... Args>
        T& Add(Args&&... args) const
        {
            T& component = m_scene->m_registry.emplace<T>(m_entityHandler, std::forward<Args>(args)...);
            return component;
        }

        template<typename T>
        T& Get() const
        {
            return m_scene->m_registry.get<T>(m_entityHandler);
        }
        
        template<typename T>
        void Remove() const
        {
            m_scene->m_registry.erase<T>(m_entityHandler);
        }

    private:
        Scene* m_scene = nullptr;
        entt::entity m_entityHandler{0};
    };
}
