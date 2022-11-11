#pragma once
#include "Rendering/Renderer.h"
#include "Rendering/Font.h"

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
	
	struct Quad : Shape
	{
		BlendingMode blendingMode = BlendingMode::Alpha;
		float uvMultiplier = 1;
		int currentSubMesh = 0;

		Quad(const Color& theColor,
			const Vector3& thePosition = Vector3::zero,
			const glm::quat& theRotation = IdentityQuat,
			const Vector3& theScale = Vector3::one)
			:Shape(theColor, thePosition, theRotation, theScale)
		{}
		
		Quad(const std::string& texturePath = "", const BlendingMode mode = BlendingMode::Alpha,
			const float uvMultiplier = 1, const Color& theColor = Color::White,
			const Vector3& thePosition = Vector3::zero, const glm::quat& theRotation = IdentityQuat, const Vector3& theScale = Vector3::one)
		
			: Shape(theColor, thePosition, theRotation, theScale)
			, blendingMode(mode)
			, uvMultiplier(uvMultiplier)
			, m_texturePath(texturePath)
		{
			m_useTex = !texturePath.empty();
			if (!m_useTex) return;
			AddTexture(texturePath);
		}

		void SpriteSheetLayout(const Vector2& subTexSize, const Vector2& subTexAmount)
		{
			if (!m_subMeshes.empty()) return;
			
			m_subTexSize = subTexSize;
			m_subTexAmount = subTexAmount;

			const int iCount = static_cast<int>(m_subTexAmount.x);
			const int jCount = static_cast<int>(m_subTexAmount.y);

			const Texture& texture = Renderer::GetTexture(m_texturePath);
			
			for (int i = 0; i < iCount; i++)
			{
				for (int j = 0; i < jCount; i++)
				{
					const Vector2 pos{static_cast<float>(i), static_cast<float>(j)};
					const std::vector<Vector2> uv = texture.GetSubTexUvCoords(pos, subTexSize);
					
					//Quad data...
					float vertices[] = {
						// x	 y	   u	 v
						-0.5, -0.5, uv[0].x, uv[0].y, // 0
						 0.5, -0.5, uv[1].x, uv[1].y, // 1
						 0.5,  0.5, uv[2].x, uv[2].y, // 2
						-0.5,  0.5, uv[3].x, uv[3].y, // 3 
					};
					
					unsigned int indices[] = {
						0, 1, 2, //triangle 1
						2, 3, 0  //triangle 2
					};

					m_subMeshes.emplace_back(std::make_shared<Mesh>(MESH_2D, true, vertices, indices, 16, 6));
				}
			}
		}
		
		void AddTexture(const unsigned char* texturePixels)
		{
			std::ostringstream ss;
			ss << texturePixels;
			const std::string path = ss.str();

			m_useTex = true;
			m_texturePath = path;
			
			Renderer::AddTexture(m_texturePath, texturePixels);
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

			if (m_subTexAmount == Vector2::zero)
			{
				Renderer::DrawQuad(mvp, color, m_useTex, m_texturePath, uvMultiplier);
				return;
			}

			if (currentSubMesh < 0 || currentSubMesh >= m_subMeshes.size())
				currentSubMesh = 0;
			Renderer::DrawMesh(m_subMeshes[currentSubMesh], mvp, Renderer::GetDefaultShader(), color, m_useTex, m_texturePath, uvMultiplier);
		}

	private:
		bool m_useTex = false;
		std::string m_texturePath;
		Vector2 m_subTexSize;
		Vector2 m_subTexAmount;
		std::vector<std::shared_ptr<Mesh>> m_subMeshes;
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
			m_meshes = m_font->StringToMeshes(content);
			m_content = content;
		}
		void Render() override
		{
			for (size_t i = 0; i < m_meshes.size(); i++)
			{
				Renderer::DrawMesh(m_meshes[0], mvp, Renderer::GetDefaultShader(), color, true, m_font->GetTextureAtlasPath());
			}
		}
		
	private:
		Font* m_font = nullptr;
		std::string m_content;
		std::vector<std::shared_ptr<Mesh>> m_meshes;
	};
}