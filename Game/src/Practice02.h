#pragma once
#ifdef PRACTICE_02

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering;
    using namespace Primitives;

    class Game final : public Application
    {
    public:
        float cameraSize = 2.f;

        //Light scale
        float lightScaleSpeed = .5f;
        float minLightScale = 5.f;
        float maxLightScale = 5.4f;

        //Fire scale
        float fireScaleSpeed = .5f;
        float minFireScale = 0.8f;
        float maxFireScale = 1.2f;
        
        //Fire rotation
        float fireCurrentDegrees = 0.f;
        float fireDegreesPerSecond = 10.f;
        float minFireDegrees = -10.f;
        float maxFireDegrees = 10.f;
        
        Quad fire = Quad("res/Textures/fire.png", BlendingMode::Add);
        Quad grille = Quad("res/Textures/grille.png", BlendingMode::Alpha, 6.f);
        Quad light = Quad("res/Textures/light.png", BlendingMode::Multiply);
        Quad wall = Quad("res/Textures/wall.jpg", BlendingMode::Solid, 4.f);
        
        Quad lightBorderDown = Quad(Color::Black, Vector3::zero, IdentityQuat, {22, 4, 0});
        Quad lightBorderTop = Quad(Color::Black, Vector3::zero, IdentityQuat, {22, 4, 0});
        Quad lightBorderRight = Quad(Color::Black, Vector3::zero, IdentityQuat, {12, 22, 0});
        Quad lightBorderLeft = Quad(Color::Black, Vector3::zero, IdentityQuat, {12, 22, 0});
        
        void OnRenderReady(RenderReadyArgs args) override
        {
            window.SetTitle("Practice 02 - Alejandro :D");
            StaticCamera::window = &window;
            StaticCamera::size = cameraSize;
            
            fire.scale = Vector3::one * minFireScale;
            light.scale = Vector3::one * minLightScale;
            
            grille.scale = Vector2::one * 10.f;
            wall.scale = Vector2::one * 10.f;
        }

        void OnRenderFrame(RenderFrameArgs args) override
        {
            DrawCalls();
            
            fire.position = MouseWorld();
            AnimateVector(fire.scale, fireScaleSpeed, minFireScale, maxFireScale);
            
            AnimateFloat(fireCurrentDegrees, fireDegreesPerSecond, minFireDegrees, maxFireDegrees);
            fire.rotation = IdentityQuat * glm::angleAxis(glm::radians(fireCurrentDegrees), Vector3::forward.ToGlm());
            
            light.position = MouseWorld();
            lightBorderDown.position = light.position + Vector3::down * 3.5f;
            lightBorderTop.position = light.position + Vector3::up * 3.5f;
            lightBorderRight.position = light.position + Vector3::right * 7.5f;
            lightBorderLeft.position = light.position + Vector3::left * 7.5f;
            
            AnimateVector(light.scale, lightScaleSpeed, minLightScale, maxLightScale);
        }

        void AnimateFloat(float& theFloat, float& speed, const float min, const float max)
        {
            theFloat += speed * Time::DeltaTime();

            if (theFloat >= max)
            {
                theFloat = max;
                speed *= -1;
            }
            else if (theFloat <= min)
            {
                theFloat = min;
                speed *= -1;
            }
        }
        
        void AnimateVector(Vector3& vector, float& speed, const float min, const float max)
        {
            vector = vector + Vector3::one * speed * Time::DeltaTime();
            
            if (vector.x >= max)
            {
                vector = Vector3::one * max;
                speed *= -1;
            }
            else if (vector.x <= min)
            {
                vector = Vector3::one * min;
                speed *= -1;
            }
        }

        Vector3 MouseWorld()
        {
            const Vector3 mousePos = Input::GetMousePosition();
            return window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
        }

        void DrawCalls()
        {
            wall.Draw();
            fire.Draw();
            grille.Draw();
            light.Draw();
            lightBorderDown.Draw();
            lightBorderTop.Draw();
            lightBorderRight.Draw();
            lightBorderLeft.Draw();
            
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }

#endif