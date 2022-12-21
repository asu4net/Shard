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
        ImGuiRenderer imGuiRenderer;
        Scene scene;
        
        Application();
        virtual ~Application();

        virtual void OnCreate();

        virtual void OnImGuiReady(ImGuiReadyArgs args);
        virtual void OnImGuiRender(ImGuiRenderArgs args);
        virtual void OnRenderReady(RenderReadyArgs args);
        virtual void OnRenderFrame(RenderFrameArgs args);
        virtual void OnFixedUpdate();
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
