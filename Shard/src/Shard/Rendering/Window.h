#pragma once
#include "ShardEvents/EventArgs.h"
#include "ShardEvents/Event.h"
#include "Math/Math.h"
#include <string>

#include "gtc/matrix_transform.hpp"

struct GLFWwindow;

namespace Shard::Rendering
{
    constexpr int OpenGlMinorVersion = 3;
    constexpr int OpenGlMajorVersion = 3;

    enum class CursorMode
    {
        Normal, Disabled, Hidden
    };

    using namespace Shard::ShardEvents;

    class Window
    {
    public:
        Event<OnRenderFrameEventArgs> OnRenderFrame;
        Event<OnRenderReadyEventArgs> OnRenderReady;
        static bool ShowOpenGlDebugMessages;
        
        Window();
        Window(int width, int height, const char* name, Math::Color color);

        const std::string& GetTitle() const;
        void SetTitle(const std::string& title);

        CursorMode GetCursorMode() const;
        void SetCursorMode(CursorMode mode);

        float GetAspect() const { return static_cast<float>(m_bufferWidth) / static_cast<float>(m_bufferHeight); }
        void SetBackgroundColor(const Math::Color& color) { m_color = color; }
        
        Math::Vector3 ScreenToWorldPoint(Math::Vector2 screenPoint, glm::mat4 proj = glm::mat4(1), glm::mat4 view = glm::mat4(1));

        float CurrentTime() const;
        void StartLoop();

    private:
        std::string m_title;
        GLFWwindow* m_window;
        int m_width, m_height;
        Math::Color m_color;
        int m_bufferWidth, m_bufferHeight;
        CursorMode m_cursorMode;

        bool Init();
        void SetProperties();
    };
}

