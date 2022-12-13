#include "shpch.h"
#include "CameraSystem.h"
#include "TransformSystem.h"
#include "Components.h"

namespace Shard::Ecs
{
    entt::entity CameraSystem::m_mainCamera;

    entt::entity CameraSystem::MainCameraEntityHandler()
    {
        return m_mainCamera;
    }
    
    void CameraSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<Camera, Transform>();

        for (const entt::entity entity : view)
        {
            const auto& [camera, camTransform] = view.get<Camera, Transform>(entity);
            HandleCamera(camera, camTransform, GetWindowAspect());

            if (camera.priority < m_minPriority || m_mainCamera == entt::entity{ 0 })
            {
                m_mainCamera = entity;
                m_minPriority = camera.priority;
            }
        }
    }

    void CameraSystem::HandleCamera(Camera& camera, const Transform& camTransform, const float windowAspectRatio)
    {
        //View calculation
        camera.m_view = glm::lookAt(camTransform.position.ToGlm(),
            (camTransform.position - camTransform.Forward()).ToGlm(), camTransform.Up().ToGlm());
        
        //Projection calculation
        if (camera.mode == Camera::Mode::Orthographic)
        {
            const float right = windowAspectRatio * camera.size;
            const float left = -right;
            camera.m_projection = glm::ortho(left, right, -camera.size, camera.size, camera.nearPlane, camera.farPlane);
            return;
        }
        
        //if Camera::Mode::Perspective
        camera.m_projection = glm::perspective(camera.fov, windowAspectRatio, camera.nearPlane, camera.farPlane);
    }
}
