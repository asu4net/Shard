#pragma once
#ifdef TEST

class Game final : public Application
{
    std::string linesKey;

    void OnRenderReady(RenderReadyArgs args) override
    {
        Line lineA{ Vector3::zero, Vector3::right };
        Line lineB{ Vector3::right, Vector3::up };
        linesKey = Renderer::AddLineGroup({ lineA, lineB });
    }

    void OnRenderFrame(RenderFrameArgs args) override
    {
        Camera& camera = scene.GetMainCameraEntity().Get<Camera>();
        MvpData mvp{ glm::mat4(1), camera.View(), camera.Projection() };

        Renderer::DrawLines(linesKey, mvp);
    }
};

SHARD_CREATE(Game)
#endif