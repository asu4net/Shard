#include "shpch.h"
#include "LogicSystem.h"
#include "Ecs/Components.h"

namespace Shard
{
    void LogicSystem::OnSceneStart()
    {
    }

    void LogicSystem::OnSceneUpdate()
    {
        Registry().view<Logic>().each([&](const auto entity, const Logic& logic)
        {
            for (size_t i = 0; i < logic.m_scripts.size(); i++)
            {
                if (!Registry().valid(entity)) break;
                Script* script = logic.m_scripts[i];
                if (m_firstFrame) script->Start();
                if (!Registry().valid(entity)) break;
                script->Update();
            }
        });
        
        if (m_firstFrame)
            m_firstFrame = false;
    }

    void LogicSystem::OnSceneFixedUpdate()
    {
        Registry().view<Logic>().each([&](const auto entity, const Logic& logic)
        {
            for (size_t i = 0; i < logic.m_scripts.size(); i++)
            {
                if (!Registry().valid(entity)) break;
                Script* script = logic.m_scripts[i];
                script->FixedUpdate();
            }
        });
    }
    
    void LogicSystem::OnComponentAdded(ComponentArgs args)
    {
        if (args.componentType != Logic::GetType()) return;
        
        const Entity entity = GetEntityByHandler(args.entityHandler);
        Logic& logic = entity.Get<Logic>();
        logic.m_entity = entity;
        logic.m_scene = GetScene();
    }
}