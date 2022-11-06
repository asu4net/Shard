#pragma once
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

namespace Shard::Rendering
{
	class Window;
	class Renderer
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
							 const std::string& texturePath = "",
							 float uvMultiplier = 1);

		static void DrawCircle(glm::mat4 model,
			                   glm::mat4 view,
			                   glm::mat4 projection,
							   Math::Color color,
							   float thickness,
							   float fade);
	};
}
