#pragma once
#include "Rendering/Window.h"

namespace Shard::ImGuiImp
{
    class ImGuiLayer
    {
    private:
        Rendering::Window* m_window = nullptr;
        
    public:
        explicit ImGuiLayer(Rendering::Window* window);
        
        void OnRenderReady(Rendering::OnRenderReadyEventArgs args);
        void OnRenderFrame(Rendering::OnRenderFrameEventArgs args);
    };
}