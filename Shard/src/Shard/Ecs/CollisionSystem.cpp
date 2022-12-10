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
        const auto view = registry.view<Transform, BoxCollider2D>();
        Camera& mainCamera = registry.get<Camera>(CameraSystem::MainCameraEntityHandler());

        for (entt::entity entity : view)
        {
            auto& [transform, boxCollider2D] = view.get<Transform, BoxCollider2D>(entity);
            Color color = defaultColor;
            DrawBox2DGizmos(color, mainCamera, transform, boxCollider2D);
        }      
    }

    void CollisionSystem::DrawCircleGizmos(Color& color, Camera& mainCamera, Transform& transform, CircleCollider& circleCollider)
    {
        MvpData mvp{ transform.Model(), mainCamera.View(), mainCamera.Projection() };

        float size = circleCollider.radius * 2;
        glm::mat4 t = glm::translate(transform.Model(), (transform.m_worldPosition + circleCollider.center).ToGlm());
        glm::mat4 s = glm::scale(transform.Model(), { size, size, 1.f });
        mvp.model = t * s;

        Renderer::DrawCircle(mvp, color, circleCollidersThickness, circleCollidersFade);
    }

    void CollisionSystem::DrawBox2DGizmos(Color& color, Camera& mainCamera, Transform& transform, BoxCollider2D& boxCollider2D)
    {
        MvpData mvp{ transform.Model(), mainCamera.View(), mainCamera.Projection() };

        glm::mat4 t = glm::translate(transform.Model(), (transform.m_worldPosition + boxCollider2D.center).ToGlm());
        glm::mat4 s = glm::scale(transform.Model(), { boxCollider2D.size.x, boxCollider2D.size.y, 1.f });
        mvp.model = t * s;
        
        Renderer::DrawLines(Renderer::GetDefaultLineBox2D(), mvp, color);
    }

}
