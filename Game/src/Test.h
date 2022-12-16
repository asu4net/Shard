#pragma once
#include "KeyCodes.h"

#ifdef TEST

class Game final : public Application
{
    Entity entityA;
    Entity entityB;
    float move = 10;
    float torque = 5;

    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Test - Alejandro :D");

        entityA = scene.CreateEntity("test");
        {
            entityA.Get<Transform>().position += Vector3::up * 2.f;
            entityA.Add<SpriteRenderer>().color = Color::LightRed;
            auto& collider = entityA.Add<BoxCollider2D>();
            entityA.Add<Physicbody2D>().RuntimeBody().SetGravityScale(0);

        }

        entityB = scene.CreateEntity();
        {
            entityB.Get<Transform>().position += Vector3::down * 2.f;

            auto& collider = entityB.Add<BoxCollider2D>();
            TransformSystem::Rotate(entityB.Get<Transform>(), 12, { 0, 0, 1 });
            collider.center = { 0, 1 };
            collider.size = { 6, 1 };

            auto& pb = entityB.Add<Physicbody2D>();

            pb.RuntimeBody().SetType((b2BodyType)Physicbody2D::BodyType::Kinematic);
        }

        Entity entityC = scene.CreateEntity("test");
        {
            entityC.Add<SpriteRenderer>().color = Color::LightBlue;
            entityC.Get<Transform>().position += Vector3::up;
            auto& collider = entityC.Add<BoxCollider2D>();
            entityC.Add<Physicbody2D>();
        }
    }

    void MoveEntityByInput(Entity entity)
    {
        auto& pb = entity.Get<Physicbody2D>();
        Vector3 position = entity.Get<Transform>().position;

        if (Input::GetKeyPressed(KEY_D))
        {
            pb.RuntimeBody().ApplyForce({ move, 0 }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_A))
        {
            pb.RuntimeBody().ApplyForce({ -move, 0 }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_SPACE))
        {
            pb.RuntimeBody().ApplyForce({ 0, move }, position.ToBox2D(), true);
        }
        if (Input::GetKeyPressed(KEY_LEFT_SHIFT))
        {
            pb.RuntimeBody().ApplyForce({ 0, -move }, position.ToBox2D(), true);
        }

        if (Input::GetKeyPressed(KEY_RIGHT))
        {
            pb.RuntimeBody().ApplyTorque(torque, true);
        }
        if (Input::GetKeyPressed(KEY_LEFT))
        {
            pb.RuntimeBody().ApplyTorque(-torque, true);
        }
    }

    void OnFixedUpdate() override
    {
        MoveEntityByInput(entityA);
    }
};

SHARD_CREATE(Game)
#endif