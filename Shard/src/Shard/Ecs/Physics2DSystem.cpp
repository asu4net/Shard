#include "shpch.h"
#include "Physics2DSystem.h"
#include "Scene.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "Components.h"
#include "TransformSystem.h"
#include "TimeData.h"

using namespace Shard::Math;

namespace Shard::Ecs
{
    Vector2 Physics2DSystem::m_gravity = { 0, -9.8f };
    b2World* Physics2DSystem::m_currentPhysicWorld = nullptr;
    float Physics2DSystem::m_timeStep = 1.0f / 60.0f;
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
        m_physicWorld = new b2World(m_gravity.ToBox2D());
        m_currentPhysicWorld = m_physicWorld;
    }

    void Physics2DSystem::OnSceneFixedUpdate()
    {
        m_physicWorld->Step(Time::FixedDeltaTime(), m_velocityIterations, m_positionIterations);

        auto view = Registry().view<BoxCollider2D, Transform, Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [c, transform, physicBody] = view.get<BoxCollider2D, Transform, Physicbody2D>(entity);
            transform.position = { physicBody.m_body->GetTransform().p - c.center.ToBox2D(), transform.position.z};
            float rotationDegrees = glm::degrees(physicBody.m_body->GetAngle());
            transform.rotation = glm::angleAxis(physicBody.m_body->GetAngle(), glm::vec3(0, 0, 1));
        }
    }

    void Physics2DSystem::OnComponentAdded(EntityArgs args)
    {
        Entity entity = GetEntityByHandler(args.entityHandler);
        if (!entity.Has<Physicbody2D>()) return;

        auto& pb = entity.Get<Physicbody2D>();
        auto& c = entity.Get<BoxCollider2D>();

        TRANSFORM_REF(entity);

        b2BodyDef bodyDef;
        bodyDef.type = static_cast<b2BodyType>(pb.bodyType);
        bodyDef.position = (entityTr.position + c.center).ToBox2D();
        bodyDef.angle = glm::eulerAngles(entityTr.rotation).z;
        pb.m_body = m_physicWorld->CreateBody(&bodyDef);

        //TODO: move to box collider
        b2PolygonShape dynamicBox;
        dynamicBox.SetAsBox(c.size.x/2, c.size.y/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &dynamicBox;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.1f;
        fixtureDef.restitution = 0.1f;

        pb.m_body->CreateFixture(&fixtureDef);
    }
}