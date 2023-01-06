#pragma once
#include "Renderer.h"

namespace Shard
{
    enum class SpriteMode { Simple, Multiple };
    
    class Sprite
    {
    public:
        SpriteMode mode;
        bool useTexture;
        BlendingMode blendingMode;
        Vector2 uvMultiplier = Vector2::one;
        int currentSubMesh = 0;
        
        Sprite(const std::string& texturePath = "", const std::shared_ptr<Shader>& shader = Renderer::GetDefaultShader());
        void Draw(const MvpData& mvp, const Color& color);

        int Count() const { return static_cast<int>(m_subTexAmount.x) * static_cast<int>(m_subTexAmount.y); }
        void Next();
        void AddTexture(const std::string& texturePath);
        void AddTexture(const unsigned char* texturePixels);
        void SetMultipleLayout(const Vector2& subTexSize, const Vector2& subTexAmount);
        
    private:
        std::string m_mesh;
        std::shared_ptr<Shader> m_shader;
        std::string m_texturePath;
        
        Vector2 m_subTexSize;
        Vector2 m_subTexAmount;
        std::vector<std::string> m_meshAtlas;

        QuadLayout CreateSpriteMesh(const Vector2& pixelSize, const std::array<Vector2, 4>& uv);
        void PushTexture(const std::string& texturePath, const unsigned char* texturePixels = nullptr);
        
        friend class Renderer;
    };

    
}
