#include "shpch.h"
#include "Texture.h"
#include "stb_image.h"
#include <GLEW/glew.h>

namespace Shard::Rendering
{
	Texture::Texture()
		: m_TextureID(0)
		, m_LocalBuffer(nullptr)
		, m_FilePath("")
		, m_Width(0)
		, m_Height(0)
		, m_BitsPerPixel(0)
	{}

	Texture::Texture(const std::string& path)
		: m_TextureID(0)
		, m_LocalBuffer(nullptr)
		, m_FilePath(path)
		, m_Width(0)
		, m_Height(0)
		, m_BitsPerPixel(0)
	{
		//Flip texture vertically because OpenGL
		//stbi_set_flip_vertically_on_load(1);
		m_LocalBuffer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BitsPerPixel, 4);

		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	
		if (0 == m_BitsPerPixel || 4 < m_BitsPerPixel) { printf("Texture error: invalid depth\n"); }

		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_LocalBuffer)
			stbi_image_free(m_LocalBuffer);
	}

	Texture::Texture(const unsigned char* rawData)
		: m_TextureID(0)
			, m_LocalBuffer(nullptr)
			, m_Width(1024)
			, m_Height(1024)
			, m_BitsPerPixel(0)
	{
		glGenTextures(1, &m_TextureID);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawData);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_TextureID);
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_TextureID);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
