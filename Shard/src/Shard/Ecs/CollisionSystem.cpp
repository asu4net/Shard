#include "shpch.h"
#include "CollisionSystem.h"
#include "Components.h"

using namespace Shard::Math;
using namespace Shard::Rendering;

namespace Shard::Ecs
{
    const float CollisionSystem::circleCollidersThickness = .05f;
    const float CollisionSystem::circleCollidersFade = 0.005f;
    const Color CollisionSystem::defaultColor = Color::LightGreen;
    const Color CollisionSystem::collidingColor = Color::LightRed;
    
    void CollisionSystem::OnSceneUpdate()
    {
        CheckCircleCircleCollisions();
        CheckRectangleRectangleCollisions();
    }

    void CollisionSystem::CheckCircleCircleCollisions()
    {
        const auto view = Registry().view<Transform, CircleCollider>();

        for (entt::entity entity : view)
        {
            auto& [transform, circleCollider] = view.get<Transform, CircleCollider>(entity);
            Color finalColor = defaultColor;
            for (entt::entity otherEntity : view)
            {
                if (entity == otherEntity) continue;

                auto& [otherTransform, otherCircleCollider] = view.get<Transform, CircleCollider>(otherEntity);

                Vector3 colliderPos = transform.m_worldPosition + circleCollider.center;
                Vector3 otherColliderPos = otherTransform.m_worldPosition + otherCircleCollider.center;

                float distance = Vector3::Distance(colliderPos, otherColliderPos);
                if (distance <= circleCollider.radius + otherCircleCollider.radius)
                {
                    finalColor = collidingColor;
                    break;
                }
            }

            DrawCircleGizmos(finalColor, transform, circleCollider);
        }
    }

    void CollisionSystem::CheckRectangleRectangleCollisions()
    {
        const auto view = Registry().view<Transform, BoxCollider2D>();

        for (entt::entity entity : view)
        {
            auto& [transform, boxCollider2D] = view.get<Transform, BoxCollider2D>(entity);
            Color color = defaultColor;
            DrawBox2DGizmos(color, transform, boxCollider2D);
        }      
    }

    void CollisionSystem::DrawCircleGizmos(Color& color, Transform& transform, CircleCollider& circleCollider)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);

        float size = circleCollider.radius * 2;
        gizmosTransform = glm::translate(gizmosTransform, (transform.m_worldPosition + circleCollider.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.m_worldRotation);
        gizmosTransform = glm::scale(gizmosTransform, { size, size, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawCircle(mvp, color, circleCollidersThickness, circleCollidersFade);
    }

    void CollisionSystem::DrawBox2DGizmos(Color& color, Transform& transform, BoxCollider2D& boxCollider2D)
    {
        glm::mat4 gizmosTransform = glm::mat4(1.f);
        gizmosTransform = glm::translate(gizmosTransform, (transform.m_worldPosition + boxCollider2D.center).ToGlm());
        gizmosTransform *= glm::toMat4(transform.m_worldRotation);
        gizmosTransform = glm::scale(gizmosTransform, { boxCollider2D.size.x, boxCollider2D.size.y, 1.f });

        MvpData mvp{ gizmosTransform, GetCamera().View(), GetCamera().Projection() };
        Renderer::DrawLines(Renderer::GetDefaultLineBox2D(), mvp, color);
    }

}
