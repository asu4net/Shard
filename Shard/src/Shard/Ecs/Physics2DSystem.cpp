#include "shpch.h"
#include "Physics2DSystem.h"
#include "Scene.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "Components.h"
#include "TimeData.h"

using namespace Shard::Math;

namespace Shard::Ecs
{
    Vector2 Physics2DSystem::m_gravity = { 0, -9.8f };
    b2World* Physics2DSystem::m_currentPhysicWorld = nullptr;
    int32 Physics2DSystem::m_velocityIterations = 6;
    int32 Physics2DSystem::m_positionIterations = 2;

    void Physics2DSystem::SetGravity(const Vector2& gravity)
    {
        if (!m_currentPhysicWorld)
        {
            assert(false);
            return;
        }

        m_gravity = gravity;
        m_currentPhysicWorld->SetGravity(gravity.ToBox2D());
    }

    Physics2DSystem::Physics2DSystem()
        : m_physicWorld(m_gravity.ToBox2D())
    {
        m_currentPhysicWorld = &m_physicWorld;
    }

    void Physics2DSystem::HandlePhysics(entt::registry& registry)
    {
        m_physicWorld.Step(Time::DeltaTime(), m_velocityIterations, m_positionIterations);

        auto view = registry.view<Transform, Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [transform, physicBody] = view.get<Transform, Physicbody2D>(entity);
            transform.position = { physicBody.m_body->GetTransform().p, transform.position.z };
            TransformSystem::Rotate(transform, physicBody.m_body->GetAngle(), Vector3::forward);
        }

    }

    void Physics2DSystem::Physicbody2DAdded(Entity physicEntity)
    {
        auto& pb = physicEntity.Get<Physicbody2D>();
        TRANSFORM_REF(physicEntity);
        b2BodyDef bodyDef;
        bodyDef.type = static_cast<b2BodyType>(pb.bodyType);
        bodyDef.position = physicEntityTr.position.ToBox2D();
        pb.m_body = m_physicWorld.CreateBody(&bodyDef);

        //TODO: move to box collider
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(physicEntityTr.scale.x * 1.0f, physicEntityTr.scale.y * 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        pb.m_body->CreateFixture(&fixtureDef);
    }
}