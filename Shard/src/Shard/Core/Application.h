#pragma once
#include "Ecs/Scene.h"
#include "ImGui/ImGuiRenderer.h"

#define SHARD_CREATE(_CLASS_NAME) inline Shard::Application* Shard::CreateApplication() { return new _CLASS_NAME(); }

namespace Shard
{
    class Application
    {
    public:
        Rendering::Window window;
        ImGuiRenderer imGuiRenderer;
        Ecs::Scene scene;
        
        Application();
        virtual ~Application();

        virtual void OnCreate();

        virtual void OnImGuiReady(ImGuiReadyArgs args);
        virtual void OnImGuiRender(ImGuiRenderArgs args);
        virtual void OnRenderReady(Rendering::RenderReadyArgs args);
        virtual void OnRenderFrame(Rendering::RenderFrameArgs args);
        virtual void OnFixedUpdate();
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
