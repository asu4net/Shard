#pragma once
#include "Rendering/Mesh.h"
#include "Math/SimpleStructs.h"

namespace Shard::Rendering
{
    constexpr int CharCount = 256;
    
    class Font
    {
    public:
        Font(const std::string& fileLocation, const int pixelHeight = 64, const int height = 1024, const int width = 1024);
        ~Font();
        
        Font(const Font& other) = delete;
        Font(Font&& other) = delete;
        Font& operator=(Font other) = delete;
        Font& operator=(Font&& other) = delete;

        void SetPixelHeight(const int newHeight) { Construct(newHeight, m_height, m_width); }
        
        const std::string& GetTextureAtlasPath() const { return m_textureAtlasPath; }
        const unsigned char* GetPixelsRgb() const { return m_pixelsRgb; }
        std::vector<std::shared_ptr<Mesh>> StringToMeshes(const std::string& string);
    
    private:
        int m_height = 0;
        int m_width = 0;
        int m_pixelHeight = 0;
        std::string m_fileLocation;
        std::string m_textureAtlasPath;
        std::map<char, std::shared_ptr<Mesh>> m_charMeshes;
        unsigned char* m_pixelsRgb = nullptr;
        unsigned char* m_pixelsAlpha = nullptr;
        void* m_bakedChar = nullptr; 

        void Construct(const int pixelHeight, int width, int height);
        bool GetFontBuffer(const std::string& ttfFileLoc, const unsigned char*& outBuffer);
        void BakeFontBuffer(const unsigned char* buffer);
        void ClearBuffers();
        
        Math::CharUv GetUvOfChar(const char c);
        std::shared_ptr<Mesh> CreateCharMesh(const char c);
    };
}
