#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Rendering/Primitives.h"
#include "TimeData.h"
#include "Input.h"
#include "Rendering/Font.h"

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering;
    using namespace Primitives;

    class Game final : public Application
    {
        float cameraSize = 7.f;
        Rendering::Font font{"res/Fonts/cubic.ttf"};
        
        void OnRenderReady(Rendering::OnRenderReadyEventArgs args) override
        {
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            window.SetTitle("Practice 03 - Alejandro :D");
        }

        void OnRenderFrame(OnRenderFrameEventArgs args) override
        {
            DrawCalls();
            
        }

        void DrawCalls()
        {
            
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }