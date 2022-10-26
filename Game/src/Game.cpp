#include "Shard/Core/Application.h"
#include "Shard/Core/EntryPoint.h"
#include "Shard/Event/Event.h"

namespace Game
{
    class Game final : public Shard::Application
    {
        virtual void Start() override
        {
            Application::Start();
        }
    };
}

Shard::Application* Shard::CreateApplication() { return new Game::Game(); }