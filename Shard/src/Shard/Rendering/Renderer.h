#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace Shard::Rendering
{
	class Window;
	class Renderer
	{
		static bool m_initialized;
		static std::unordered_map<std::string, Texture> textures;
		static std::shared_ptr<Mesh> quadMesh;
		static std::shared_ptr<Shader> defaultShader;
		static std::shared_ptr<Shader> circleShader;
		
	public:
		static void Init();
		static std::shared_ptr<Shader> GetDefaultShader() { return defaultShader; }
		
		static void AddTexture(const std::string& texturePath);
		static void AddTexture(const std::string& texturePath, const unsigned char* texturePixels);

		static void DrawMesh(const std::shared_ptr<Mesh>& mesh,
			const Math::MvpData& matrices,
			const std::shared_ptr<Shader>& shader = defaultShader,
			const Math::Color& color = Math::Color::White,
			const bool useTexture = false,
			const std::string& texturePath = "",
			const float uvMultiplier = 1.f);
		
		static void DrawQuad(const Math::MvpData& matrices,
			const Math::Color& color = Math::Color::White,
			const bool useTexture = false,
			const std::string& texturePath = "",
			const float uvMultiplier = 1.f);

		static void DrawCircle(const Math::MvpData& matrices,
			const Math::Color& color = Math::Color::White,
			const float thickness = 1.f,
			const float fade = .005f);
	};
}
