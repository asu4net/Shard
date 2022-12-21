#pragma once
#include "Scene.h"
#include "entt.hpp"

#define TRANSFORM_REF(_ENTITY) auto& _ENTITY##Tr = _ENTITY.Get<Transform>()
#define ENTITY_ACCESS_ERROR(_FUNC) std::cout << "Error!: " << #_FUNC << "<" << T::GetType()->GetName().c_str() << ">() called on invalid entity id: " << static_cast<int>(m_entityHandler) << std::endl;

namespace Shard
{
    struct Transform;

    class Entity
    {
    public:
        Entity() = default;
        Entity(Scene* scene, const entt::entity entityHandler)
            : m_scene(scene)
            , m_entityHandler(entityHandler)
        {}
        Entity(const Entity& other) = default;
        
        entt::entity GetHandler() const { return m_entityHandler; }
        
        bool operator==(const Entity& other)
        {
            return m_entityHandler == other.m_entityHandler;
        }

        bool IsValid() const
        {
            if (!m_scene) return false;
            return m_scene->m_registry.valid(m_entityHandler);
        }
        
        template<typename T>
        bool Has() const
        {
            if (!IsValid())
            {
                ENTITY_ACCESS_ERROR(Has)
                assert(false);
            }
            return m_scene->m_registry.try_get<T>(m_entityHandler);
        }

        template<typename T, typename... Args>
        T& Add(Args&&... args) const
        {
            if (!IsValid())
            {
                ENTITY_ACCESS_ERROR(Add)
                assert(false);
            }
            T& component = m_scene->m_registry.emplace<T>(m_entityHandler, std::forward<Args>(args)...);
            m_scene->OnComponentAdded.Invoke({m_entityHandler, T::GetType()});
            return component;
        }
        
        template<typename T>
        T& Get() const
        {
            if (!IsValid())
            {
                ENTITY_ACCESS_ERROR(Get)
                assert(false);
            }
            return m_scene->m_registry.get<T>(m_entityHandler);
        }
        
        template<typename T>
        void Remove() const
        {
            if (!IsValid())
            {
                ENTITY_ACCESS_ERROR(Remove)
                assert(false);
            }
            m_scene->OnComponentRemoved.Invoke({m_entityHandler, T::GetType()});
            m_scene->m_registry.erase<T>(m_entityHandler);
        }

    private:
        Scene* m_scene = nullptr;
        entt::entity m_entityHandler{0};
        static std::map<entt::entity, Entity> m_entities;
        
        friend class Scene;
    };
}
