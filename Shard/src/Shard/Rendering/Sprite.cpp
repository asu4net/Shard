#include "shpch.h"
#include "Sprite.h"

using namespace Shard::Math;

namespace Shard::Rendering
{
    Sprite::Sprite(const std::string& texturePath, const std::shared_ptr<Shader>& shader)
        : mode(SpriteMode::Simple)
        , m_shader(shader)
        , m_texturePath(texturePath)
    {
        useTexture = !m_texturePath.empty();
        if (!useTexture)
        {
            m_mesh = Renderer::GetDefaultQuad();
            return;
        }
        AddTexture(m_texturePath);
    }
    
    void Sprite::Draw(const Math::MvpData& mvp, const Math::Color& color)
    {
        if (mode == SpriteMode::Simple)
        {
            Renderer::DrawQuad(m_mesh, mvp, m_shader, color, useTexture, m_texturePath, uvMultiplier, blendingMode);
            return;
        }

        //If multiple mode...
        if (currentSubMesh < 0 || currentSubMesh >= m_meshAtlas.size())
            currentSubMesh = 0;
        Renderer::DrawQuad(m_meshAtlas[currentSubMesh], mvp, m_shader, color, useTexture, m_texturePath, uvMultiplier);
    }

    void Sprite::AddTexture(const std::string& texturePath)
    {
        PushTexture(texturePath);
    }

    void Sprite::AddTexture(const unsigned char* texturePixels)
    {
        std::ostringstream ss;
        ss << texturePixels;
        const std::string path = ss.str();
        PushTexture(path, texturePixels);
    }

    void Sprite::SetMultipleLayout(const Vector2& subTexSize, const Vector2& subTexAmount)
    {
        if (!m_meshAtlas.empty()) return;
        mode = SpriteMode::Multiple;
        m_subTexSize = subTexSize;
        m_subTexAmount = subTexAmount;

        const int iCount = static_cast<int>(m_subTexAmount.x);
        const int jCount = static_cast<int>(m_subTexAmount.y);

        const Texture& texture = Renderer::GetTexture(m_texturePath);
			
        for (int i = 0; i < iCount; i++)
        {
            for (int j = 0; i < jCount; i++)
            {
                const Vector2 pos{static_cast<float>(i), static_cast<float>(j)};
                const std::array<Vector2, 4> uv = texture.GetSubTexUvCoords(pos, subTexSize);
                std::string quad = Renderer::AddQuad(CreateSpriteMesh(subTexSize, uv));
                m_meshAtlas.push_back(quad);
            }
        }
    }

    QuadLayout Sprite::CreateSpriteMesh(const Vector2& pixelSize, const std::array<Vector2, 4>& uv)
    {
        QuadLayout l;

        const Vector2 s = pixelSize.Normalized() / 2;
        
        l.size[0] = {-s.x, -s.y}; l.uv[0] = {uv[0].x, uv[0].y};
        l.size[1] = { s.x, -s.y}; l.uv[1] = {uv[1].x, uv[1].y};
        l.size[2] = { s.x, s.y}; l.uv[2] = {uv[2].x, uv[2].y};
        l.size[3] = {-s.x, s.y}; l.uv[3] = {uv[3].x, uv[3].y};
        return l;
    }

    void Sprite::PushTexture(const std::string& texturePath, const unsigned char* texturePixels)
    {
        useTexture = true;
        m_texturePath = texturePath;

        if (texturePixels) Renderer::AddTexture(m_texturePath, texturePixels);
        else  Renderer::AddTexture(m_texturePath);
        
        //Default uv layout
        const std::array<Vector2, 4> uv = {
            Vector2{0.0f, 1.0f},
            Vector2{1.0f, 1.0f},
            Vector2{1.0f, 0.0f},
            Vector2{0.0f, 0.0f}
        };
        
        const Texture& tex = Renderer::GetTexture(m_texturePath);
        float w = static_cast<float>(tex.Width());
        float h = static_cast<float>(tex.Height());
        m_mesh = Renderer::AddQuad(CreateSpriteMesh({w, h}, uv));
    }
}
