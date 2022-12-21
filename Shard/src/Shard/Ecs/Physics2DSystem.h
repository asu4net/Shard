#pragma once
#include "box2d/b2_world.h"
#include "System.h"

struct b2FixtureDef;
class b2Shape;

namespace Shard::Ecs
{
    struct Physicbody2D;
    struct BoxCollider2D;
    struct Transform;
    struct CircleCollider;
    class Entity;
    struct PhysicMaterial;

    class Physics2DSystem : public System
    {
    public:
        ~Physics2DSystem() { m_currentPhysicWorld = nullptr; }

        static const Math::Vector2 GetGravity() { return m_gravity; }
        static void SetGravity(const Math::Vector2& gravity);

    private:
        static Math::Vector2 m_gravity;
        static b2World* m_currentPhysicWorld;
        static int32 m_velocityIterations;
        static int32 m_positionIterations;

        void CreateBody(Physicbody2D& pb2D, const Math::Vector3& position, const glm::quat& rotation);
        
        static void CreateBoxFixture(Physicbody2D& pb2D, BoxCollider2D& boxCollider2D);
        static void CreateCircleFixture(Physicbody2D& pb2D, CircleCollider& circleCollider);
        static void SetFixtureDefinition(b2FixtureDef& fixtureDef, const b2Shape& shape, const PhysicMaterial& pMaterial);

        void UpdateBox2DBodies();
        void UpdateCircleBodies();
        void CheckCollisions();
        void UpdatePhysicBody(Physicbody2D& physicBody);
        void FinalizePhysicbody2DComponent(Entity entity);

        b2World* m_physicWorld = nullptr;
        
        void OnSceneStart() override;
        void OnSceneFixedUpdate() override;
        void OnEntityDestroyed(EntityArgs args) override;
        void OnComponentRemoved(ComponentArgs args) override;
        void OnComponentAdded(ComponentArgs args) override;
    };
}

