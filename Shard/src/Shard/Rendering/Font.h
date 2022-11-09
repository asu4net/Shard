#pragma once

#include "Math/SimpleStructs.h"

namespace Shard::Rendering
{
    class Font
    {
    public:
        static const int DefaultHeight;
        static const int DefaultWidth;
        static const int DefaultPixelHeight;
        static const int DefaultCharCount;
        
        int height;
        int width;
        int pixelHeight;
        int charCount;

        unsigned char* pixelsRgb;
        void* bakedChar;
        Font(const std::string& fileLocation);
        Math::CharUv GetUvOfChar(const char c);
        const std::string& GetTextureAtlasPath() const { return m_textureAtlasPath; }

    private:
        std::string m_textureAtlasPath;
    };
}
