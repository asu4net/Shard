﻿#pragma once
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

        void ListenWindowEvents(Rendering::Window& window);
        void OnRenderReady(Rendering::RenderReadyArgs args);
        void OnRenderFrame(Rendering::RenderFrameArgs args);
    };
}