#pragma once
#ifdef TEST

class Game final : public Application
{
    Entity entity;

    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Test - Alejandro :D");

        entity = scene.CreateEntity();
        auto& collider = entity.Add<BoxCollider2D>();
        collider.center = { 0, 1 };
        collider.size = { 3, 1 };

        entity.Add<Physicbody2D>();
    }

    void OnRenderFrame(RenderFrameArgs args) override
    {
        auto& camera = scene.GetMainCameraEntity().Get<Camera>();
        /*entity.Get<Transform>().position =
            window.ScreenToWorldPoint(Input::GetMousePosition(), camera.Projection(), camera.View());*/
    }
};

SHARD_CREATE(Game)
#endif