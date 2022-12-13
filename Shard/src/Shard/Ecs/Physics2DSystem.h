#pragma once
#include "entt.hpp"
#include "box2d/b2_world.h"

namespace Shard::Ecs
{
    struct Physicbody2D;
    class Entity;

    class Physics2DSystem
    {
    public:
        Physics2DSystem();
        ~Physics2DSystem() { m_currentPhysicWorld = nullptr; }

        static const Math::Vector2 GetGravity() { return m_gravity; }
        static void SetGravity(const Math::Vector2& gravity);

    private:
        static Math::Vector2 m_gravity;
        static b2World* m_currentPhysicWorld;
        static float m_timeStep;
        static int32 m_velocityIterations;
        static int32 m_positionIterations;

        b2World m_physicWorld;
        
        void HandlePhysics(entt::registry& registry);
        void Physicbody2DAdded(Entity physicEntity);

        friend class Scene;
    };
}

