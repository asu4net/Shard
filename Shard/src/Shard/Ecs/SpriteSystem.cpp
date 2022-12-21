#include "shpch.h"
#include "SpriteSystem.h"
#include "Components.h"

namespace Shard
{
    void SpriteSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<SpriteRenderer, Transform>();

        Registry().sort<SpriteRenderer>([](const SpriteRenderer& a, const SpriteRenderer& b)
            {
                return a.orderInLayer > b.orderInLayer;
            });

        for (const entt::entity entity : view)
        {
            const auto& [spriteRenderer, transform] = view.get<SpriteRenderer, Transform>(entity);
            if (!spriteRenderer.enabled) return;
            MvpData mvp{ transform.Model(), GetCamera().View(), GetCamera().Projection()};
            spriteRenderer.sprite->Draw(mvp, spriteRenderer.color);
        }
    }
}