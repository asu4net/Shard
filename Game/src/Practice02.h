#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Rendering/Primitives.h"
#include "Shard/Math/Math.h"
#include "TimeData.h"
#include "Input.h"
#include "Conversions.h"

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering::Primitives;

    class Game final : public Application
    {
        Quad mouseQuad;

        virtual void OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args) override
        {
            
        }

        virtual void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args) override
        {
            
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }