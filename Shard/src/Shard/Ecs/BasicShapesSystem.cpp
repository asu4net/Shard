#include "shpch.h"
#include "BasicShapesSystem.h"
#include "Components.h"
#include "Rendering/Renderer.h"

namespace Shard
{
    void BasicShapesSystem::OnSceneUpdate()
    {
        const auto circleView = Registry().view<CircleRenderer, Transform>();

        for (const entt::entity entity : circleView)
        {
            const auto& [circle, circleTransform] = circleView.get<CircleRenderer, Transform>(entity);
            if (!circle.enabled) return;

            MvpData mvp{ circleTransform.Model(), GetCamera().View(), GetCamera().Projection()};
            Renderer::DrawCircle(mvp, circle.color, circle.thickness, circle.fade);
        }

        const auto quadView = Registry().view<QuadRenderer, Transform>();

        for (const entt::entity entity : quadView)
        {
            const auto& [quad, quadTransform] = quadView.get<QuadRenderer, Transform>(entity);
            if (!quad.enabled) return;

            MvpData mvp{ quadTransform.Model(), GetCamera().View(), GetCamera().Projection() };
            Renderer::DrawQuad(Renderer::GetDefaultQuad(), mvp,
                Renderer::GetDefaultShader(), quad.color);
        }
    }
}
