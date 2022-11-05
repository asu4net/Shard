#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Rendering/Primitives.h"
#include "Shard/Math/Math.h"
#include "Input.h"
#include "Conversions.h"
#include "TimeData.h"

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering::Primitives;

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
        
        Quad fire = Quad("Textures/fire.png", BlendingMode::Add);
        Quad grille = Quad("Textures/grille.png", BlendingMode::Alpha, 6.f);
        Quad light = Quad("Textures/light.png", BlendingMode::Multiply);
        Quad wall = Quad("Textures/wall.jpg", BlendingMode::Solid, 4.f);
        
        Quad lightBorderDown = Quad(Color::Black, Quad::DefaultPosition, Quad::DefaultRotation, {20, 3, 0});
        Quad lightBorderTop = Quad(Color::Black, Quad::DefaultPosition, Quad::DefaultRotation, {20, 3, 0});
        Quad lightBorderRight = Quad(Color::Black, Quad::DefaultPosition, Quad::DefaultRotation, {10, 20, 0});
        Quad lightBorderLeft = Quad(Color::Black, Quad::DefaultPosition, Quad::DefaultRotation, {10, 20, 0});
        
        void OnRenderReady(ShardEvents::OnRenderReadyEventArgs args) override
        {
            m_Window.SetTitle("Practice 02 - Alejandro :D");
            StaticCamera::window = &m_Window;
            StaticCamera::size = cameraSize;
            
            fire.scale = Vector3::one * minFireScale;
            light.scale = Vector3::one * minLightScale;
            
            grille.scale = Vector2::one * 8.f;
            wall.scale = Vector2::one * 8.f;
        }

        void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs args) override
        {
            DrawCalls();
            
            fire.position = MouseWorld();
            AnimateVector(fire.scale, fireScaleSpeed, minFireScale, maxFireScale);
            
            AnimateFloat(fireCurrentDegrees, fireDegreesPerSecond, minFireDegrees, maxFireDegrees);
            fire.rotation = Quad::DefaultRotation * glm::angleAxis(glm::radians(fireCurrentDegrees), Vector3::forward.ToGlm());
            
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
            return m_Window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
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