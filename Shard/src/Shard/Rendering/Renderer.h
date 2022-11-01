#pragma once
#include "Core.h"
#include <memory>
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "ShaderStrings.h"
#include "Mesh.h"
#include "Math/Color.h"
#include <string>
#include <map>
#include "Texture.h"

namespace Shard::Rendering
{
	class SHARD_API Renderer
	{
		static std::map<const std::string, Texture> textures;
		static std::shared_ptr<Mesh> quad;
		static std::shared_ptr<Shader> defaultShader;
		static std::shared_ptr<Shader> circleShader;

	public:
		static void Init();
		
		static void AddTexture(const std::string& texturePath);

		static void DrawQuad(glm::mat4 model,
							 glm::mat4 view,
							 glm::mat4 projection,
			                 Math::Color color,
							 bool useTexture = false,
							 const std::string& texturePath = "");

		static void DrawCircle(glm::mat4 model,
			                   glm::mat4 view,
			                   glm::mat4 projection,
							   Math::Color color,
							   float thickness,
							   float fade);
	};
}