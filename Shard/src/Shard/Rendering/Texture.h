#pragma once

//TODO: Add texture mode multiple and spriteSheets layouts (an array of pixel size for each sprite)

namespace Shard::Rendering
{
	class Texture
	{
	public:
		
		
		Texture();
		Texture(std::string path);
		Texture(const unsigned char* rawData);
		~Texture();

		std::vector<Math::Vector2> GetSubTexUvCoords(const Math::Vector2& pos, const Math::Vector2& size) const;
		
		void Bind(unsigned int slot = 0) const;
		void Unbind() const;	
		 
	private:
		unsigned int m_textureId;
		unsigned char* m_localBuffer;
		std::string m_filePath;
		int m_width, m_height, m_bitsPerPixel;
	};
}

