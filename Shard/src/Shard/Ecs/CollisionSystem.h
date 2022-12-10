#pragma once
#include "entt.hpp"

class Scene;

namespace Shard::Ecs
{
    struct Camera;
    struct Transform;
    struct CircleCollider;
    struct BoxCollider2D;

    class CollisionSystem
    {
        static const float circleCollidersThickness;
        static const float circleCollidersFade;
        static const Math::Color collidingColor;
        static const Math::Color defaultColor;

        CollisionSystem() = default;
        void CheckCollisions(entt::registry& registry);
        void CheckCircleCircleCollisions(entt::registry& registry);
        void CheckRectangleRectangleCollisions(entt::registry& registry);
        void DrawCircleGizmos(Math::Color& color, Camera& mainCamera, Transform& transform, CircleCollider& circleCollider);
        void DrawBox2DGizmos(Math::Color& color, Camera& mainCamera, Transform& transform, BoxCollider2D& boxCollider2D);
        friend class Scene;
    };
}

