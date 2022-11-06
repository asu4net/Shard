#pragma once
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
			projection = glm::ortho(-window->Aspect() * size, window->Aspect() * size, -1.0f * size, 1.0f * size, -100.f, 100.f);
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
		inline static const Color DefaultColor = {1, 1, 1, 1};
		inline static const Vector3 DefaultPosition = {0, 0, 0};
		inline static const glm::quat DefaultRotation = {1, 0, 0, 0};
		inline static const Vector3 DefaultScale = {1, 1, 1};
		
		Vector3 position = DefaultPosition;
		Vector3 scale = DefaultScale;
		glm::quat rotation = DefaultRotation;
		
		Color color = DefaultColor;
		glm::mat4 transform = glm::mat4(1);
    	
		Shape() = default;

		explicit Shape(const Color& color = DefaultColor,
			const Vector3& position = DefaultPosition, const glm::quat& rotation = DefaultRotation, const Vector3& scale = DefaultScale)
			: position(position)
			, scale(scale)
			, rotation(rotation)
			, color(color)
		{}
		virtual ~Shape() = default;

		void Draw()
		{
			glm::mat4 model = glm::mat4(1);
			model = glm::translate(model, position.ToGlm());
			model *= glm::toMat4(rotation);
			model = glm::scale(model, scale.ToGlm());
			transform = model;
			
			Render();
		}

		virtual void Render() = 0;
	};
	
	struct Quad : Shape
	{
		static constexpr BlendingMode DefaultBlendingMode = BlendingMode::Alpha;
		static constexpr float DefaultUvMultiplier = 1;
		
		BlendingMode blendingMode = DefaultBlendingMode;
		float uvMultiplier = DefaultUvMultiplier;
		
		using Shape::Shape;

		explicit Quad(const std::string& texturePath = "", const BlendingMode mode = DefaultBlendingMode,
			const float uvMultiplier = DefaultUvMultiplier, const Color& theColor = DefaultColor,
			const Vector3& thePosition = DefaultPosition, const glm::quat& theRotation = DefaultRotation, const Vector3& theScale = DefaultScale)
		
			: Shape(theColor, thePosition, theRotation, theScale)
			, blendingMode(mode)
			, uvMultiplier(uvMultiplier)
			, m_texturePath(texturePath)
		{
			m_useTex = !texturePath.empty();
			if (!m_useTex) return;
			AddTexture(texturePath);
		}

		void AddTexture(const std::string& path)
		{
			m_useTex = true;
			m_texturePath = path;
			Renderer::AddTexture(m_texturePath);
		}

		void Render() override
		{
			SetBlendMode(blendingMode);
			Renderer::DrawQuad(transform, StaticCamera::view, StaticCamera::projection, color, m_useTex, m_texturePath, uvMultiplier);
		}

	private:
		bool m_useTex = false;
		std::string m_texturePath;
	};

	struct Circle : Shape
	{
		constexpr static float DefaultFade = 0.005f;
		constexpr static float DefaultThickness = 1.f;
		
		float thickness = DefaultThickness;
		float fade = DefaultFade;

		Circle() = default;
		using Shape::Shape;

		explicit Circle(const float thickness = DefaultThickness, const float fade = DefaultFade, const Color& theColor = DefaultColor,
			const Vector3& thePosition = DefaultPosition, const glm::quat& theRotation = DefaultRotation, const Vector3& theScale = DefaultScale)
		
			: Shape(theColor, thePosition, theRotation, theScale)
			, thickness(thickness)
			, fade(fade) 
		{}

		void Render() override
		{
			Renderer::DrawCircle(transform, StaticCamera::view, StaticCamera::projection, color, thickness, fade);
		}
	};
}