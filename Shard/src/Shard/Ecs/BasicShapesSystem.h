#pragma once
#include "System.h"

namespace Shard::Ecs
{
    class Scene;

    class BasicShapesSystem : public System
    {
    private:
        void OnSceneUpdate() override;
    };
}
