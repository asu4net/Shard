#pragma once

//TODO: Add texture mode multiple and spriteSheets layouts (an array of pixel size for each sprite)

namespace Shard
{
	class Texture
	{
	public:
		
		
		Texture();
		Texture(std::string path);
		Texture(const unsigned char* rawData);
		~Texture();

		std::array<Vector2, 4> GetSubTexUvCoords(const Vector2& pos, const Vector2& size) const;
		
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;	
		 
	private:
		unsigned int m_textureId;
		unsigned char* m_localBuffer;
		std::string m_filePath;
		int m_width, m_height, m_bitsPerPixel;
	public:
		[[nodiscard]] int Width() const
		{
			return m_width;
		}

		[[nodiscard]] int Height() const
		{
			return m_height;
		}
	};
}

