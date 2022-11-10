﻿#pragma once
#ifdef PRACTICE_04

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering;
    using namespace Primitives;

    class Game final : public Application
    {
        float cameraSize = 7.f;
        Quad bee{"res/Textures/bee_anim.png"};
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            window.SetTitle("Practice 03 - Alejandro :D");
            window.SetBackgroundColor(Color::DarkGray);

            bee.scale = Vector2::one * 1.5f;
            bee.LoadSheet({90, 90}, {1, 8});
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            bee.currentSubMesh = 7;
            bee.Draw();
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }

#endif