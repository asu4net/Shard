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

	struct StaticCamera
	{
		inline static Window* window = nullptr;
		inline static float size = 3.f;
		inline static glm::mat4 projection = glm::mat4(1);
		inline static glm::mat4 view = glm::mat4(1);

		inline static Vector3 position = { 0, 0, 0.f };
		inline static Vector3 forward = { 0, 0, 1.f };
		inline static Vector3 up = { 0, 1.f, 0 };

		static void CalculateMatrices()
		{
			if (!window) return;
			projection = glm::mat4(1);
			view = glm::mat4(1);
			projection = glm::ortho(-window->GetAspect() * size, window->GetAspect() * size, -1.0f * size, 1.0f * size, -100.f, 100.f);
			view = glm::lookAt(position.ToGlm(), (position + forward).ToGlm(), up.ToGlm());
		}
	};

	enum class BlendingMode
	{
		Solid,
		Alpha,
		Add,
		Multiply
	};

	inline void SetBlendMode(const BlendingMode mode)
	{
		switch (mode) {
		case BlendingMode::Solid:
			glBlendFunc(GL_ONE, GL_ZERO);
			break;
		case BlendingMode::Alpha:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;
		case BlendingMode::Add:
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;
		case BlendingMode::Multiply:
			glBlendFunc(GL_DST_COLOR, GL_ZERO);
			break;
		}
	}

	struct Shape
	{
		Vector3 position;
		Vector3 scale = {1, 1, 1};
		Vector3 rotation;

		Color color = { 1, 0, 0, 1 };

		glm::mat4 transform = glm::mat4(1);
    	
		Shape() = default;

		Shape(Color _Color)
			: color(_Color)
		{}

		void Draw()
		{
			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, position.ToGlm());
			model = glm::scale(model, scale.ToGlm());
			transform = model;
			
			Render();
		}

		virtual void Render() = 0;
	};
	
	struct Quad : Shape
	{
		BlendingMode mode = BlendingMode::Alpha;
		float uvMultiplier = 1;
		
	private:
		bool m_useTex = false;
	
	public:
		std::string texturePath;
		
		using Shape::Shape;

		Quad(Color _color = Color::White, std::string _texturePath = "")
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
			SetBlendMode(mode);
			Renderer::DrawQuad(transform, StaticCamera::view, StaticCamera::projection, color, m_useTex, texturePath, uvMultiplier);
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
			Renderer::DrawCircle(transform, StaticCamera::view, StaticCamera::projection, color, thickness, fade);
		}
	};
}