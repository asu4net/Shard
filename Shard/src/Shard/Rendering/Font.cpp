#include "shpch.h"
#include "Font.h"
#include "Renderer.h"
#include "stb_truetype.h"

namespace Shard::Rendering
{
    constexpr int Font::DefaultHeight = 1024;
    constexpr int Font::DefaultWidth = 1024;
    constexpr int Font::DefaultPixelHeight = 64;
    constexpr int Font::DefaultCharCount = 256;
    
    Font::Font(const std::string& fileLocation)
        : height(DefaultHeight)
        , width(DefaultWidth)
        , pixelHeight(DefaultPixelHeight)
        , charCount(DefaultCharCount)
        , pixelsRgb(nullptr)
        , bakedChar(nullptr)
    {
        std::ifstream fileStream(fileLocation, std::ifstream::binary);

        if (!fileStream) return;
        fileStream.seekg(0, fileStream.end);
        int length = fileStream.tellg();
        fileStream.seekg(0, fileStream.beg);
        char* buffer = new char[length]; 
        fileStream.read(buffer, length);
        fileStream.close();
        const int pixelsLenght = height * width;
        auto* pixels = new unsigned char[pixelsLenght];
        auto* bakedCharPtr = new stbtt_bakedchar[256];
        
        stbtt_BakeFontBitmap(reinterpret_cast<const unsigned char*>(buffer), 0, pixelHeight, pixels,
            width, height, 0, charCount, bakedCharPtr);
        
         const int pixelsRgbLenght = pixelsLenght * 4;
         pixelsRgb = new unsigned char[pixelsRgbLenght];
        
         int currIndex = 0;
         int pixelsIndex = 0;
         for (int i = 0; i < pixelsRgbLenght; i++)
         {
             currIndex++;
             if (currIndex == 4)
             {
                 pixelsRgb[i] = pixels[pixelsIndex];
                 pixelsIndex++;
                 currIndex = 0;
                 continue;
             }
             
             pixelsRgb[i] = 255;
         }

        Renderer::AddTexture(m_textureAtlasPath, pixelsRgb);
        
        // delete[] data;
        // delete[] pixelsRgb;
        // delete[] pixels;
        // delete[] buffer;
    }

    Math::CharUv Font::GetUvOfChar(const char c)
    {
        if (!bakedChar) return{};

        const auto* bakedCharPtr = static_cast<stbtt_bakedchar*>(bakedChar);
        
        float xPos{0}, yPos{0};
        auto* q = new stbtt_aligned_quad();
        stbtt_GetBakedQuad(bakedCharPtr, width, height, c, &xPos, &yPos, q, true);
        const Math::CharUv uv{xPos, yPos, q->s0, q->s1, q->t0, q->t1, q->x0, q->x1, q->y0, q->y1};
        delete q;
        return uv;
    }
}
