#include "shpch.h"
#include "Shader.h"
#include <GLEW/glew.h>
#include "ShaderStrings.h"

namespace Shard
{
    const int Shader::GetUniform(const char* name) const { return glGetUniformLocation(shaderID, name); }

	std::string Shader::ReadFile(const char* fileLocation)
	{
		std::string content;
		std::ifstream fileStream(fileLocation, std::ios::in);

		if (!fileStream.is_open())
		{
			printf("Failed to read %s! File doesn't exist.", fileLocation);
			return "";
		}

		std::string line = "";
		while (!fileStream.eof())
		{
			std::getline(fileStream, line);
			content.append(line + "\n");
		}

		fileStream.close();
		return content;
	}
	bool Shader::Compile(int shaderID, const char* shaderCode, int shaderType, int theShader)
	{
		const char* theCode[1];
		theCode[0] = shaderCode;

		GLint codeLength[1];
		codeLength[0] = strlen(shaderCode);

		glShaderSource(theShader, 1, theCode, codeLength);
		glCompileShader(theShader);

		int result = 0;
		char eLog[1024] = { 0 };
		glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

		if (!result)
		{
			glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
			printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
			return false;
		}

		glAttachShader(shaderID, theShader);
		return true;
	}
	void Shader::LinkAndValidate(const char* vertexCode, const char* fragmentCode)
	{
		shaderID = glCreateProgram();

		if (!shaderID)
		{
			printf("Error creating shader program!");
			return;
		}

		int vertex = glCreateShader(GL_VERTEX_SHADER);

		if (!Compile(shaderID, vertexCode, GL_VERTEX_SHADER, vertex))
		{
			printf("Error compiling vertex shader!");
			return;
		}

		int fragment = glCreateShader(GL_FRAGMENT_SHADER);

		if (!Compile(shaderID, fragmentCode, GL_FRAGMENT_SHADER, fragment))
		{
			printf("Error compiling fragment shader!");
			return;
		}

		int result = 0;
		char eLog[1024] = { 0 };

		glLinkProgram(shaderID);
		glGetProgramiv(shaderID, GL_LINK_STATUS, &result);

		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
			printf("Error linking program '%s'\n", eLog);
			return;
		}

		glValidateProgram(shaderID);
		glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);

		if (!result)
		{
			glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
			printf("Error validating program '%s'\n", eLog);
			return;
		}

		glDetachShader(shaderID, vertex);
		glDetachShader(shaderID, fragment);

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}
	void Shader::Create(const char* vertexLocation, const char* fragmentLocation)
	{
		std::string vertexString = ReadFile(vertexLocation);
		std::string fragmentString = ReadFile(fragmentLocation);
		LinkAndValidate(vertexString.c_str(), fragmentString.c_str());
	}
	Shader::Shader(const char* vertexLocation, const char* fragmentLocation)
		: shaderID(0), modelLocation(0), viewLocation(0), projectionLocation(0)
	{
		Create(vertexLocation, fragmentLocation);
	}
	Shader::Shader()
		: shaderID(0), modelLocation(0), viewLocation(0), projectionLocation(0)
	{
		Create(DEFAULT_VERTEX_PATH, DEFAULT_FRAGMENT_PATH);
	}
	Shader::~Shader()
	{
		Clear();
	}
	void Shader::SetUniformFloat(const char* name, float value)
	{
		int location = GetUniform(name);
		glUniform1f(location, value);
	}
	void Shader::SetUniformInt(const char* name, int value)
	{
		int location = GetUniform(name);
		glUniform1i(location, value);

	}
	void Shader::SetUniformMat4(const char* name, glm::mat4 value)
	{
		int location = GetUniform(name);
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	}
	
	void Shader::SetUniformVec4(const char* name, glm::vec4 value)
	{
		int location = GetUniform(name);
		glUniform4fv(location, 1, glm::value_ptr(value));
	}
	
	void Shader::SetUniformVec3(const char* name, Vector3 value)
	{
		int location = GetUniform(name);
		glUniform3fv(location, 1, glm::value_ptr(value.ToGlm()));
	}
	void Shader::Bind()
	{
		glUseProgram(shaderID);
	}
	void Shader::Unbind()
	{
		glUseProgram(0);
	}
	void Shader::Clear()
	{
		if (shaderID == 0) return;
		glDeleteProgram(shaderID);
		shaderID = 0;
		modelLocation = 0;
		viewLocation = 0;
		projectionLocation = 0;
	}
}