#include "shpch.h"
#include "Physics2DSystem.h"
#include "Scene.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "Components.h"

using namespace Shard::Math;

namespace Shard::Ecs
{
    Vector2 Physics2DSystem::m_gravity = { 0, -9.8f };
    b2World* Physics2DSystem::m_currentPhysicWorld = nullptr;
    float Physics2DSystem::m_timeStep = 1.0f / 120.0f;
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

    void Physics2DSystem::OnSceneStart()
    {
        m_currentPhysicWorld = m_physicWorld;
        m_physicWorld = new b2World(m_gravity.ToBox2D());
    }

    void Physics2DSystem::OnSceneUpdate()
    {
        m_physicWorld->Step(m_timeStep, m_velocityIterations, m_positionIterations);

        auto view = Registry().view<Transform, Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [transform, physicBody] = view.get<Transform, Physicbody2D>(entity);
            transform.position = { physicBody.m_body->GetTransform().p, transform.position.z };
            TransformSystem::Rotate(transform, physicBody.m_body->GetAngle(), Vector3::forward);
        }
    }

    void Physics2DSystem::OnComponentAdded(EntityArgs args)
    {
        Entity entity = GetEntityByHandler(args.entityHandler);
        if (!entity.Has<Physicbody2D>()) return;

        auto& pb = entity.Get<Physicbody2D>();
        TRANSFORM_REF(entity);

        b2BodyDef bodyDef;
        bodyDef.type = static_cast<b2BodyType>(pb.bodyType);
        bodyDef.position = entityTr.position.ToBox2D();
        pb.m_body = m_physicWorld->CreateBody(&bodyDef);

        //TODO: move to box collider
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(entityTr.scale.x * 1.0f, entityTr.scale.y * 1.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.3f;

        pb.m_body->CreateFixture(&fixtureDef);
    }
}