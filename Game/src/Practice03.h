﻿#pragma once
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
        //Font font{"res/Fonts/transformers.ttf"};
        //Quad fontQuad;

        Quad quad{Color::LightRed};
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            window.SetTitle("Practice 03 - Alejandro :D");
            // fontQuad = Quad(font.pixelsRgb);
            // fontQuad.color = Color::LightRed;
            // fontQuad.scale = Vector2::one * 10.f;
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            DrawCalls();
        }
        
        void DrawCalls()
        {
            //fontQuad.Draw();
            StaticCamera::CalculateMatrices();
            quad.Draw();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }

#endif