#pragma once
#include "Rendering/Renderer.h"
#include "Rendering/Font.h"
#include "Rendering/Sprite.h"

namespace Shard::Rendering::Primitives
{
	using namespace Math;

	struct StaticCamera
	{
		inline static Window* window = nullptr;
		inline static float size = 3.f;
		inline static glm::mat4 projection = glm::mat4(1);
		inline static glm::mat4 view = glm::mat4(1);

		inline static Vector3 position = {0, 0, 0};
		inline static Vector3 forward = {0, 0, 1.f};
		inline static Vector3 up = {0, 1.f, 0};

		static void CalculateMatrices()
		{
			if (!window) return;
			projection = glm::mat4(1);
			view = glm::mat4(1);
			projection = glm::ortho(-window->Aspect() * size, window->Aspect() * size, -1.0f * size, 1.0f * size, -100.f, 100.f);
			view = glm::lookAt(position.ToGlm(), (position + forward).ToGlm(), up.ToGlm());
		}
	};
	
	struct Shape
	{
		Vector3 position = Vector3::zero;
		Vector3 scale = Vector3::one;
		glm::quat rotation = IdentityQuat;
		Color color = Color::White;
		glm::mat4 transform = glm::mat4(1);
		MvpData mvp;
		
		Shape(const Color& color = Color::White,
			const Vector3& position = Vector3::zero, const glm::quat& rotation = IdentityQuat, const Vector3& scale = Vector3::one)
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
			mvp = { transform, StaticCamera::view, StaticCamera::projection };
			
			Render();
		}

		virtual void Render() = 0;
	};
	
	struct Quad : Shape
	{
		Quad(const Color& theColor,
			const Vector3& thePosition = Vector3::zero,
			const glm::quat& theRotation = IdentityQuat,
			const Vector3& theScale = Vector3::one)
			:Shape(theColor, thePosition, theRotation, theScale)
		{
			m_sprite = Sprite("");
		}
		
		Quad(const std::string& texturePath = "", const BlendingMode mode = BlendingMode::Alpha,
			const float uvMultiplier = 1, const Color& theColor = Color::White,
			const Vector3& thePosition = Vector3::zero, const glm::quat& theRotation = IdentityQuat, const Vector3& theScale = Vector3::one)
		
			: Shape(theColor, thePosition, theRotation, theScale)
			, m_texturePath(texturePath)
		{
			m_sprite = Sprite(texturePath);
			m_sprite.blendingMode = mode;
			m_sprite.uvMultiplier = uvMultiplier;
		}

		Sprite& GetSprite() { return m_sprite; }

		void SpriteSheetLayout(const Vector2& subTexSize, const Vector2& subTexAmount)
		{
			m_sprite.SetMultipleLayout(subTexSize, subTexAmount);
		}
		
		void AddTexture(const unsigned char* texturePixels)
		{
			m_sprite.AddTexture(texturePixels);
		}
		void AddTexture(const std::string& path)
		{
			m_sprite.AddTexture(path);
		}
		void Render() override
		{
			m_sprite.Draw(mvp, color);
		}

	private:
		std::string m_texturePath;
		Sprite m_sprite;
	};

	struct Circle : Shape
	{
		float thickness = 1.f;
		float fade = 0.005f;

		Circle(const Color& theColor,
			const Vector3& thePosition = Vector3::zero,
			const glm::quat& theRotation = IdentityQuat,
			const Vector3& theScale = Vector3::one)
			:Shape(theColor, thePosition, theRotation, theScale)
		{}
		
		Circle(const float thickness = 1.f, const float fade = 0.005f, const Color& theColor = Color::White,
			const Vector3& thePosition = Vector3::zero, const glm::quat& theRotation = IdentityQuat, const Vector3& theScale = Vector3::one)
		
			: Shape(theColor, thePosition, theRotation, theScale)
			, thickness(thickness)
			, fade(fade) 
		{}

		void Render() override
		{
			Renderer::DrawCircle(mvp, color, thickness, fade);
		}
	};

	struct Text : Shape
	{
		Text(Font* font = nullptr, const std::string& content = "", const Color& textColor = Color::White)
			: Shape(textColor, Vector3::zero, IdentityQuat, Vector3::one)
			, m_font(font)
		{
			SetContent(content);
		}
		void SetContent(const std::string& content)
		{
			if (content.empty()) return;
			m_quads = m_font->StringToQuads(content);
			m_content = content;
		}
		void Render() override
		{
			for (size_t i = 0; i < m_quads.size(); i++)
			{
				Renderer::DrawQuad(m_quads[0], mvp, Renderer::GetDefaultShader(), color, true, m_font->GetTextureAtlasPath());
			}
		}
		
	private:
		Font* m_font = nullptr;
		std::string m_content;
		std::vector<std::string> m_quads;
	};
}