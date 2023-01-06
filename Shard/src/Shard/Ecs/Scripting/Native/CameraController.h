#pragma once
#include "Ecs/Scripting/Script.h"

namespace Shard
{
    class CameraController : public Script
    {
        SHARD_OBJECT(CameraController, Script)
    public:
        float cameraSpeed = 5.f;
        float zoomSpeed = 3.f;
        
        void Update() override;
    };
}


