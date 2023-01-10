#pragma once
#include "Ecs/Scripting/EntityScript.h"

namespace Shard
{
    class CameraController : public EntityScript
    {
        SHARD_OBJECT(CameraController, EntityScript)
    public:
        float cameraSpeed = 5.f;
        float zoomSpeed = 3.f;
        
        void Update() override;
    };
}


