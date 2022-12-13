#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class Scene;
    class Entity;
    struct EntityArgs;

    class System
    {
    public:
        System(Scene* scene);

    private:
        Scene* m_scene = nullptr;

    protected:
        entt::registry& Registry();
        Entity Camera();

        virtual void OnEngineStart() {};
        virtual void OnEngineUpdate() {};
        virtual void OnRuntimeStart() {};
        virtual void OnRuntimeUpate() {};

        virtual void OnEntityCreated(EntityArgs args);
        virtual void OnEntityDestroyed(EntityArgs args);
        virtual void OnComponentAdded(EntityArgs args);
        virtual void OnComponentRemoved(EntityArgs args);

        friend class Scene;
    };
}