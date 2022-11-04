#include "Window.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include <stdio.h>
#include "TimeData.h"
#include "Renderer.h"

namespace Shard::Rendering
{
	bool Window::ShowOpenGlDebugMessages = true;

	static void APIENTRY OnDebugMessage(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam)
	{
		if (!Window::ShowOpenGlDebugMessages) return;
		printf("OpenGL: %s\n", message);
	}

	static int CursorModeValue(CursorMode _cursorMode)
	{
		switch (_cursorMode)
		{
		case Shard::Rendering::CursorMode::Normal:
			return GLFW_CURSOR_NORMAL;
		case Shard::Rendering::CursorMode::Disabled:
			return GLFW_CURSOR_DISABLED;
		case Shard::Rendering::CursorMode::Hidden:
			return GLFW_CURSOR_HIDDEN;
		default:
			return 0;
		}
	}

	Window::Window()
		: m_title("Default Shard Window")
		, m_height(1080)
		, m_width(1920)
		, m_color(Math::Color::darkGray)
	{
		Init();
	}

	Window::Window(int width, int height, const char* _Title, Math::Color color)
		: m_title(_Title)
		, m_height(height)
		, m_width(width)
		, m_color(color)
	{
		Init();
	}

	bool Window::Init()
	{
		m_window = nullptr;
		m_bufferWidth = 0;
		m_bufferHeight = 0;
		m_cursorMode = CursorMode::Normal;

		if (!glfwInit())
		{
			printf("GLFW initialisation failed!\n");
			return false;
		}

		SetProperties();

		m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

		if (!m_window)
		{
			printf("GLFW window creation failed!\n");
			glfwTerminate();
			return false;
		}

		glfwGetFramebufferSize(m_window, &m_bufferWidth, &m_bufferHeight);

		//Provides glfwWindow as open gl context.
		glfwMakeContextCurrent(m_window);

		//INPUT ASSIGNEMENT
		Input::Init(m_window);

		//Cursor settings
		SetCursorMode(CursorMode::Normal);

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			printf("GLEW initialisation failed!\n");
			glfwDestroyWindow(m_window);
			glfwTerminate();
			return false;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OnDebugMessage, nullptr);

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_bufferWidth, m_bufferHeight);
		glfwSetWindowUserPointer(m_window, this);

		Renderer::Init();

		return true;
	}

	const std::string& Window::GetTitle() const { return m_title; }

	void Window::SetTitle(const std::string& title)
	{
		m_title = title;
		glfwSetWindowTitle(m_window, title.c_str());
	}

	CursorMode Window::GetCursorMode() const { return m_cursorMode; }

	Math::Vector3 Window::ScreenToWorldPoint(Math::Vector2 _ScreenPoint, glm::mat4 proj, glm::mat4 view)
	{
		float halfScreenWidth =  static_cast<float>(m_width) / 2;
		float halfScreenHeight =  static_cast<float>(m_height) / 2;
		glm::mat4 inverseMV = glm::inverse(proj * view);
		glm::vec4 near = glm::vec4(((_ScreenPoint.x - halfScreenWidth) / halfScreenWidth),
			(-1 * (_ScreenPoint.y - halfScreenHeight) / halfScreenHeight), -1, 1.0);
		glm::vec4 nearResult = inverseMV * near;
		nearResult /= nearResult.w;
		return Math::Vector3(nearResult.x, nearResult.y, 0);
	}

	void Window::SetCursorMode(CursorMode mode)
	{
		m_cursorMode = mode;
		glfwSetInputMode(m_window, GLFW_CURSOR, CursorModeValue(m_cursorMode));
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

		while (!glfwWindowShouldClose(m_window))
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