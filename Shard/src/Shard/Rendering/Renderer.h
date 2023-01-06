#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Lines.h"

namespace Shard
{
	struct QuadLayout
	{
		std::array<Vector2, 4> size;
		std::array<Vector2, 4> uv;
	};

	enum class BlendingMode
	{
		Solid,
		Alpha,
		Add,
		Multiply
	};
	
	class Window;
	class Renderer
	{
		static std::shared_ptr<Shader> defaultShader;
		static std::shared_ptr<Shader> circleShader;
		
	public:
		static void Init();
		static std::shared_ptr<Shader> GetDefaultShader() { return defaultShader; }

		static void SetBlendMode(const BlendingMode mode);
		
		static void AddTexture(const std::string& texturePath);
		static void AddTexture(const std::string& texturePath, const unsigned char* texturePixels);
		static const Texture& GetTexture(const std::string& texturePath) { return m_textures[texturePath]; }

		static std::string AddLineGroup(const std::vector<Line>& lines);
		static std::string GenerateLinesKey(const std::vector<Line>& lines);
		static std::string GetDefaultLineBox2D() { return m_defaultLineBox2D; }

		static std::string AddQuad(const QuadLayout& layout);
		static std::string GenerateQuadKey(const QuadLayout& layout);
		static std::string GetDefaultQuad() { return m_defaultQuadKey; }
		
		static void DrawQuad(const std::string& meshKey,
			const MvpData& matrices,
			const std::shared_ptr<Shader>& shader = defaultShader,
			const Color& color = Color::White,
			const bool useTexture = false,
			const std::string& texturePath = "",
			const Vector2& uvMultiplier = Vector2::one,
			const BlendingMode blendingMode = BlendingMode::Alpha);

		static void DrawCircle(const MvpData& matrices,
			const Color& color = Color::White,
			const float thickness = 1.f,
			const float fade = .005f);

		static void DrawLines(const std::string& linesKey,
			const MvpData& matrices,
			const Color& color = Color::White);

	private:
		static bool m_initialized;
		static std::unordered_map<std::string, Texture> m_textures;
		static std::unordered_map<std::string, Mesh> m_quadMeshes;
		static std::unordered_map<std::string, Lines> m_lines;
		static std::string m_defaultQuadKey;
		static std::string m_defaultLineBox2D;
		static BlendingMode m_blendingMode;
	};
}
