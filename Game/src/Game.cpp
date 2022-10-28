#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/ShardEvents/Event.h"
#include "Shard/Rendering/Window.h"
#include "Shard/Math/Vector2.h"

namespace Game
{
    class Game final : public Shard::Application
    {
        virtual void Start() override
        {
            Application::Start();

            Shard::Rendering::Window window;
            window.StartLoop();

            Shard::Math::Vector2 vector;
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }