#pragma once
#include "Rendering/Window.h"
#include "Event.h"

namespace Shard
{
    struct ImGuiReadyArgs {};
    struct ImGuiRenderArgs {};
    
    class ImGuiRenderer
    {
    public:
        inline static bool showDemo = false;
        
        Event<ImGuiRenderArgs> OnImGuiRender;
        Event<ImGuiReadyArgs> OnImGuiReady;

        void ListenWindowEvents(Window& window);
        void OnRenderReady(RenderReadyArgs args);
        void OnRenderFrame(RenderFrameArgs args);
    };
}