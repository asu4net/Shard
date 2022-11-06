#pragma once
#include "Rendering/Window.h"

namespace Shard::ImGuiImp
{
    class ImGuiLayer
    {
        inline static bool showDemo = true;
        
    public:
        ImGuiLayer() = default;
        explicit ImGuiLayer(Rendering::Window* window);
        
        void OnRenderReady(Rendering::OnRenderReadyEventArgs args);
        void OnRenderFrame(Rendering::OnRenderFrameEventArgs args);
    };
}