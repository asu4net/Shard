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
        Font font{&window, "res/Fonts/transformers.ttf"};
        Quad fontQuad;
        Text text;
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            text = Text(&font, "pito", Color::LightBlue);
            text.SetContent("pito");
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            window.SetTitle("Practice 03 - Alejandro :D");
            
            fontQuad.AddTexture(font.GetPixelsRgb());
            fontQuad.position = fontQuad.position + Vector2::right * -6.f;
            fontQuad.color = Color::LightRed;
            fontQuad.scale = Vector2::one * 10.f;
            text.position = Vector2::right * 3.f;
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            text.Draw();
            fontQuad.Draw();
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }

#endif