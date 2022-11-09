#pragma once
#include "Mesh.h"

namespace Shard::Rendering
{
    class Font;
    
    class Text
    {
    public:
        Text(Font* font);
        
    private:
        Font* m_font;
        std::map<char, Mesh> m_charMeshes;

        void CreateCharMesh(const char c);
    };
}
