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

    void CollisionSystem::CheckCollisions(entt::registry& registry)
    {
        CheckCircleCircleCollisions(registry);
        CheckRectangleRectangleCollisions(registry);
    }

    void CollisionSystem::CheckCircleCircleCollisions(entt::registry& registry)
    {
        const auto view = registry.view<Transform, CircleCollider>();
        Camera& mainCamera = registry.get<Camera>(CameraSystem::MainCameraEntityHandler());

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

            DrawCircleGizmos(finalColor, mainCamera, transform, circleCollider);
        }
    }

    void CollisionSystem::CheckRectangleRectangleCollisions(entt::registry& registry)
    {
    }

    void CollisionSystem::DrawCircleGizmos(Color& color, Camera& mainCamera, Transform& transform, CircleCollider& circleCollider)
    {
        MvpData mvp{ transform.Model(), mainCamera.View(), mainCamera.Projection() };

        float size = circleCollider.radius * 2;
        mvp.model = glm::translate(transform.Model(), (transform.m_worldPosition + circleCollider.center).ToGlm());
        mvp.model = glm::scale(transform.Model(), { size, size, 1.f });

        Renderer::DrawCircle(mvp, color, circleCollidersThickness, circleCollidersFade);
    }

}
