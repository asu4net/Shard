#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Rendering/Primitives.h"
#include "Shard/Math/Math.h"
#include "Input.h"
#include "Conversions.h"

namespace Game
{
    using namespace Shard;
    using namespace Math;
    using namespace Rendering::Primitives;

    class Game final : public Application
    {
    public:
        float cameraSize = 2.f;
        
        Quad fire = Quad(Color::white, "Textures/fire.png");
        Quad grille = Quad(Color::white, "Textures/grille.png");
        Quad light = Quad(Color::white, "Textures/light.png");
        Quad wall = Quad(Color::white, "Textures/wall.jpg");
        
        void OnRenderReady(ShardEvents::OnRenderReadyEventArgs args) override
        {
            m_Window.SetBackgroundColor(Color::darkGray);
            StaticCamera::window = &m_Window;
            StaticCamera::size = cameraSize;
            
            light.scale = Vector2::one * 4;
            wall.scale = Vector2::one * 4;
        }

        void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs args) override
        {
            GraphicCalculations();
            
            fire.position = MouseWorld();
            light.position = MouseWorld();
        }

        Vector3 MouseWorld()
        {
            const Vector3 mousePos = Input::GetMousePosition();
            return m_Window.ScreenToWorldPoint(mousePos, StaticCamera::projection, StaticCamera::view);
        }

        void GraphicCalculations()
        {
            fire.Draw();
            light.Draw();
            grille.Draw();
            wall.Draw();
            StaticCamera::CalculateMatrices();
        }
    };
}

inline Shard::Application* Shard::CreateApplication() { return new Game::Game(); }