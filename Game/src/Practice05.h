#pragma once

#ifdef PRACTICE_05

class Game final : public Application
{
    Entity b;

    void OnRenderReady(RenderReadyArgs args) override
    {
        {
            Entity a = scene.CreateEntity();
            auto& collider = a.Add<CircleCollider>();
            collider.radius = 1;
            a.Get<Transform>().position += Vector3::right * 2.f;
        }
        
        {
            b = scene.CreateEntity();
            auto& collider = b.Add<CircleCollider>();
            collider.radius = .5f;
        }
    }

    void OnRenderFrame(RenderFrameArgs args) override
    {
        auto& camera = scene.GetMainCameraEntity().Get<Camera>();
        Vector3 cameraPosition = window.ScreenToWorldPoint(Input::GetMousePosition(), camera.Projection(), camera.View());
        b.Get<Transform>().position = cameraPosition;
    }
};

SHARD_CREATE(Game)

#endif
