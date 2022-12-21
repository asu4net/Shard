#pragma once
#include "Ecs/System.h"

namespace Shard
{
    struct Transform;

    class Scene;
    
    class TransformSystem : public System
    {
    public:
        static void SmoothTranslation(Transform& transform, const Vector3& destination, const float deltaSpeed, const float offset = .05f);
        static void Rotate(Transform& transform, const float degrees, const Vector3& axis);
        static void RotateAround(Transform& transform, const float degrees, const Vector3& axis);
        
    private:
        void OnSceneUpdate() override;
        void HandleTransform(Transform& t);
    };
}
