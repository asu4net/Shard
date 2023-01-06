#pragma once
#include "Ecs/Scripting/Script.h"

namespace Shard
{
    class Parallax : public Script
    {
        SHARD_OBJECT(Parallax, Script)
    public:
        Vector2 scrollRate;
        
        void Start() override;
        void Update() override;
    };
}
