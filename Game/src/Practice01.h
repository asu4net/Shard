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
        Quad centerQuad;
        Circle circle;

        float degreesPerSecond = 32.f;
        float deltaRadians = 0;
        float circleOffset = 2.f;

        virtual void OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args) override
        {
            circle = Circle(Color::lightBlue);
            centerQuad = Quad(Color::lightRed, "Textures/fire.png");
            mouseQuad = Quad(Color::lightGreen);
        }

        virtual void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args) override
        {
            centerQuad.Draw();
            mouseQuad.Draw();
            circle.Draw();

            Vector2 mousePos = Input::GetMousePosition();
            Vector3 mouseWorldPos = m_Window.ScreenToWorldPoint(mousePos, mouseQuad.projection, mouseQuad.view);
            mouseQuad.position = Vector3(mouseWorldPos, 0);

            deltaRadians += (degreesPerSecond * g_Radians) * Time::DeltaTime();

            Vector2 newPos = Vector2::RotateAround(mouseWorldPos, Vector2(mouseWorldPos) + Vector2::one * circleOffset, deltaRadians);

            circle.position = newPos;

            float angle = Vector2::Angle(mouseWorldPos, circle.position);
            float distance = Vector2::Distance(Vector3::zero, mouseWorldPos);

            std::string title = "Distance: "
                + StringFromNumber(distance)
                + " -- Angle: "
                + StringFromNumber(angle);

            m_Window.SetTitle(title);
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }