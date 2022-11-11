#pragma once
#include "Renderer.h"

namespace Shard::Rendering
{
    enum class SpriteMode { Simple, Multiple };
    
    class Sprite
    {
    public:
        SpriteMode mode;
        bool useTexture;
        BlendingMode blendingMode;
        float uvMultiplier = 1;
        int currentSubMesh = 0;
        
        Sprite(const std::string& texturePath = "", const std::shared_ptr<Shader>& shader = Renderer::GetDefaultShader());
        void Draw(const Math::MvpData& mvp, const Math::Color& color);
        
        void AddTexture(const std::string& texturePath);
        void SetMultipleLayout(const Math::Vector2& subTexSize, const Math::Vector2& subTexAmount);
        
    private:
        std::string m_mesh;
        std::shared_ptr<Shader> m_shader;
        std::string m_texturePath;
        
        Math::Vector2 m_subTexSize;
        Math::Vector2 m_subTexAmount;
        std::vector<std::string> m_meshAtlas;

        QuadLayout CreateSpriteMesh(const Math::Vector2& pixelSize, const std::array<Math::Vector2, 4>& uv);
        
        friend class Renderer;
    };

    
}
