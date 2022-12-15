#pragma once
#ifdef TEST

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Test - Alejandro :D");

        Entity entityA = scene.CreateEntity("test");
        {
            entityA.Get<Transform>().position += Vector3::up * 2.f;
            auto& collider = entityA.Add<BoxCollider2D>();
            entityA.Add<Physicbody2D>();
        }

        Entity entityB = scene.CreateEntity();
        {
            entityB.Get<Transform>().position += Vector3::down * 2.f;
            TransformSystem::Rotate(entityB.Get<Transform>(), 12, Vector3::forward);

            auto& collider = entityB.Add<BoxCollider2D>();
            auto& pb = entityB.Add<Physicbody2D>();
            collider.center = { 0, 1 };
            collider.size = { 3, 1 };
            pb.RuntimeBody().SetType((b2BodyType)Physicbody2D::BodyType::Kinematic);
        }
    }
};

SHARD_CREATE(Game)
#endif