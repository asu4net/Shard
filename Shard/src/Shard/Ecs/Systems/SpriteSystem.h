#pragma once
#include "Ecs/System.h"

namespace Shard
{
    class SpriteSystem : public System
    {
    private:
        void OnSceneUpdate() override;
    };
}
