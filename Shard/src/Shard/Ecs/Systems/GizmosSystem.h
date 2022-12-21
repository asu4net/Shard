#pragma once
#include "Ecs/Components.h"
#include "Ecs/System.h"

namespace Shard
{
    class GizmosSystem : public System
    {
        void OnSceneUpdate() override;
        void DrawCircleCollider(const Color& color, const Transform& transform, const CircleCollider& circleCollider);
        void DrawBoxCollider2D(const Color& color, const Transform& transform, BoxCollider2D& boxCollider2D);
    };
}