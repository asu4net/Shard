#include "shpch.h"
#include "Physics2DSystem.h"
#include "Scene.h"
#include "box2d/b2_body.h"
#include "box2d/b2_fixture.h"
#include "Components.h"
#include "TransformSystem.h"
#include "TimeData.h"
#include "Rendering/Renderer.h"
#include "PhysicMaterial.h"

using namespace Shard::Math;
using namespace Shard::Rendering;

//TODO: Handle destruction. Check collisions and save references in components. Change colors if collides. Add runtime body functions.

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

    void Physics2DSystem::OnSceneStart()
    {
        m_physicWorld = new b2World(m_gravity.ToBox2D());
        m_currentPhysicWorld = m_physicWorld;
    }

    void Physics2DSystem::OnSceneUpdate()
    {
        auto boxView = Registry().view<Transform, BoxCollider2D>();

        for (entt::entity entity : boxView)
        {
            auto& [transform, boxCollider2D] = boxView.get<Transform, BoxCollider2D>(entity);
            DrawBox2DGizmos(Color::LightGreen, transform, boxCollider2D);
        }

        auto circleView = Registry().view<Transform, CircleCollider>();

        for (entt::entity entity : circleView)
        {
            auto& [transform, circleCollider] = circleView.get<Transform, CircleCollider>(entity);
            DrawCircleGizmos(Color::LightGreen, transform, circleCollider);
        }
    }

    void Physics2DSystem::OnSceneFixedUpdate()
    {
        m_physicWorld->Step(Time::FixedDeltaTime(), m_velocityIterations, m_positionIterations);
        UpdateBox2DBodies();
        UpdateCircleBodies();
        CheckCollisions();
    }

    void Physics2DSystem::OnEntityDestroyed(EntityArgs args)
    {
        FinalizePhysicComponents(GetEntityByHandler(args.entityHandler));
    }

    void Physics2DSystem::OnComponentRemoved(EntityArgs args)
    {
        FinalizePhysicComponents(GetEntityByHandler(args.entityHandler));
    }

    void Physics2DSystem::FinalizePhysicComponents(Entity entity)
    {
        if (!entity.Has<Physicbody2D>()) return;

        
    }

    void Physics2DSystem::UpdateBox2DBodies()
    {
        auto view = Registry().view<BoxCollider2D, Transform, Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [collider, transform, physicBody] = view.get<BoxCollider2D, Transform, Physicbody2D>(entity);
            if (collider.size != collider.m_prevSize)
                CreateBoxFixture(physicBody, collider);
            transform.position = { physicBody.m_body->GetTransform().p - collider.center.ToBox2D(), transform.position.z };
            transform.rotation = glm::angleAxis(physicBody.m_body->GetAngle(), glm::vec3(0, 0, 1));
            UpdatePhysicBody(physicBody);
        }
    }

    void Physics2DSystem::UpdateCircleBodies()
    {
        auto view = Registry().view<CircleCollider, Transform, Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [collider, transform, physicBody] = view.get<CircleCollider, Transform, Physicbody2D>(entity);
            if (collider.radius != collider.m_prevRadius)
                CreateCircleFixture(physicBody, collider);
            transform.position = { physicBody.m_body->GetTransform().p - collider.center.ToBox2D(), transform.position.z };
            transform.rotation = glm::angleAxis(physicBody.m_body->GetAngle(), glm::vec3(0, 0, 1));
            UpdatePhysicBody(physicBody);
        }
    }

    void Physics2DSystem::CheckCollisions()
    {
        auto view = Registry().view<Physicbody2D, Logic>();
        auto otherView = Registry().view<Physicbody2D>();

        for (entt::entity entity : view)
        {
            auto& [pb, logic] = view.get<Physicbody2D, Logic>(entity);
            b2Body* body = pb.m_body;
            b2Shape* shape = body->GetFixtureList()[0].GetShape();
            if (!shape) continue;

            for (entt::entity otherEntity : otherView)
            {
                if (entity == otherEntity) continue;

                auto& otherPb = otherView.get<Physicbody2D>(otherEntity);
                b2Body* otherBody = otherPb.m_body;
                b2Shape* otherShape = body->GetFixtureList()[0].GetShape();
                if (!otherShape) continue;

                bool isCollision = b2TestOverlap(shape, 0, otherShape, 0, body->GetTransform(), otherBody->GetTransform());
                
                if (!isCollision) continue;
                
                Entity other = GetEntityByHandler(otherEntity);
                
                for (Script* script : logic.m_scripts)
                    script->OnCollision(other);

                if (!other.Has<Logic>()) continue;

                auto& otherLogic = other.Get<Logic>();

                for (Script* otherScript : otherLogic.m_scripts)
                    otherScript->OnCollision(GetEntityByHandler(entity));
            }
        }
    }

    void Physics2DSystem::UpdatePhysicBody(Physicbody2D& physicBody)
    {
        b2Body& body = physicBody.RuntimeBody();
        body.SetGravityScale(physicBody.gravityScale);
        
        if (physicBody.bodyType != physicBody.m_prevBodyType)
        {
            body.SetType(static_cast<b2BodyType>(physicBody.bodyType));
            if (physicBody.bodyType == Physicbody2D::BodyType::Kinematic)
                body.SetLinearVelocity({ 0, 0 });
        }    
    }

    void Physics2DSystem::OnComponentAdded(EntityArgs args)
    {  
        Entity entity = GetEntityByHandler(args.entityHandler);
        
        if (!entity.Has<Physicbody2D>()) return;
        auto& pb = entity.Get<Physicbody2D>();
        
        if (pb.m_body) return;
        auto& transform = entity.Get<Transform>();

        if (entity.Has<BoxCollider2D>())
        {
            auto& boxCollider = entity.Get<BoxCollider2D>();
            if (boxCollider.m_fixture) return;
            boxCollider.m_prevSize = boxCollider.size;
            CreateBody(pb, transform.position + boxCollider.center, transform.rotation);
            CreateBoxFixture(pb, boxCollider);
        }

        else if (entity.Has<CircleCollider>())
        {
            auto& circleCollider = entity.Get<CircleCollider>();
            if (circleCollider.m_fixture) return;
            circleCollider.m_prevRadius = circleCollider.radius;
            CreateBody(pb, transform.position + circleCollider.center, transform.rotation);
            CreateCircleFixture(pb, circleCollider);
        }
    }

    void Physics2DSystem::CreateBody(Physicbody2D& pb2D, const Vector3& position, const glm::quat& rotation)
    {
        b2BodyDef bodyDef;
        pb2D.m_prevBodyType = pb2D.bodyType;
        bodyDef.type = static_cast<b2BodyType>(pb2D.bodyType);
        bodyDef.position = position.ToBox2D();
        bodyDef.angle = glm::eulerAngles(rotation).z;
        pb2D.m_body = m_physicWorld->CreateBody(&bodyDef);
    }

    void Physics2DSystem::CreateBoxFixture(Physicbody2D& pb2D, BoxCollider2D& boxCollider2D)
    {
        b2Fixture* fixture = boxCollider2D.m_fixture;

        if (fixture)
            pb2D.RuntimeBody().DestroyFixture(fixture);

        b2PolygonShape boxShape;
        boxShape.SetAsBox(boxCollider2D.size.x / 2, boxCollider2D.size.y / 2);
        b2FixtureDef fixtureDef;
        SetFixtureDefinition(fixtureDef, boxShape, boxCollider2D.physicMaterial);
        fixture = pb2D.RuntimeBody().CreateFixture(&fixtureDef);
    }

    void Physics2DSystem::CreateCircleFixture(Physicbody2D& pb2D, CircleCollider& circleCollider)
    {
        b2Fixture* fixture = circleCollider.m_fixture;

        if (fixture)
            pb2D.RuntimeBody().DestroyFixture(fixture);

        b2CircleShape circleShape;
        circleShape.m_radius = circleCollider.radius;
        b2FixtureDef fixtureDef;
        SetFixtureDefinition(fixtureDef, circleShape, circleCollider.physicMaterial);
        fixture = pb2D.RuntimeBody().CreateFixture(&fixtureDef);
    }

    void Physics2DSystem::SetFixtureDefinition(b2FixtureDef& fixtureDef, const b2Shape& shape, const PhysicMaterial& pMaterial)
    {
        fixtureDef.shape = &shape;
        fixtureDef.density = pMaterial.density;
        fixtureDef.friction = pMaterial.friction;
        fixtureDef.restitution = pMaterial.bounciness;
        fixtureDef.restitutionThreshold = pMaterial.bouncinessThreshold;
    }

    void Physics2DSystem::DrawCircleGizmos(const Color& color, Transform& transform, CircleCollider& circleCollider)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);

        float size = circleCollider.radius * 2;
        gizmosTransform = glm::translate(gizmosTransform, (transform.m_worldPosition + circleCollider.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.m_worldRotation);
        gizmosTransform = glm::scale(gizmosTransform, { size, size, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawCircle(mvp, color, .05f, 0.005f);
    }

    void Physics2DSystem::DrawBox2DGizmos(const Color& color, Transform& transform, BoxCollider2D& boxCollider2D)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);
        gizmosTransform = glm::translate(gizmosTransform, (transform.m_worldPosition + boxCollider2D.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.m_worldRotation);
        gizmosTransform = glm::scale(gizmosTransform, { boxCollider2D.size.x, boxCollider2D.size.y, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawLines(Renderer::GetDefaultLineBox2D(), mvp, color);
    }
}