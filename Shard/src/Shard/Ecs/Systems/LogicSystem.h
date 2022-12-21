#pragma once
#include "Ecs/System.h"

namespace Shard
{
    class LogicSystem : public System
    {
        bool m_firstFrame = true;

        void OnSceneStart() override;
        void OnSceneUpdate() override;
        void OnSceneFixedUpdate() override;
        void OnComponentAdded(ComponentArgs args) override;
    };
}
