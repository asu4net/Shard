#include "Renderer.h"

namespace Shard::Rendering
{
    std::shared_ptr<Mesh> Renderer::quad;
    std::shared_ptr<Shader> Renderer::defaultShader;
    std::shared_ptr<Shader> Renderer::circleShader;

    void Renderer::Init()
    {
        defaultShader = std::make_shared<Shader>();
        circleShader = std::make_shared<Shader>(CIRCLE_VERTEX_PATH, CIRCLE_FRAGMENT_PATH);

        //Quad data...
        float vertices[] = {
            // x	 y	   u	 v
            -0.5f, -0.5f, 1.0f, 0.0f, // 0
             0.5f, -0.5f, 0.0f, 0.0f, // 1
             0.5f,  0.5f, 0.0f, 1.0f, // 2
            -0.5f,	0.5f, 1.0f, 1.0f, // 3 
        };

        unsigned int indices[] = {
            0, 1, 2, //triangle 1
            2, 3, 0  //triangle 2
        };

        quad = std::make_shared<Mesh>(MESH_2D, true, vertices, indices, 16, 6);
    }

    void Renderer::DrawQuad(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Math::Color color)
    {
        defaultShader->Bind();

        defaultShader->SetUnfiformMat4(UNIFORM_MODEL_MATRIX_NAME, model);
        defaultShader->SetUnfiformMat4(UNIFORM_PROJECTION_MATRIX_NAME, projection);
        defaultShader->SetUnfiformMat4(UNIFORM_VIEW_MATRIX_NAME, view);

        defaultShader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());

        quad->m_vertexArray->Bind();
        quad->m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, quad->m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        quad->m_indexBuffer->Unbind();
        quad->m_vertexArray->Unbind();

        defaultShader->Unbind();
    }

    void Renderer::DrawCircle(glm::mat4 model, glm::mat4 view, glm::mat4 projection, Math::Color color, float thickness, float fade)
    {
        circleShader->Bind();

        circleShader->SetUnfiformMat4(UNIFORM_MODEL_MATRIX_NAME, model);
        circleShader->SetUnfiformMat4(UNIFORM_PROJECTION_MATRIX_NAME, projection);
        circleShader->SetUnfiformMat4(UNIFORM_VIEW_MATRIX_NAME, view);

        circleShader->SetUniformVec4(UNIFORM_DEFAULT_COLOR_NAME, color.ToGlm());
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_THICKNESS_NAME, thickness);
        circleShader->SetUniformFloat(UNIFORM_CIRCLE_FADE_NAME, fade);

        quad->m_vertexArray->Bind();
        quad->m_indexBuffer->Bind();
        glDrawElements(GL_TRIANGLES, quad->m_indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        quad->m_indexBuffer->Unbind();
        quad->m_vertexArray->Unbind();

        circleShader->Unbind();
    }

    
    

}