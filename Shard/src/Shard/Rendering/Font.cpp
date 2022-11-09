#include "shpch.h"
#include "Font.h"
#include "Renderer.h"
#include "stb_truetype.h"

namespace Shard::Rendering
{
    Font::Font(const std::string& fileLocation, const int pixelHeight, const int height, const int width)
        : m_height(height)
        , m_width(width)
        , m_pixelHeight(pixelHeight)
        , m_fileLocation(fileLocation)
    {
        Construct(m_pixelHeight, m_width, m_height);
    }

    Font::~Font()
    {
        ClearBuffers();
    }

    void Font::Construct(const int pixelHeight, int width, int height)
    {
        ClearBuffers();
        const unsigned char* fontBuffer = nullptr;
        if (!GetFontBuffer(m_fileLocation, fontBuffer)) return;
        BakeFontBuffer(fontBuffer);
        delete[] fontBuffer;

        //TODO: Remove old texture
        Renderer::AddTexture(m_textureAtlasPath, m_pixelsRgb);
    }

    bool Font::GetFontBuffer(const std::string& ttfFileLoc, const unsigned char*& outBuffer)
    {
        std::ifstream fileStream(ttfFileLoc, std::ifstream::binary);

        if (!fileStream) return false;
        fileStream.seekg(0, std::ifstream::end);
        const std::streamoff length = fileStream.tellg();
        fileStream.seekg(0, std::ifstream::beg);
        char* buffer = new char[length]; 
        fileStream.read(buffer, length);
        fileStream.close();
        outBuffer = reinterpret_cast<unsigned char*>(buffer);
        return true;
    }

    void Font::BakeFontBuffer(const unsigned char* buffer)
    {
        const int pixelsAlphaLenght = m_height * m_width;
        m_pixelsAlpha = new unsigned char[pixelsAlphaLenght];
        auto* bakedChar = new stbtt_bakedchar[CharCount];

        stbtt_BakeFontBitmap(buffer, 0, static_cast<float>(m_pixelHeight), m_pixelsAlpha,
                             m_width, m_height, 0, CharCount, bakedChar);
        m_bakedChar = reinterpret_cast<void*>(bakedChar);
        
        const int pixelsRgbLenght = pixelsAlphaLenght * 4;
        m_pixelsRgb = new unsigned char[pixelsRgbLenght];

        int currIndex = 0;
        int pixelsIndex = 0;
        for (int i = 0; i < pixelsRgbLenght; i++)
        {
            currIndex++;
            if (currIndex == 4)
            {
                m_pixelsRgb[i] = m_pixelsAlpha[pixelsIndex];
                pixelsIndex++;
                currIndex = 0;
                continue;
            }

            m_pixelsRgb[i] = 255;
        }
    }

    void Font::ClearBuffers()
    {
        delete[] m_pixelsAlpha;
        const auto* bakedCharPtr = static_cast<stbtt_bakedchar*>(m_bakedChar);
        delete[] bakedCharPtr;
        delete[] m_pixelsRgb;

        m_pixelsAlpha = nullptr;
        m_bakedChar = nullptr;
        m_pixelsRgb = nullptr;
    }

    Math::CharUv Font::GetUvOfChar(const char c)
    {
        if (!m_bakedChar) return{};

        const auto* bakedCharPtr = static_cast<stbtt_bakedchar*>(m_bakedChar);
        
        float xPos{0}, yPos{0};
        auto* q = new stbtt_aligned_quad();
        stbtt_GetBakedQuad(bakedCharPtr, m_width, m_height, c, &xPos, &yPos, q, true);
        const Math::CharUv uv{xPos, yPos, q->s0, q->s1, q->t0, q->t1, q->x0, q->x1, q->y0, q->y1};
        delete q;
        return uv;
    }

    void Font::CreateCharMesh(const char c)
    {
        const Math::CharUv uv = GetUvOfChar(c);

        //Quad data...
        float vertices[] = {
            // x	 y	   u	 v
            -0.5, -0.5, uv.s0, uv.s1, // 0
             0.5, -0.5, uv.t0, uv.t1, // 1
             0.5,  0.5, uv.x0, uv.x1, // 2
            -0.5,  0.5, uv.y0, uv.y1 // 3 
        };

        unsigned int indices[] = {
            0, 1, 2, //triangle 1
            2, 3, 0  //triangle 2
        };

        m_charMeshes.try_emplace(c, MESH_2D, true, vertices, indices, 16, 6);
    }
}
