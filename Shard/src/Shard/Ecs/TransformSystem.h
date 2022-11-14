#pragma once

namespace Shard::Ecs
{
    struct Transform;
    class Entity;
    
    //Global functions
    
    class TransformSystem
    {
    public:
        static glm::mat4 GetMatrix(const Transform& transform);
        static glm::mat4 GetMatrix(const Entity entity);
        static bool TryApplyParentTransform(Transform& transform);
        static Math::Vector3 Right(const Transform& transform);
        static Math::Vector3 Up(const Transform& transform);
        static Math::Vector3 Forward(const Transform& transform);
        static void Rotate(Transform& transform, const float degrees, const Math::Vector3& axis);
        static void RotateAround(Transform& transform, const float degrees, const Math::Vector3& axis);
    };
}
