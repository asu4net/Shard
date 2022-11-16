#include "shpch.h"
#include "SpriteSystem.h"
#include "Components.h"

namespace Shard::Ecs
{
    void SpriteSystem::DrawSprites(entt::registry& registry)
    {
        const auto view = registry.view<SpriteRenderer, Transform>();

        const Camera& mainCamera = registry.get<Camera>(CameraSystem::MainCameraEntityHandler());
        
        for (const entt::entity entity : view)
        {
            const auto& [spriteRenderer, transform] = view.get<SpriteRenderer, Transform>(entity);
            Math::MvpData mvp{transform.Model(), mainCamera.View(), mainCamera.Projection()};
            spriteRenderer.sprite->Draw(mvp, spriteRenderer.color);
        }
    }
}
