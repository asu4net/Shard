#include "shpch.h"
#include "SpriteSystem.h"
#include "Components.h"

namespace Shard::Ecs
{
    void SpriteSystem::DrawSprites(entt::registry& registry)
    {
        const auto view = registry.view<SpriteRenderer, Transform>();

        const Camera& mainCamera = registry.get<Camera>(CameraSystem::MainCameraEntityHandler());

        registry.sort<SpriteRenderer>([](const SpriteRenderer& a, const SpriteRenderer& b)
        {
            return a.orderInLayer > b.orderInLayer;
        });
        
        for (const entt::entity entity : view)
        {
            const auto& [spriteRenderer, transform] = view.get<SpriteRenderer, Transform>(entity);
            if (!spriteRenderer.enabled) return;
            Math::MvpData mvp{transform.Model(), mainCamera.View(), mainCamera.Projection()};
            spriteRenderer.sprite->Draw(mvp, spriteRenderer.color);
        }
    }
}
