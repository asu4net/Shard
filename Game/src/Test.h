#pragma once

#ifdef TEST

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering;
    using namespace Ecs;

    class Game final : public Application
    {
        float cameraSize = 7.f;
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            Entity circle = scene.CreateEntity();
            circle.Add<Circle>();
            circle.Get<Transform>().position += Vector3::right * 3;
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }
#endif