#include "Window.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "Input.h"
#include <stdio.h>
#include "TimeData.h"
#include "Renderer.h"

//TODO: Getters y setters: mouse, tamaño de ventana, nombre de ventana, aspect ratio

namespace Shard::Rendering
{
	bool Window::s_ShowOpenGLDebugMessages = true;

	static void APIENTRY OnDebugMessage(GLenum source, GLenum type, unsigned int id, GLenum severity,
		GLsizei length, const char* message, const void* userParam)
	{
		if (!Window::s_ShowOpenGLDebugMessages) return;
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
		: m_Name("Default Shard Window")
		, m_Height(600)
		, m_Width(800)
		, m_Color(Math::Color())
	{
		Init();
	}

	Window::Window(int _Width, int _Height, const char* _Name, Math::Color _Color)
		: m_Name(_Name)
		, m_Height(_Height)
		, m_Width(_Width)
		, m_Color(_Color)
	{
		Init();
	}

	bool Window::Init()
	{
		m_Window = nullptr;
		m_BufferWidth = 0;
		m_BufferHeight = 0;
		m_CursorMode = CursorMode::Normal;

		if (!glfwInit())
		{
			printf("GLFW initialisation failed!\n");
			return false;
		}

		SetProperties();

		m_Window = glfwCreateWindow(m_Width, m_Height, m_Name.c_str(), nullptr, nullptr);

		if (!m_Window)
		{
			printf("GLFW window creation failed!\n");
			glfwTerminate();
			return false;
		}

		glfwGetFramebufferSize(m_Window, &m_BufferWidth, &m_BufferHeight);

		//Provides glfwWindow as open gl context.
		glfwMakeContextCurrent(m_Window);

		//INPUT ASSIGNEMENT
		Input::Init(m_Window);

		//Cursor settings
		SetCursorMode(CursorMode::Normal);

		glewExperimental = true;

		if (glewInit() != GLEW_OK)
		{
			printf("GLEW initialisation failed!\n");
			glfwDestroyWindow(m_Window);
			glfwTerminate();
			return false;
		}

		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

		glDebugMessageCallback(OnDebugMessage, nullptr);

		glEnable(GL_DEPTH_TEST);
		glViewport(0, 0, m_BufferWidth, m_BufferHeight);
		glfwSetWindowUserPointer(m_Window, this);

		Renderer::Init();

		return true;
	}

	const std::string& Window::GetName() const { return m_Name; }

	void Window::SetName(const char* _Name)
	{
		m_Name = _Name;
		glfwSetWindowTitle(m_Window, _Name);
	}

	CursorMode Window::GetCursorMode() const { return m_CursorMode; }

	glm::vec3 Window::ScreenToWorldPoint(glm::vec2 _ScreenPoint, glm::mat4 _Proj, glm::mat4 _View)
	{
		float halfScreenWidth =  static_cast<float>(m_Width) / 2;
		float halfScreenHeight =  static_cast<float>(m_Height) / 2;
		glm::mat4 inverseMV = glm::inverse(_Proj * _View);
		glm::vec4 near = glm::vec4(((_ScreenPoint.x - halfScreenWidth) / halfScreenWidth),
			(-1 * (_ScreenPoint.y - halfScreenHeight) / halfScreenHeight), -1, 1.0);
		glm::vec4 nearResult = inverseMV * near;
		nearResult /= nearResult.w;
		return nearResult;
	}

	void Window::SetCursorMode(CursorMode _Mode)
	{
		m_CursorMode = _Mode;
		glfwSetInputMode(m_Window, GLFW_CURSOR, CursorModeValue(m_CursorMode));
	}

	void Window::SetProperties()
    {
        //OpenGL version 3.3
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, g_OpenGLMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, g_OpenGLMinorVersion);
        //Disables deprecated code
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //Enables new code
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
    }

	void Window::StartLoop()
	{
		OnRenderReady.Invoke({});

		while (!glfwWindowShouldClose(m_Window))
		{
			//Input events
			glfwPollEvents();

			glClearColor(m_Color.r, m_Color.g, m_Color.b, m_Color.a);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			Time::CalculateDeltaTime(CurrentTime());

			//DRAW STUFF
			OnRenderFrame.Invoke({});

			glfwSwapBuffers(m_Window);
		}
	}

	float Window::CurrentTime() const
	{
		return static_cast<float>(glfwGetTime());
	}
}