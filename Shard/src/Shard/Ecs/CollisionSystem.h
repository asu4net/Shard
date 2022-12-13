#pragma once
#include "System.h"

namespace Shard::Ecs
{
    struct Camera;
    struct Transform;
    struct CircleCollider;
    struct BoxCollider2D;

    class CollisionSystem : public System
    {
        static const float circleCollidersThickness;
        static const float circleCollidersFade;
        static const Math::Color collidingColor;
        static const Math::Color defaultColor;

        void OnSceneUpdate() override;

        void CheckCircleCircleCollisions();
        void CheckRectangleRectangleCollisions();
        void DrawCircleGizmos(Math::Color& color, Transform& transform, CircleCollider& circleCollider);
        void DrawBox2DGizmos(Math::Color& color, Transform& transform, BoxCollider2D& boxCollider2D);
        friend class Scene;
    };
}

