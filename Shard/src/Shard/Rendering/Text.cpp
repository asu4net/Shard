#include "shpch.h"
#include "Text.h"
#include "Font.h"

namespace Shard::Rendering
{
    Text::Text(Font* font)
        : m_font(font) {}

    void Text::CreateCharMesh(const char c)
    {
        // if (!m_font) return;
        // const Math::CharUv uv = m_font->GetUvOfChar(c);
        //
        // //Quad data...
        // float vertices[] = {
        //     // x	 y	   u	 v
        //     -0.5, -0.5, uv.s0, uv.s1, // 0
        //      0.5, -0.5, uv.t0, uv.t1, // 1
        //      0.5,  0.5, uv.x0, uv.x1, // 2
        //     -0.5,  0.5, uv.y0, uv.y1 // 3 
        // };
        //
        // unsigned int indices[] = {
        //     0, 1, 2, //triangle 1
        //     2, 3, 0  //triangle 2
        // };
        //
        // m_charMeshes.try_emplace(c, MESH_2D, true, vertices, indices, 16, 6);
    }

    void Text::SetContent(const std::string& content)
    {
        for (size_t i = 0; i < content.size(); i++)
        {
            
        }
        m_content = content;
    }
}
