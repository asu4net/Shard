#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    struct Transform;
    struct Camera;
    class Scene;
    
    class CameraSystem
    {
    public:
        CameraSystem() = default;
        static entt::entity MainCameraEntity();
        
    private:
        static entt::entity m_mainCamera;
        int m_minPriority = 0;
        
        void CalculateCameraMatrices(entt::registry& registry, float windowAspectRatio);
        void HandleCamera(Camera& camera, const Transform& camTransform, const float windowAspectRatio);

        friend class Scene;
    };
}