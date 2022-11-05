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
        Quad mouseQuad = Quad(Color::LightRed);
        Quad centerQuad = Quad(Color::LightGreen);
        Circle circle = Circle(Color::LightBlue);

        const float startDegreeOffset = 45.f;
        const float startRadians = startDegreeOffset * ToRadians;
        
        float degreesPerSecond = 32.f;
        float radians = startRadians;
        float circleOffset = 2.f;
        float cameraSize = 7.f;

        void OnRenderReady(ShardEvents::OnRenderReadyEventArgs args) override
        {
            StaticCamera::window = &m_Window;
            StaticCamera::size = cameraSize;
        }

        void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs args) override
        {
            DrawCalls();
            
            mouseQuad.position = MouseWorld();

            radians += (degreesPerSecond * ToRadians) * Time::DeltaTime();
            
            const float displayRadians = radians / ToRadians - startDegreeOffset;
            if (displayRadians >= 360) radians = startRadians;

            circle.position = Vector2::RotateAround(mouseQuad.position, Vector2(mouseQuad.position) + Vector2::one * circleOffset, radians);

            const std::string title = "Practice 01 - Alejandro :D |||| Distance: "
                + StringFromNumber(Vector2::Distance(Vector3::zero, mouseQuad.position))
                + " -- Angle: "
                + StringFromNumber(displayRadians);

            m_Window.SetTitle(title);
        }

        Vector3 MouseWorld()
        {
            const Vector3 mousePos = Input::GetMousePosition();
            return m_Window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
        }

        void DrawCalls()
        {
            mouseQuad.Draw();
            circle.Draw();
            centerQuad.Draw();
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }