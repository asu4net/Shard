#pragma once
#ifdef TEST

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        const Entity circle = scene.CreateEntity();
        circle.Add<CircleRenderer>(Color::LightRed);
        circle.Get<Transform>().position += Vector3::right * 3;
    }
};

SHARD_APPLICATION(Game)
#endif