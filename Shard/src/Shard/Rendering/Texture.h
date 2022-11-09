#pragma once

namespace Shard::Rendering
{
	class Texture
	{
	public:
		Texture();
		Texture(const std::string& path);
		Texture(const unsigned char* rawData);
		~Texture();

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;	
		 
	private:
		unsigned int m_TextureID;
		unsigned char* m_LocalBuffer;
		std::string m_FilePath;
		int m_Width, m_Height, m_BitsPerPixel;
	};
}

