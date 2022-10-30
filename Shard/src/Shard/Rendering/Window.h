#pragma once
#include "Core.h"
#include "ShardEvents/EventArgs.h"
#include "ShardEvents/Event.h"
#include "Math/Color.h"
#include <string>

#include "Rendering/Primitives.h"
#include "gtc/matrix_transform.hpp"

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
        Event<OnRenderReadyEventArgs> OnRenderReady;
        static bool s_ShowOpenGLDebugMessages;
        
        Window();
        Window(int _Width, int _Height, const char* _Name, Math::Color _Color);

        const std::string& GetName() const;
        void SetName(const char* _Name);

        CursorMode GetCursorMode() const;
        void SetCursorMode(CursorMode _Mode);

        glm::vec3 ScreenToWorldPoint(glm::vec2 _ScreenPoint, glm::mat4 _Proj = glm::mat4(1), glm::mat4 _View = glm::mat4(1));

        float CurrentTime() const;
        void StartLoop();

    private:
        std::string m_Name;
        GLFWwindow* m_Window;
        int m_Width, m_Height;
        Math::Color m_Color;
        int m_BufferWidth, m_BufferHeight;
        CursorMode m_CursorMode;

        bool Init();
        void SetProperties();
    };
}

