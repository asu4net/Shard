#include "shpch.h"
#include "Input.h"
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace Shard
{
	GLFWwindow* Input::m_Window = nullptr;

	void Input::Init(GLFWwindow* window)
	{
		m_Window = window;
	}

	bool Input::GetKeyPressed(int keycode)
	{
		int state = glfwGetKey(m_Window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
		return false;
	}

	bool Input::GetMouseButtonPressed(int button)
	{
		int state = glfwGetMouseButton(m_Window, button);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
		return false;
	}

	Vector2 Input::GetMousePosition()
	{
		double x, y;
		glfwGetCursorPos(m_Window, &x, &y);
		return { (float)x, (float)y };
	}
}
