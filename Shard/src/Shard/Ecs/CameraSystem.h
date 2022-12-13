#pragma once
#include "System.h"

namespace Shard::Ecs
{
    struct Transform;
    struct Camera;
    class Scene;
    
    class CameraSystem : public System
    {
    public:
        static entt::entity MainCameraEntityHandler();
        
    private:
        static entt::entity m_mainCamera;
        int m_minPriority = 0;
        
        void OnSceneUpdate() override;
        void HandleCamera(Camera& camera, const Transform& camTransform, const float windowAspectRatio);
    };
}