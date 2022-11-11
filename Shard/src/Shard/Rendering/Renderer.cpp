#include "shpch.h"
#include "Renderer.h"
#include "ShaderStrings.h"

namespace Shard::Rendering
{
    std::shared_ptr<Shader> Renderer::defaultShader;
    std::shared_ptr<Shader> Renderer::circleShader;
    
    bool Renderer::m_initialized = false;
    std::unordered_map<std::string, Texture> Renderer::m_textures;
    std::unordered_map<std::string, Mesh> Renderer::m_quadMeshes;
    std::string Renderer::m_defaultQuadKey;
    BlendingMode Renderer::m_blendingMode = BlendingMode::Alpha;
    
    void Renderer::Init()
    {
        if (m_initialized) return;
        m_initialized = true;

        //Default quad generation
        const std::function genDefaultQuad = []
        {
            QuadLayout l;
            l.size[0] = {-0.5, -0.5}; l.uv[0] = {1.0f, 1.0f};
            l.size[1] = { 0.5, -0.5}; l.uv[1] = {0.0f, 1.0f};
            l.size[2] = { 0.5,  0.5}; l.uv[2] = {0.0f, 0.0f};
            l.size[3] = {-0.5,  0.5}; l.uv[3] = {1.0f, 0.0f};
            return l;
        };
        
        m_defaultQuadKey = AddQuad(genDefaultQuad());
        defaultShader = std::make_shared<Shader>();
        circleShader = std::make_shared<Shader>(CIRCLE_VERTEX_PATH, CIRCLE_FRAGMENT_PATH);
    }

    void Renderer::SetBlendMode(const BlendingMode mode)
    {
        m_blendingMode = mode;
        switch (mode) {
        case BlendingMode::Solid:
            glBlendFunc(GL_ONE, GL_ZERO);
            break;
        case BlendingMode::Alpha:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        case BlendingMode::Add:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE);
            break;
        case BlendingMode::Multiply:
            glBlendFunc(GL_DST_COLOR, GL_ZERO);
            break;
        }
    }

    void Renderer::AddTexture(const std::string& texturePath)
    {
        if (!m_initialized) return;
        
        if (m_textures.find(texturePath) != m_textures.end())
            return;

        m_textures.emplace(texturePath, texturePath);
    }

    void Renderer::AddTexture(const std::string& texturePath, const unsigned char* texturePixels)
    {
        if (!m_initialized) return;
        
        if (m_textures.find(texturePath) != m_textures.end())
            return;

        m_textures.emplace(texturePath, texturePixels);
    }
    
    std::string Renderer::AddQuad(const QuadLayout& layout)
    {
        if (!m_initialized) return "";
        
        std::string key = GenerateQuadKey(layout);
        if (m_quadMeshes.find(key) != m_quadMeshes.end())
            return key;

        const auto& size = layout.size;
        const auto& uv = layout.uv;
        
        //Apply layout...
        float vertices[] = {
            size[0].x, size[0].y, uv[0].x, uv[0].y, // 0
            size[1].x, size[1].y, uv[1].x, uv[1].y, // 1
            size[2].x, size[2].y, uv[2].x, uv[2].y, // 2
            size[3].x, size[3].y, uv[3].x, uv[3].y, // 3 
        };
        
        unsigned int indices[] = {
            0, 1, 2, //triangle 1
            2, 3, 0  //triangle 2
        };

        m_quadMeshes.try_emplace(key, MESH_2D, true, vertices, indices, 16, 6);
        return key;
    }

    std::string Renderer::GenerateQuadKey(const QuadLayout& layout)
    {
        std::stringstream ss;

        const std::function fn = [&ss](const std::array<Math::Vector2, 4>& vectors)
        {
            for (const auto& v : vectors) { ss << v.x; ss << v.y; }
        };

        fn(layout.size);
        fn(layout.uv);

        return ss.str();
    }

    void Renderer::DrawQuad(const std::string& meshKey, const Math::MvpData& matrices,
                            const std::shared_ptr<Shader>& shader, const Math::Color& color, const bool useTexture,
                            const std::string& texturePath, const float uvMultiplier, const BlendingMode blendingMode)
    {
        if (!m_initialized) return;
        
        const Mesh& mesh = m_quadMeshes[meshKey];
        
        shader->Bind();
        shader->SetUniformFloat(UNIFORM_USE_TEXTURE_NAME, useTexture);
        shader->SetUniformInt(UNIFORM_TEXTURE_NAME, 0);

        if (useTexture)
        {
            glEnable(GL_BLEND);
            SetBlendMode(blendingMode);
            shader->SetUniformFloat(UNIFORM_UV_MULTIPLIER, uvMultiplier);
            shader->SetUniformInt(UNIFORM_TEXTURE_NAME, 0);
            m_textures[texturePath].Bind();
        }

        shader->SetUniformMat4(UNIFORM_MODEL_MATRIX_NAME, matrices.model);
        shader->SetUniformMat4(UNIFORM_PROJECTION_MATRIX_NAME, matrices.projection);
        shader->SetUniformMat4(UNIFORM_VIEW_MATRIX_NAME, matrices.view);

        shader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());

        mesh.m_vertexArray->Bind();
        mesh.m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, mesh.m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        mesh.m_indexBuffer->Unbind();
        mesh.m_vertexArray->Unbind();

        if (useTexture)
        {
            m_textures[texturePath].Unbind();
            glDisable(GL_BLEND);
        }
        
        shader->Unbind();
        SetBlendMode(BlendingMode::Alpha);
    }
    
    void Renderer::DrawCircle(const Math::MvpData& matrices, const Math::Color& color, const float thickness, const float fade)
    {
        if (!m_initialized) return;
        circleShader->Bind();

        circleShader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_THICKNESS_NAME, thickness);
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_FADE_NAME, fade);

        circleShader->Unbind();
        
        DrawQuad(m_defaultQuadKey, matrices, circleShader, color);
    }
}