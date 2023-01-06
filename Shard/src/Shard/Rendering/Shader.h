#pragma once

namespace Shard
{
	class Shader
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
		
		void SetUniformInt(const char* name, int value);
		void SetUniformFloat(const char* name, float value);
		void SetUniformMat4(const char* name, glm::mat4 value);
		void SetUniformVec2(const char* name, Vector2 value);
		void SetUniformVec4(const char* name, glm::vec4 value);
		void SetUniformVec3(const char* name, Vector3 value);

		void Bind();
		void Unbind();
		void Clear();
	};
}



