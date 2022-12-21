#include "shpch.h"
#include "TransformSystem.h"
#include "Ecs/Components.h"
#include "Ecs/Entity.h"

namespace Shard
{
    void TransformSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<Transform>();

        for (const entt::entity entity : view)
        {
            Transform& t = view.get<Transform>(entity);
            HandleTransform(t);
        }
    }

    void TransformSystem::HandleTransform(Transform& t)
    {
        t.m_worldPosition = t.position;
        t.m_worldRotation = t.rotation;
        t.m_worldScale = t.scale;
        
        if (t.parent.IsValid())
        {
            const auto& tParent = t.parent.Get<Transform>();
            t.m_worldPosition += tParent.m_worldPosition;
            t.m_worldRotation += tParent.m_worldRotation;
            t.m_worldScale += t.m_worldScale;
        }
        
        glm::mat4 model = glm::mat4(1);
        model = glm::translate(model, t.m_worldPosition.ToGlm());
        model *= glm::toMat4(t.m_worldRotation);
        model = glm::scale(model, t.m_worldScale.ToGlm());
        t.m_model = model;

        t.m_right = Vector3::LookAt(t.rotation, Vector3::right);
        t.m_up = Vector3::LookAt(t.rotation, Vector3::up);
        t.m_forward = Vector3::LookAt(t.rotation, Vector3::forward);
    }

    void TransformSystem::SmoothTranslation(Transform& transform, const Vector3& destination, const float deltaSpeed, const float offset)
    {
        const Vector3 moveDir = (destination - transform.position).Normalized();
        const Vector3 newPos = transform.position + moveDir * deltaSpeed;
        if (Vector3::Distance(destination, newPos) <= offset)
            return;
        transform.position = newPos;
    }

    void TransformSystem::Rotate(Transform& transform, const float degrees, const Vector3& axis)
    {
        transform.rotation = transform.rotation * glm::normalize(glm::angleAxis(glm::radians(degrees), axis.ToGlm()));
        transform.rotation = glm::normalize(transform.rotation);
    }

    void TransformSystem::RotateAround(Transform& transform, const float degrees, const Vector3& axis)
    {
        transform.rotation = glm::normalize(glm::angleAxis(glm::radians(degrees), axis.ToGlm())) * transform.rotation;
        transform.rotation = glm::normalize(transform.rotation);
    }
}
