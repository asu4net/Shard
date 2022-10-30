#pragma once
#include <memory>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include <common.hpp>
#include <gtx/quaternion.hpp>
#include "Rendering/Renderer.h"

namespace Shard::Rendering::Primitives
{
    struct Shape
    {
        glm::vec4 color = { 1, 0, 0, 1 };

		glm::mat4 transform = glm::mat4(1);
		glm::mat4 projection;
		glm::mat4 view;

		void Draw()
		{
			projection = glm::mat4(1);
			view = glm::mat4(1);

			glm::vec2 size = glm::vec2(2.f, 1.5f) * 2.f;
			projection = glm::ortho(-size.x, size.x, -size.y, size.y, .1f, 100.f);

			glm::vec3 cameraPos = { 0, 0, -6.f };
			glm::vec3 forward = glm::vec3(0, 0, 1.f);
			glm::vec3 up = glm::vec3(0, 1.f, 0);
			
			view = glm::lookAt(cameraPos, cameraPos + forward, up);
			Render();
		}

		virtual void Render() = 0;
    };
	
	struct Quad : public Shape
	{
		virtual void Render() override
		{
			Renderer::DrawQuad(transform, view, projection, color);
		}
	};

	struct Circle : public Shape
	{
		float thickness = 1.f;
		float fade = 0.005f;

		virtual void Render() override
		{
			Renderer::DrawCircle(transform, view, projection, color, thickness, fade);
		}
	};
}