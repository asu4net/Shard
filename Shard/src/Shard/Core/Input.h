#pragma once
#include "Core.h"
#include "Math/Math.h"
#include "KeyCodes.h"

struct GLFWwindow;

namespace Shard
{
	class SHARD_API Input
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