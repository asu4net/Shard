#include "shpch.h"
#include "TransformSystem.h"
#include "Components.h"
#include "Entity.h"

namespace Shard::Ecs
{
    glm::mat4 TransformSystem::GetMatrix(const Transform& transform)
    {
        glm::mat4 model = glm::mat4(1);
        model = glm::translate(model, transform.position.ToGlm());
        model *= glm::toMat4(transform.rotation);
        model = glm::scale(model, transform.scale.ToGlm());
        return model;
    }

    glm::mat4 TransformSystem::GetMatrix(const Entity entity)
    {
        if (!entity.Has<Transform>())
        {
            assert(false);
            return glm::mat4(1);
        }
        return GetMatrix(entity.Get<Transform>());
    }

    bool TransformSystem::TryApplyParentTransform(Transform& transform)
    {
        if (!transform.parent.IsValid()) return false;
        
        const auto& parentTransform = transform.parent.Get<Transform>();
        transform.position += parentTransform.position;
        transform.rotation += parentTransform.rotation;
        transform.scale += transform.scale;
        return true;
    }

    Math::Vector3 TransformSystem::Right(const Transform& transform)
    {
        return Math::Vector3::LookAt(transform.rotation, Math::Vector3::right);
    }

    Math::Vector3 TransformSystem::Up(const Transform& transform)
    {
        return Math::Vector3::LookAt(transform.rotation, Math::Vector3::up);
    }

    Math::Vector3 TransformSystem::Forward(const Transform& transform)
    {
        return Math::Vector3::LookAt(transform.rotation, Math::Vector3::forward);
    }

    void TransformSystem::Rotate(Transform& transform, const float degrees, const Math::Vector3& axis)
    {
        transform.rotation = transform.rotation * glm::normalize(glm::angleAxis(glm::radians(degrees), axis.ToGlm()));
        transform.rotation = glm::normalize(transform.rotation);
    }

    void TransformSystem::RotateAround(Transform& transform, const float degrees, const Math::Vector3& axis)
    {
        transform.rotation = glm::normalize(glm::angleAxis(glm::radians(degrees), axis.ToGlm())) * transform.rotation;
        transform.rotation = glm::normalize(transform.rotation);
    }
}
