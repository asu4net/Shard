#pragma once
#ifdef PRACTICE_03

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering;
    using namespace Primitives;

    class Game final : public Application
    {
        float cameraSize = 7.f;
        Font font{"res/Fonts/transformers.ttf"};
        Quad fontQuad;
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            window.SetTitle("Practice 03 - Alejandro :D");
            fontQuad = Quad(font.GetPixelsRgb());
            fontQuad.color = Color::LightRed;
            fontQuad.scale = Vector2::one * 10.f;
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            DrawCalls();
        }
        
        void DrawCalls()
        {
            fontQuad.Draw();
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }

#endif