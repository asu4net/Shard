#pragma once
#include "entt.hpp"

namespace Shard
{
    class Scene;
    class Entity;
    struct ComponentArgs;
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
        Scene* GetScene() const { return m_scene; }

        virtual void OnSceneStart() {}
        virtual void OnSceneUpdate() {}
        virtual void OnSceneFixedUpdate() {}
        virtual void OnSceneFinish() {}

        virtual void OnEntityCreated(EntityArgs args);
        virtual void OnEntityDestroyed(EntityArgs args);
        virtual void OnComponentAdded(ComponentArgs args);
        virtual void OnComponentRemoved(ComponentArgs args);

        friend class Scene;
    };
}