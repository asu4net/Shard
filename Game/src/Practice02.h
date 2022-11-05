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
        float fireScaleSpeed = .2f;
        float lightScaleSpeed = .2f;
        float maxFireScale = 1.5f;
        float minFireScale = 1.f;
        float minLightScale = 4.f;
        float maxLightScale = 4.5f;
        
        Quad fire = Quad(Color::White, "Textures/fire.png");
        Quad grille = Quad(Color::White, "Textures/grille.png");
        Quad light = Quad(Color::White, "Textures/light.png");
        Quad lightBorderDown = Quad(Color::Black);
        Quad lightBorderTop = Quad(Color::Black);
        Quad lightBorderRight = Quad(Color::Black);
        Quad lightBorderLeft = Quad(Color::Black);
        Quad wall = Quad(Color::White, "Textures/wall.jpg");
        
        void OnRenderReady(ShardEvents::OnRenderReadyEventArgs args) override
        {
            fire.mode = BlendingMode::Add;
            
            grille.mode = BlendingMode::Alpha;
            grille.scale = Vector2::one * 8.f;
            grille.uvMultiplier = 6.f;
            
            light.mode = BlendingMode::Multiply;
            light.scale = Vector2::one * 4.f;

            lightBorderDown.scale = {20, 3, 0};
            lightBorderTop.scale = {20, 3, 0};
            lightBorderRight.scale = {10, 20, 0};
            lightBorderLeft.scale = {10, 20, 0};

            wall.scale = Vector2::one * 8.f;
            wall.mode = BlendingMode::Solid;
            wall.uvMultiplier = 4.f;
            
            m_Window.SetBackgroundColor(Color::Red);
            StaticCamera::window = &m_Window;
            StaticCamera::size = cameraSize;
        }

        void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs args) override
        {
            DrawCalls();
            
            fire.position = MouseWorld();
            light.position = MouseWorld();
            lightBorderDown.position = light.position + Vector3::down * 3.f;
            lightBorderTop.position = light.position + Vector3::up * 3.f;
            lightBorderRight.position = light.position + Vector3::right * 7.f;
            lightBorderLeft.position = light.position + Vector3::left * 7.f;

            AnimateScale(fire.scale, fireScaleSpeed, minFireScale, maxFireScale);
            AnimateScale(light.scale, lightScaleSpeed, minLightScale, maxLightScale);
        }

        void AnimateScale(Vector3& scale, float& speed, const float min, const float max)
        {
            scale = scale + Vector3::one * speed * Time::DeltaTime();
            
            if (scale.x >= max)
            {
                scale = Vector3::one * max;
                speed *= -1;
            }
            else if (scale.x <= min)
            {
                scale = Vector3::one * min;
                speed *= -1;
            }
        }

        Vector3 MouseWorld()
        {
            const Vector3 mousePos = Input::GetMousePosition();
            printf("%f, %f\n", mousePos.x, mousePos.y);
            return m_Window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
        }

        void DrawCalls()
        {
            wall.Draw();
            grille.Draw();
            light.Draw();
            lightBorderDown.Draw();
            lightBorderTop.Draw();
            lightBorderRight.Draw();
            lightBorderLeft.Draw();
            fire.Draw();
            
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }