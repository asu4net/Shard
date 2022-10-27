#pragma once
#include "Core.h"
#include "ShardEvents/EventArgs.h"
#include "ShardEvents/Event.h"
#include "Math/Color.h"

struct GLFWwindow;

namespace Shard::Rendering
{
    constexpr int g_OpenGLMinorVersion = 3;
    constexpr int g_OpenGLMajorVersion = 3;

    enum class CursorMode
    {
        Normal, Disabled, Hidden
    };

    using namespace Shard::ShardEvents;

    class SHARD_API Window
    {
    public:
        Event<OnRenderFrameEventArgs> OnRenderFrame;
        const char* m_Name;
        static bool s_ShowOpenGLDebugMessages;
        
        Window();
        Window(int _Width, int _Height, const char* _Name, Math::Color _Color);

        void StartLoop();

    private:
        GLFWwindow* m_Window;
        int m_Width, m_Height;
        Math::Color m_Color;
        int m_BufferWidth, m_BufferHeight;
        CursorMode m_CursorMode;

        bool Init();
        void SetProperties();
    };
}

