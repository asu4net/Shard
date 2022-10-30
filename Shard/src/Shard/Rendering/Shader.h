#pragma once
#include "Core.h"
#include "glm.hpp"
#include <string>

namespace Shard::Rendering
{
	class SHARD_API Shader
	{
		int shaderID, modelLocation, projectionLocation, viewLocation;

		std::string ReadFile(const char* fileLocation);
		bool Compile(int shaderID, const char* shaderCode, int shaderType, int theShader);
		void LinkAndValidate(const char* vertexCode, const char* fragmentCode);
		void Create(const char* vertexLocation, const char* fragmentLocation);

	public:
		Shader(const char* vertexLocation, const char* fragmentLocation);
		Shader();
		~Shader();

		const int GetUniform(const char* name) const;

		void SetUniformFloat(const char* name, float value);
		
		void SetUnfiformMat4(const char* name, glm::mat4 value);
		void SetUniformVec4(const char* name, glm::vec4 value);
		void SetUniformVec3(const char* name, glm::vec3 value);

		void Bind();
		void Unbind();
		void Clear();
	};
}



