#include "Window.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include <cstdio>
#include "TimeData.h"
#include "Renderer.h"

namespace Shard::Rendering
{
	static void APIENTRY OnDebugMessage(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam)
	{
		if (!Window::ShowOpenGlDebugMessages) return;
		printf("OpenGL: %s\n", message);
	}

	void FrameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
	{
		glViewport(0, 0, width, height);
		glScissor(0, 0, width, height);
	}
	
	const char* Window::DefaultTitle = "Default Shard Window";
	constexpr int Window::DefaultWidth = 1920;
	constexpr int Window::DefaultHeight = 1080;
	const Math::Color Window::DefaultColor = Math::Color::DarkGrey;
	constexpr CursorMode Window::DefaultCursorMode = CursorMode::Normal;
	bool Window::ShowOpenGlDebugMessages = true;
	bool Window::KeepWindowOpened = true;
	
	Window::Window()
		: m_title(DefaultTitle)
		, m_window(nullptr)
		, m_width(DefaultWidth)
		, m_height(DefaultHeight)
		, m_color(DefaultColor)
		, m_bufferWidth(0)
		, m_bufferHeight(0)
		, m_cursorMode(DefaultCursorMode)
	{
		Initialise();
	}

	Window::Window(const int width, const int height, const char* name, const Math::Color& color)
		: m_title(name)
		, m_window(nullptr)
		, m_width(width)
		, m_height(height)
		, m_color(color)
		, m_bufferWidth(0)
		, m_bufferHeight(0)
		, m_cursorMode(CursorMode::Normal)
	{
		Initialise();
	}

	void Window::Initialise()
	{
		if (!glfwInit())
		{
			printf("GLFW initialisation failed!\n");
			return;
		}

		SetProperties();

		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			printf("GLFW window creation failed!\n");
			glfwTerminate();
			return;
		}

		glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);
		glfwMakeContextCurrent(m_window);
		glfwSetFramebufferSizeCallback(m_window, FrameBufferSizeCallback);
		Input::Init(m_window);
		SetCursorMode(m_cursorMode);

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			printf("GLEW initialisation failed!\n");
			glfwDestroyWindow(m_window);
			glfwTerminate();
			return;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OnDebugMessage, nullptr);

		//glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_bufferWidth, m_bufferHeight);
		glfwSetWindowUserPointer(m_window, this);

		Renderer::Init();
	}

	const std::string& Window::GetTitle() const { return m_title; }

	void Window::SetTitle(const std::string& title)
	{
		m_title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}

	CursorMode Window::GetCursorMode() const { return m_cursorMode; }

	Math::Vector3 Window::ScreenToWorldPoint(const Math::Vector2 screenPoint, const glm::mat4 proj, const glm::mat4 view)
	{
		const float halfScreenWidth =  static_cast<float>(m_width) / 2;
		const float halfScreenHeight =  static_cast<float>(m_height) / 2;
		const glm::mat4 inverseMv = glm::inverse(proj * view);
		const glm::vec4 near = glm::vec4(((screenPoint.x - halfScreenWidth) / halfScreenWidth),(-1 * (screenPoint.y - halfScreenHeight) / halfScreenHeight), -1, 1.0);
		glm::vec4 nearResult = inverseMv * near;
		nearResult /= nearResult.w;
		return {nearResult.x, nearResult.y, 0};
	}

	void Window::SetCursorMode(const CursorMode mode)
	{
		m_cursorMode = mode;
		
		switch (m_cursorMode)
		{
		case CursorMode::Normal:
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			return;
		case CursorMode::Disabled:
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			return;
		case CursorMode::Hidden:
			glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	void Window::SetProperties()
    {
        //OpenGL version 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OpenGlMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OpenGlMinorVersion);
        //Disables deprecated code
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //Enables new code
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    }

	void Window::StartLoop()
	{
		OnRenderReady.Invoke({});

		while (!glfwWindowShouldClose(m_window) && KeepWindowOpened)
		{
			//Input events
			glfwPollEvents();

			glClearColor(m_color.r, m_color.g, m_color.b, m_color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Time::CalculateDeltaTime(CurrentTime());

			//DRAW STUFF
			OnRenderFrame.Invoke({});

			glfwSwapBuffers(m_window);
		}
	}

	float Window::CurrentTime() const
	{
		return static_cast<float>(glfwGetTime());
	}
}