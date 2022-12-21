#include "shpch.h"
#include "GizmosSystem.h"
#include "Rendering/Renderer.h"
#include "Components.h"

namespace Shard
{
    void GizmosSystem::OnSceneUpdate()
    {
        const auto boxView = Registry().view<Transform, BoxCollider2D>();

        for (const entt::entity entity : boxView)
        {
            auto& [transform, boxCollider2D] = boxView.get<Transform, BoxCollider2D>(entity);
            DrawBoxCollider2D(Color::LightGreen, transform, boxCollider2D);
        }

        const auto circleView = Registry().view<Transform, CircleCollider>();

        for (const entt::entity entity : circleView)
        {
            auto& [transform, circleCollider] = circleView.get<Transform, CircleCollider>(entity);
            DrawCircleCollider(Color::LightGreen, transform, circleCollider);
        }
    }

    void GizmosSystem::DrawCircleCollider(const Color& color, const Transform& transform, const CircleCollider& circleCollider)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);

        float size = circleCollider.radius * 2;
        gizmosTransform = glm::translate(gizmosTransform, (transform.WorldPosition() + circleCollider.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.WorldRotation());
        gizmosTransform = glm::scale(gizmosTransform, { size, size, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawCircle(mvp, color, .05f, 0.005f);
    }

    void GizmosSystem::DrawBoxCollider2D(const Color& color, const Transform& transform, BoxCollider2D& boxCollider2D)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);
        gizmosTransform = glm::translate(gizmosTransform, (transform.WorldPosition() + boxCollider2D.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.WorldRotation());
        gizmosTransform = glm::scale(gizmosTransform, { boxCollider2D.size.x, boxCollider2D.size.y, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawLines(Renderer::GetDefaultLineBox2D(), mvp, color);
    }
}