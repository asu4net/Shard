#include "shpch.h"
#include "Font.h"
#include "Renderer.h"
#include "stb_truetype.h"

namespace Shard::Rendering
{
    Font::Font(const Window* window, const std::string& fileLocation, const int pixelHeight, const int height, const int width)
        : m_window(window)
        , m_height(height)
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

    //TODO: Tiene pinta de que esta función se va a comer toda la performance xd
    std::vector<std::string> Font::StringToQuads(const std::string& string)
    {
        std::vector<std::string> meshes;
        for (const char& c : string)
        {
            if (!m_charQuads.empty() && m_charQuads.find(c) != m_charQuads.end())
            {
                meshes.push_back(m_charQuads[c]);
                continue;
            }

            meshes.push_back(CreateCharQuad(c));
        }
        return meshes;
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
        m_charQuads.clear();
        
        delete[] m_pixelsAlpha;
        const auto* bakedCharPtr = static_cast<stbtt_bakedchar*>(m_bakedChar);
        delete[] bakedCharPtr;
        delete[] m_pixelsRgb;

        m_pixelsAlpha = nullptr;
        m_bakedChar = nullptr;
        m_pixelsRgb = nullptr;
    }

    Math::UvCoords Font::GetUvOfChar(const char c)
    {
        if (!m_bakedChar) return{};

        const auto* bakedCharPtr = static_cast<stbtt_bakedchar*>(m_bakedChar);
        
        float xPos{0}, yPos{0};
        auto* q = new stbtt_aligned_quad();
        stbtt_GetBakedQuad(bakedCharPtr, m_width, m_height, c, &xPos, &yPos, q, true);
        const Math::UvCoords uv{xPos, yPos, q->s0, q->s1, q->t0, q->t1, q->x0, q->x1, q->y0, q->y1};
        delete q;
        return uv;
    }

    std::string Font::CreateCharQuad(const char c)
    {
        const Math::UvCoords uv = GetUvOfChar(c);

        Math::Vector2 s;
        s.x = (uv.s1 - uv.s0);
        s.y = (uv.t1 - uv.t0);
        //s = s.Normalized() / 2;
        s = s * 7;
        QuadLayout l;
        l.size[0] = {-s.x, -s.y}; l.uv[0] = {uv.s1, uv.t1};
        l.size[1] = { s.x, -s.y}; l.uv[1] = {uv.s0, uv.t1};
        l.size[2] = { s.x,  s.y}; l.uv[2] = {uv.s0, uv.t0};
        l.size[3] = {-s.x,  s.y}; l.uv[3] = {uv.s1, uv.t0};

        std::string quad = Renderer::AddQuad(l);
        m_charQuads.emplace(c, quad);
        return quad;
    }
}
