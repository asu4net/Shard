#pragma once
#include "Core.h"
#include "Rendering/Window.h"
#include "ShardEvents/EventArgs.h"

namespace Shard
{
    class SHARD_API Application
    {
    public:
        Rendering::Window m_Window;

        Application();
        virtual ~Application();

        virtual void Start();

        virtual void OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args);
        virtual void OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args);
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
