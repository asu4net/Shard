#include "shpch.h"
#include "Renderer.h"
#include "ShaderStrings.h"

namespace Shard::Rendering
{
    bool Renderer::m_initialized = false;
    std::map<const std::string, Texture> Renderer::textures;
    std::shared_ptr<Mesh> Renderer::quadMesh;
    std::shared_ptr<Shader> Renderer::defaultShader;
    std::shared_ptr<Shader> Renderer::circleShader;

    void Renderer::Init()
    {
        defaultShader = std::make_shared<Shader>();
        circleShader = std::make_shared<Shader>(CIRCLE_VERTEX_PATH, CIRCLE_FRAGMENT_PATH);
        
        //Quad data...
        float vertices[] = {
            // x	 y	   u	 v
            -0.5, -0.5, 1.0f, 1.0f, // 0
             0.5, -0.5, 0.0f, 1.0f, // 1
             0.5,  0.5, 0.0f, 0.0f, // 2
            -0.5,  0.5, 1.0f, 0.0f, // 3 
        };

        unsigned int indices[] = {
            0, 1, 2, //triangle 1
            2, 3, 0  //triangle 2
        };

        quadMesh = std::make_shared<Mesh>(MESH_2D, true, vertices, indices, 16, 6);
        m_initialized = true;
    }

    void Renderer::AddTexture(const std::string& texturePath)
    {
        if (!m_initialized) return;
        
        if (textures.find(texturePath) != textures.end())
            return;

        textures.emplace(texturePath, texturePath);
    }

    void Renderer::AddTexture(const std::string& texturePath, const unsigned char* texturePixels)
    {
        if (!m_initialized) return;
        
        if (textures.find(texturePath) != textures.end())
            return;

        textures.emplace(texturePath, texturePixels);
    }

    void Renderer::DrawMesh(const std::shared_ptr<Mesh>& mesh, const Math::MvpData& matrices,
        const std::shared_ptr<Shader>& shader, const Math::Color& color, const bool useTexture,
        const std::string& texturePath, const float uvMultiplier)
    {
        if (!m_initialized) return;

        shader->Bind();
        shader->SetUniformFloat(UNIFORM_USE_TEXTURE_NAME, useTexture);
        shader->SetUniformInt(UNIFORM_TEXTURE_NAME, 0);

        if (useTexture)
        {
            glEnable(GL_BLEND);
            shader->SetUniformFloat(UNIFORM_UV_MULTIPLIER, uvMultiplier);
            shader->SetUniformInt(UNIFORM_TEXTURE_NAME, 0);
            textures[texturePath].Bind();
        }

        shader->SetUniformMat4(UNIFORM_MODEL_MATRIX_NAME, matrices.model);
        shader->SetUniformMat4(UNIFORM_PROJECTION_MATRIX_NAME, matrices.projection);
        shader->SetUniformMat4(UNIFORM_VIEW_MATRIX_NAME, matrices.view);

        shader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());

        mesh->m_vertexArray->Bind();
        mesh->m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, mesh->m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        mesh->m_indexBuffer->Unbind();
        mesh->m_vertexArray->Unbind();

        if (useTexture)
        {
            textures[texturePath].Unbind();
            glDisable(GL_BLEND);
        }
        
        shader->Unbind();
    }

    void Renderer::DrawQuad(const Math::MvpData& matrices, const Math::Color& color, const bool useTexture,
                            const std::string& texturePath, const float uvMultiplier)
    {
        if (!m_initialized) return;
        DrawMesh(quadMesh, matrices, defaultShader, color, useTexture, texturePath, uvMultiplier);
    }
    
    void Renderer::DrawCircle(const Math::MvpData& matrices, const Math::Color& color, const float thickness, const float fade)
    {
        if (!m_initialized) return;
        circleShader->Bind();

        circleShader->SetUniformMat4(UNIFORM_MODEL_MATRIX_NAME, matrices.model);
        circleShader->SetUniformMat4(UNIFORM_PROJECTION_MATRIX_NAME, matrices.projection);
        circleShader->SetUniformMat4(UNIFORM_VIEW_MATRIX_NAME, matrices.view);

        circleShader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_THICKNESS_NAME, thickness);
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_FADE_NAME, fade);

        circleShader->Unbind();
        
        DrawMesh(quadMesh, matrices, circleShader, color);
    }
}
