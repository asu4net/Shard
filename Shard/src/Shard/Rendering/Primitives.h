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
		inline static Vector3 forward = {0, 0, -1.f};
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
	
	//Char declaration
	struct Text;
	struct Char : Shape
	{
		Char(const std::string& mesh, Text* text, Char* prevChar);
		void SetPosition();
	private:
		std::string m_mesh;
		Text* m_text = nullptr;
		Char* m_prevChar = nullptr;
		
		void Render() override;
	};

	struct Text : Shape
	{
		float spacing = .7f;
		
		Text(Font* font = nullptr, const std::string& content = "", const Color& textColor = Color::White)
			: Shape(textColor, Vector3::zero, IdentityQuat, Vector3::one)
			, m_font(font)
		{
			//SetContent(content);
		}
		
		void SetContent(const std::string& content)
		{
			if (content.empty()) return;
			const auto charMeshes = m_font->StringToQuads(content);
			
			m_chars.clear();
			for (auto& mesh: charMeshes)
			{
				Char* theChar = new Char(mesh, this, prevChar);
				m_chars.push_back(theChar);
				prevChar = theChar;
			}
			m_content = content;
		}

		~Text() override
		{
			for (int i = 0; i < m_chars.size(); i++)
				delete m_chars[i];
			m_chars.clear();
		}

		const Font& GetFont() const { return *m_font; }
		
		void Render() override
		{
			for (auto* theChar : m_chars)
			{
				theChar->SetPosition();
				theChar->Draw();
			}
		}
		
	private:
		Font* m_font = nullptr;
		std::string m_content;
		std::vector<Char*> m_chars;
		Char* prevChar = nullptr;
	};

	//Char definition
	inline Char::Char(const std::string& mesh, Text* text, Char* prevChar)
			: m_mesh(mesh)
			, m_text(text)
			, m_prevChar(prevChar)
	{}

	inline void Char::SetPosition()
	{
		const Vector3 prevPos = m_prevChar ? m_prevChar->position : m_text->position;
		position = prevPos + Vector2::right * m_text->spacing;
	}
	
	inline void Char::Render()
	{
		Renderer::DrawQuad(m_mesh, mvp, Renderer::GetDefaultShader(), m_text->color, true, m_text->GetFont().GetTextureAtlasPath());
	}

}