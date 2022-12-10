#pragma once
#ifdef TEST

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        Entity entity = scene.CreateEntity();
        auto& collider = entity.Add<BoxCollider2D>();
        collider.center = { 0, 1 };
        collider.size = { 3, 1 };

        auto& transform = entity.Get<Transform>();
        TransformSystem::Rotate(transform, 10, { 0, 0, 1 });
    }
};

SHARD_CREATE(Game)
#endif