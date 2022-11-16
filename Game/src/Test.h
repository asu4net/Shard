#pragma once
#ifdef TEST

using namespace Ecs;

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        const Entity circle = scene.CreateEntity();
        circle.Add<Circle>();
        circle.Get<Transform>().position += Vector3::right * 3;
    }
};

SHARD_APPLICATION(Game)
#endif