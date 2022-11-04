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
        float radians = 0;
        float circleOffset = 2.f;
        float cameraSize = 7.f;

        void OnRenderReady(ShardEvents::OnRenderReadyEventArgs args) override
        {
            centerQuad = Quad(Color::lightRed);
            circle = Circle(Color::lightBlue);
            mouseQuad = Quad(Color::lightGreen);
            StaticCamera::window = &m_Window;
            StaticCamera::size = cameraSize;
        }

        void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs args) override
        {
            mouseQuad.Draw();
            circle.Draw();
            centerQuad.Draw();
            StaticCamera::CalculateMatrices();
            
            Vector2 mousePos = Input::GetMousePosition();
            Vector3 mouseWorldPos = m_Window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
            mouseQuad.position = Vector3(mouseWorldPos, 0);

            radians += (degreesPerSecond * g_Radians) * Time::DeltaTime();

            Vector2 newPos = Vector2::RotateAround(mouseWorldPos, Vector2(mouseWorldPos) + Vector2::one * circleOffset, radians);

            circle.position = newPos;

            float angle = Vector2::Angle(mouseWorldPos, circle.position);
            float distance = Vector2::Distance(Vector3::zero, mouseWorldPos);

            std::string title = "Distance: "
                + StringFromNumber(distance)
                + " -- Angle: "
                + StringFromNumber(radians/g_Radians);

            m_Window.SetTitle(title);
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }