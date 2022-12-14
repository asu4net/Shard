#pragma once

struct GLFWwindow;

namespace Shard
{
	class Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool GetKeyPressed(int keycode);
		static bool GetMouseButtonPressed(int button);
		static Vector2 GetMousePosition();

	private:
		static GLFWwindow* m_Window;
	};
}