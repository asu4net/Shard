#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Rendering/Primitives.h"
#include "Shard/Math/Math.h"
#include "TimeData.h"
#include "Input.h"

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering::Primitives;

    class Game final : public Application
    {
        Quad mouseQuad;
        Quad centerQuad;
        Circle circle;
        float degreesPerSecond = 32.f;
        float deltaRadians = 0;
        float circleOffset = 2.f;

        virtual void OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args) override
        {
            circle = Circle(Color::lightBlue);
            centerQuad = Quad(Color::lightRed);
            mouseQuad = Quad(Color::lightGreen);
        }

        virtual void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args) override
        {
            centerQuad.Draw();
            circle.Draw();
            mouseQuad.Draw();

            Vector2 mousePos = Input::GetMousePosition();
            Vector3 screenWorld = m_Window.ScreenToWorldPoint(Vector3(mousePos.x, mousePos.y, 0), mouseQuad.projection, mouseQuad.view);
            mouseQuad.Translate(screenWorld);

            deltaRadians += (degreesPerSecond * g_Radians) * Time::DeltaTime();

            Vector2 newPos = Vector2::RotateAround(screenWorld, Vector2(screenWorld) + Vector2(circleOffset, circleOffset), deltaRadians);

            circle.Translate(Vector3(newPos, 0));
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }