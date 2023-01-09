#include "shpch.h"
#include "CameraSystem.h"
#include "Ecs/Components.h"

namespace Shard
{
    entt::entity CameraSystem::m_mainCamera{0};
    
    Entity CameraSystem::GetMainCameraEntity()
    {
        return Scene::GetEntityByHandler(m_mainCamera);
    }

    Vector3 CameraSystem::ScreenToWorldPoint(const Vector2& screenPoint, const glm::mat4& proj, const glm::mat4& view)
    {
        const float halfScreenWidth =  static_cast<float>(Window::CurrentWindowWidth) / 2;
        const float halfScreenHeight =  static_cast<float>(Window::CurrentWindowHeight) / 2;
        const glm::mat4 inverseMv = glm::inverse(proj * view);
        const glm::vec4 near = glm::vec4(((screenPoint.x - halfScreenWidth) / halfScreenWidth),(-1 * (screenPoint.y - halfScreenHeight) / halfScreenHeight), -1, 1.0);
        glm::vec4 nearResult = inverseMv * near;
        nearResult /= nearResult.w;
        return {nearResult.x, nearResult.y, 0};
    }
    
    Vector3 CameraSystem::ScreenToWorldPoint(const Vector2& screenPoint, const Camera& camera)
    {
        return ScreenToWorldPoint(screenPoint, camera.Projection(), camera.View());
    }
    
    Vector3 CameraSystem::ScreenToWorldPoint(const Vector2& screenPoint)
    {
        const Entity mainCamera = GetMainCameraEntity();
        if (!mainCamera.IsValid())
        {
            assert(false);
            return {};
        }
        return ScreenToWorldPoint(screenPoint, mainCamera.Get<Camera>());
    }

    void CameraSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<Camera, Transform>();

        Registry().sort<Camera>([](const Camera& a, const Camera& b)
            {
                return a.priority > b.priority;
            });
        
        for (const entt::entity entity : view)
        {
            if (entity == *(view.begin())) m_mainCamera = entity;
            const auto& [camera, camTransform] = view.get<Camera, Transform>(entity);
            HandleCamera(camera, camTransform, GetWindowAspect());
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
