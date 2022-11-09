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
        std::string m_content;
        std::map<char, Mesh> m_charMeshes;

        void CreateCharMesh(const char c);
        void SetContent(const std::string& content);
        
    };
}
