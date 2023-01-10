#pragma once
#include "Ecs/Scripting/EntityScript.h"

namespace Shard
{
    class Parallax : public EntityScript
    {
        SHARD_OBJECT(Parallax, EntityScript)
    public:
        Vector2 scrollScale = {1, 1};
        
        void Start() override;
        void Update() override;

    private:
        Vector3 lastCameraPosition;
    };
}
