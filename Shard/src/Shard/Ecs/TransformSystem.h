#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    struct Transform;

    class Scene;
    class TransformSystem
    {
    public:
        TransformSystem() = default;
        static void SmoothTranslation(Transform& transform, const Math::Vector3& destination, const float deltaSpeed, const float offset = .05f);
        static void Rotate(Transform& transform, const float degrees, const Math::Vector3& axis);
        static void RotateAround(Transform& transform, const float degrees, const Math::Vector3& axis);
        
    private:

        void CalculateTransforms(entt::registry& registry);
        void HandleTransform(Transform& t);

        friend class Scene;
    };
}
