#pragma once
#include "Core.h"
#include "Math/Vector2.h"
#include "KeyCodes.h"
#include "glm.hpp"

struct GLFWwindow;

namespace Shard
{
	class SHARD_API Input
	{
	public:
		static void Init(GLFWwindow* window);
		static bool GetKeyPressed(int keycode);
		static bool GetMouseButtonPressed(int button);
		static glm::vec2 GetMousePosition();

	private:
		static GLFWwindow* m_Window;
	};
}