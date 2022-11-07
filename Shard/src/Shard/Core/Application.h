#pragma once
#include "ImGui/ImGuiRenderer.h"

namespace Shard
{
    class Application
    {
    public:
        Rendering::Window window;
        ImGuiRenderer imGuiRenderer;

        Application();
        virtual ~Application();

        virtual void Start();

        virtual void OnImGuiReady(ImGuiReadyArgs args);
        virtual void OnImGuiRender(ImGuiRenderArgs args);
        virtual void OnRenderReady(Rendering::RenderReadyArgs args);
        virtual void OnRenderFrame(Rendering::RenderFrameArgs args);
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
