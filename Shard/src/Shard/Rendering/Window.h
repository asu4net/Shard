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
          Normal
        , Disabled
        , Hidden
    };

    class Window
    {
    public:
        static const char* DefaultTitle;
        static const int DefaultWidth;
        static const int DefaultHeight;
        static const Math::Color DefaultColor;
        static const CursorMode DefaultCursorMode;
        static bool ShowOpenGlDebugMessages;
        static bool KeepWindowOpened;
        
        ShardEvents::Event<ShardEvents::OnRenderFrameEventArgs> OnRenderFrame;
        ShardEvents::Event<ShardEvents::OnRenderReadyEventArgs> OnRenderReady;
        
        Window();
        Window(const int width, const int height, const char* name = DefaultTitle, const Math::Color& color = DefaultColor);
        Window(const Window& other) = delete;
        Window(Window&& other) = delete;
        ~Window() = default;
        
        Window& operator=(Window other) = delete;
        Window& operator=(Window&& other) = delete;
        
        const std::string& GetTitle() const;
        void SetTitle(const std::string& title);

        CursorMode GetCursorMode() const;
        void SetCursorMode(const CursorMode mode);

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

        void Initialise();
        void SetProperties();
    };
}

