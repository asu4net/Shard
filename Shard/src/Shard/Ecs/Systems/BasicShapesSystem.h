#pragma once
#include "Ecs/System.h"

namespace Shard
{
    class Scene;

    class BasicShapesSystem : public System
    {
    private:
        void OnSceneUpdate() override;
    };
}
