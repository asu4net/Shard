#include "shpch.h"
#include "Texture.h"
#include "stb_image.h"
#include <GLEW/glew.h>

namespace Shard
{
	Texture::Texture()
		: m_textureId(0)
		, m_localBuffer(nullptr)
		, m_width(0)
		, m_height(0)
		, m_bitsPerPixel(0)
	{}

	Texture::Texture(std::string path)
		: m_textureId(0)
		, m_localBuffer(nullptr)
		, m_filePath(std::move(path))
		, m_width(0)
		, m_height(0)
		, m_bitsPerPixel(0)
	{
		//Flip texture vertically because OpenGL
		//stbi_set_flip_vertically_on_load(1);
		m_localBuffer = stbi_load(m_filePath.c_str(), &m_width, &m_height, &m_bitsPerPixel, 4);

		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer);
	
		if (0 == m_bitsPerPixel || 4 < m_bitsPerPixel) { printf("Texture error: invalid depth\n"); }

		glBindTexture(GL_TEXTURE_2D, 0);

		if (m_localBuffer)
			stbi_image_free(m_localBuffer);
	}

	Texture::Texture(const unsigned char* rawData)
		: m_textureId(0)
			, m_localBuffer(nullptr)
			, m_width(1024)
			, m_height(1024)
			, m_bitsPerPixel(0)
	{
		glGenTextures(1, &m_textureId);
		glBindTexture(GL_TEXTURE_2D, m_textureId);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rawData);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &m_textureId);
	}

	std::array<Vector2, 4> Texture::GetSubTexUvCoords(const Vector2& pos, const Vector2& size) const
	{
		const float width = static_cast<float>(m_width);
		const float height = static_cast<float>(m_height);
		
		const std::array<Vector2, 4> uvCoords = {
			Vector2{(pos.x * size.x) / width, ((pos.y + 1) * size.y) / height},
			Vector2{((pos.x + 1) * size.x) / width, ((pos.y + 1) * size.y) / height},
			Vector2{((pos.x + 1) * size.x) / width, (pos.y * size.y) / height},
			Vector2{(pos.x * size.x) / width, (pos.y * size.y) / height}
		};
		
		return uvCoords;
	}

	void Texture::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, m_textureId);
	}

	void Texture::Unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}
