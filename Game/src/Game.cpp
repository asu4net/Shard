#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Rendering/Primitives.h"
#include "Input.h"

namespace Game
{
    using namespace Shard;

    class Game final : public Application
    {
        Rendering::Primitives::Quad quad;
        Rendering::Primitives::Circle circle;
        glm::mat4 model;

        virtual void OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args) override
        {
            circle.color = glm::vec4(0, 1, 0, 1);
            model = quad.transform;
        }

        virtual void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args) override
        {
            circle.CalculateMatrix();
            circle.Draw();

            quad.CalculateMatrix();
            quad.Draw();

            glm::vec2 mousePos = Input::GetMousePosition();
            glm::vec3 screenWorld = m_Window.ScreenToWorldPoint(glm::vec3(mousePos.x, mousePos.y, 0), quad.projection, quad.view);
            quad.transform = glm::translate(model, glm::vec3(screenWorld.x, screenWorld.y, 0));
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }