#pragma once
#include "Ecs/Scripting/Script.h"

namespace Shard
{
    class Parallax : public Script
    {
        SHARD_OBJECT(Parallax, Script)
    public:
        Vector2 scrollScale = {1, 1};
        
        void Start() override;
        void Update() override;

    private:
        Vector3 lastCameraPosition;
    };
}
