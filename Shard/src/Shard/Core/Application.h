#pragma once
#include "ImGuiImp/ImGuiLayer.h"
#include "Rendering/Window.h"

namespace Shard
{
    class Application
    {
    public:
        Rendering::Window window;
        ImGuiImp::ImGuiLayer imGuiLayer;

        Application();
        virtual ~Application();

        virtual void Start();

        virtual void OnRenderReady(Rendering::OnRenderReadyEventArgs args);
        virtual void OnRenderFrame(Rendering::OnRenderFrameEventArgs args);
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
