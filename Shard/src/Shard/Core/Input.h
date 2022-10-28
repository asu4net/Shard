#pragma once
#include "Math/Vector2.h"
#include "KeyCodes.h"

struct GLFWwindow;

namespace Shard
{
	class Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool GetKeyPressed(int keycode);
		static bool GetMouseButtonPressed(int button);
		static Math::Vector2 GetMousePosition();

	private:
		static GLFWwindow* m_Window;
	};
}