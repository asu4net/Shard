#include "shpch.h"
#include "TextSystem.h"
#include "Rendering/Renderer.h"
#include "Components.h"

namespace Shard::Ecs
{
    using namespace Rendering;
        
    void TextSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<TextRenderer, Transform>();

        for (const entt::entity entity : view)
        {
            const auto& [text, transform] = view.get<TextRenderer, Transform>(entity);
            if (!text.enabled) return;
            RenderText(text, transform, GetCamera());
        }
    }

    void TextSystem::OnComponentAdded(ComponentArgs args)
    {
        Entity entity = GetEntityByHandler(args.entityHandler);

        if (entity.Has<TextRenderer>())
        {
            TextRenderer& textRenderer = entity.Get<TextRenderer>();
            TextSystem::SetText(textRenderer, textRenderer.Text());
        }
    }

    void TextSystem::SetText(TextRenderer& textRenderer, const std::string& newText)
    {
        textRenderer.m_charMeshes.clear();
        textRenderer.m_charMeshes = textRenderer.font->StringToQuads(newText);
    }
    
    void TextSystem::RenderText(const TextRenderer& textRenderer, const Transform& transform, const Camera& mainCamera)
    {
        glm::mat4 charMatrix = transform.Model();
        
        for (const std::string& charMesh : textRenderer.m_charMeshes)
        {
            Math::MvpData mvp{charMatrix, mainCamera.View(), mainCamera.Projection()};
            
            Renderer::DrawQuad(charMesh, mvp, Renderer::GetDefaultShader(),
                textRenderer.color, true, textRenderer.font->GetTextureAtlasPath());

            glm::vec3 newPosition = glm::vec3(charMatrix[3]) + glm::vec3(textRenderer.spacing, 0, 0);
            charMatrix = glm::translate(glm::mat4(1), newPosition);
        }
    }
}
