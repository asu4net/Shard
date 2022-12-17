#include "shpch.h"
#include "LogicSystem.h"
#include "Components.h"

namespace Shard::Ecs
{

    void LogicSystem::OnSceneStart()
    {
    }

    void LogicSystem::OnSceneUpdate()
    {
        auto view = Registry().view<Logic>();

        for (entt::entity entity : view)
        {
            Logic& logic = view.get<Logic>(entity);
            for (Script* script : logic.m_scripts)
            {
                if (m_firstFrame)
                    script->Start();
                script->Update();
            }
                
        }

        if (m_firstFrame)
            m_firstFrame = false;
    }

    void LogicSystem::OnSceneFixedUpdate()
    {
        auto view = Registry().view<Logic>();

        for (entt::entity entity : view)
        {
            Logic& logic = view.get<Logic>(entity);
            for (Script* script : logic.m_scripts)
                script->FixedUpdate();
        }
    }
}