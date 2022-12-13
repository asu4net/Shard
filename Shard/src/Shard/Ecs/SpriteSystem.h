#pragma once
#include "System.h"

namespace Shard::Ecs
{
    class SpriteSystem : public System
    {
    private:
        void OnSceneUpdate() override;
    };
}
