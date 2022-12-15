#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    class Scene;
    class Entity;
    struct EntityArgs;
    struct Camera;

    class System
    {
    public:
        System() = default;
        void Initialize(Scene* scene);

    private:
        Scene* m_scene = nullptr;

    protected:
        entt::registry& Registry();
        Entity GetCameraEntity();
        Camera& GetCamera();
        Entity GetEntityByHandler(entt::entity entityHandler);
        float GetWindowAspect() const;

        virtual void OnSceneStart() {};
        virtual void OnSceneUpdate() {};
        virtual void OnSceneFixedUpdate() {};
        virtual void OnSceneFinish() {};

        virtual void OnEntityCreated(EntityArgs args);
        virtual void OnEntityDestroyed(EntityArgs args);
        virtual void OnComponentAdded(EntityArgs args);
        virtual void OnComponentRemoved(EntityArgs args);

        friend class Scene;
    };
}