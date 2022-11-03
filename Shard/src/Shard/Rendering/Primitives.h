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
		Vector3 position;
		Vector3 scale = {1, 1, 1};
		Vector3 rotation;

        Color color = { 1, 0, 0, 1 };

		glm::mat4 transform = glm::mat4(1);
		glm::mat4 projection = glm::mat4(1);
		glm::mat4 view = glm::mat4(1);

		Window* window = nullptr;
    	
		Shape() = default;

		Shape(Color _Color)
			: color(_Color)
		{}

		void Draw()
		{
			projection = glm::mat4(1);
			view = glm::mat4(1);

			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, position.ToGlm());
			model = glm::scale(model, scale.ToGlm());
			transform = model;

			float size = 5.f;
			
			projection = glm::ortho(-window->GetAspect() * size, window->GetAspect() * size, -1.0f * size, 1.0f * size, -100.f, 100.f);

			Vector3 cameraPos = { 0, 0, -6.f };
			Vector3 forward = { 0, 0, 1.f };
			Vector3 up = { 0, 1.f, 0 };
			
			view = glm::lookAt(cameraPos.ToGlm(), (cameraPos + forward).ToGlm(), up.ToGlm());
			Render();
		}

		virtual void Render() = 0;
    };
	
	struct Quad : public Shape
	{
	private:
		bool m_useTex = false;
	
	public:
		std::string texturePath;
		
		using Shape::Shape;

		Quad(Color _color, std::string _texturePath = "")
			: Shape(_color)
			, texturePath(_texturePath)
			, m_useTex(false)
		{
			m_useTex = !texturePath.empty();
			if (!m_useTex) return;
			Renderer::AddTexture(texturePath);
		}

		void AddTexture(std::string texturePath)
		{
			m_useTex = true;
			Renderer::AddTexture(texturePath);
		}

		virtual void Render() override
		{
			Renderer::DrawQuad(transform, view, projection, color, m_useTex, texturePath);
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