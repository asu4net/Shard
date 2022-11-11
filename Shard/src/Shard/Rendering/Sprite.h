#pragma once
#include "Mesh.h"
#include "Texture.h"

namespace Shard::Rendering
{
    class Sprite
    {
    private:
        explicit Sprite(std::string texturePath, std::shared_ptr<Shader> shader);
        
        std::string m_texturePath;
        std::shared_ptr<Shader> m_shader;
        std::shared_ptr<Mesh> m_defaultMesh;
        std::vector<std::shared_ptr<Mesh>> m_meshAtlas;  
        
        friend class Renderer;
    };

    
}
