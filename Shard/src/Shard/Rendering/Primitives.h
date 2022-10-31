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
	using namespace Math;

    struct Shape
    {
        Color color = { 1, 0, 0, 1 };

		glm::mat4 transform = glm::mat4(1);
		glm::mat4 projection = glm::mat4(1);;
		glm::mat4 view = glm::mat4(1);;

		Shape() = default;

		Shape(Color _Color)
			: color(_Color)
		{}

		void Draw()
		{
			projection = glm::mat4(1);
			view = glm::mat4(1);

			Vector2 size = Vector2(2.f, 1.5f) * 4.f;
			projection = glm::ortho(-size.x, size.x, -size.y, size.y, .1f, 100.f);

			Vector3 cameraPos = { 0, 0, -6.f };
			Vector3 forward = Vector3(0, 0, 1.f);
			Vector3 up = Vector3(0, 1.f, 0);
			
			view = glm::lookAt(cameraPos.ToGlm(), (cameraPos + forward).ToGlm(), up.ToGlm());
			Render();
		}

		void Translate(const Vector3& _Position)
		{
			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, _Position.ToGlm());
			transform = model;
		}

		virtual void Render() = 0;
    };
	
	struct Quad : public Shape
	{
		using Shape::Shape;

		virtual void Render() override
		{
			Renderer::DrawQuad(transform, view, projection, color);
		}
	};

	struct Circle : public Shape
	{
		float thickness = 1.f;
		float fade = 0.005f;

		Circle() = default;

		Circle(Color _Color)
			: Shape(_Color) 
		{}

		Circle(Color _Color, float _Thickness, float _Fade)
			: Shape(_Color)
			, thickness(_Thickness)
			, fade(_Fade) 
		{}

		virtual void Render() override
		{
			Renderer::DrawCircle(transform, view, projection, color, thickness, fade);
		}
	};
}