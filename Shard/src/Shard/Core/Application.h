#pragma once
#include "Ecs/Scene/Scene.h"
#include "ImGui/ImGuiRenderer.h"

#define SHARD_CREATE(_CLASS_NAME) inline Shard::Application* Shard::CreateApplication() { return new _CLASS_NAME(); }

namespace Shard
{
    class Application
    {
    public:
        Window window;
        Scene scene;
        ImGuiRenderer imGuiRenderer;
        
        Application();
        virtual ~Application();
        
        virtual void PreInitialize();
        virtual void Initialize();
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}