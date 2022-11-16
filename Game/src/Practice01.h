#pragma once
#ifdef PRACTICE_01

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

    void OnRenderReady(RenderReadyArgs args) override
    {
        StaticCamera::window = &window;
        StaticCamera::size = cameraSize;
    }

    void OnRenderFrame(RenderFrameArgs args) override
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

        window.SetTitle(title);
    }

    Vector3 MouseWorld()
    {
        const Vector3 mousePos = Input::GetMousePosition();
        return window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
    }

    void DrawCalls()
    {
        mouseQuad.Draw();
        circle.Draw();
        centerQuad.Draw();
        StaticCamera::CalculateMatrices();
    }
};

SHARD_CREATE(Game)
#endif