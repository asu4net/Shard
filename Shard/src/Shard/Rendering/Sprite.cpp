#include "shpch.h"
#include "Sprite.h"
#include "Renderer.h"

namespace Shard::Rendering
{
    Sprite::Sprite(std::string texturePath, std::shared_ptr<Shader> shader)
        : m_texturePath(std::move(texturePath))
        , m_shader(std::move(shader))
    {
        Renderer::AddTexture(texturePath);
        
    }
    
}
