#pragma once
#include "Ecs/System.h"

namespace Shard
{
    struct Transform;
    struct Camera;
    class Scene;
    class Entity;
    
    class CameraSystem : public System
    {
    public:
        static Entity GetMainCameraEntity();

        static Vector3 ScreenToWorldPoint(const Vector2& screenPoint, const glm::mat4& proj, const glm::mat4& view);
        static Vector3 ScreenToWorldPoint(const Vector2& screenPoint, const Camera& camera);
        static Vector3 ScreenToWorldPoint(const Vector2& screenPoint);
        
    private:
        static entt::entity m_mainCamera;
        
        void OnSceneUpdate() override;
        void HandleCamera(Camera& camera, const Transform& camTransform, const float windowAspectRatio);
    };
}