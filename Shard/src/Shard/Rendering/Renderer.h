#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace Shard::Rendering
{
	struct QuadLayout
	{
		std::array<Math::Vector2, 4> size;
		std::array<Math::Vector2, 4> uv;
	};
	
	class Window;
	class Renderer
	{
		static std::shared_ptr<Shader> defaultShader;
		static std::shared_ptr<Shader> circleShader;
		
	public:
		static void Init();
		static std::shared_ptr<Shader> GetDefaultShader() { return defaultShader; }
		
		static void AddTexture(const std::string& texturePath);
		static void AddTexture(const std::string& texturePath, const unsigned char* texturePixels);
		static const Texture& GetTexture(const std::string& texturePath) { return m_textures[texturePath]; }
		
		static std::string AddQuad(const QuadLayout& layout);
		static std::string GenerateQuadKey(const QuadLayout& layout);
		static std::string GetDefaultQuad() { return m_defaultQuadKey; }
		
		static void DrawQuad(const std::string& meshKey,
			const Math::MvpData& matrices,
			const std::shared_ptr<Shader>& shader = defaultShader,
			const Math::Color& color = Math::Color::White,
			const bool useTexture = false,
			const std::string& texturePath = "",
			const float uvMultiplier = 1.f);

		static void DrawCircle(const Math::MvpData& matrices,
			const Math::Color& color = Math::Color::White,
			const float thickness = 1.f,
			const float fade = .005f);

	private:
		static bool m_initialized;
		static std::unordered_map<std::string, Texture> m_textures;
		static std::unordered_map<std::string, Mesh> m_quadMeshes;
		static std::string m_defaultQuadKey;
	};
}
