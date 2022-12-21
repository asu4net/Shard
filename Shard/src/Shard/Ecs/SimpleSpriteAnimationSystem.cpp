#include "shpch.h"
#include "SimpleSpriteAnimationSystem.h"
#include "Components.h"
#include "TimeData.h"

namespace Shard
{
    void SimpleSpriteAnimationSystem::OnSceneUpdate()
    {
        const auto view = Registry().view<SpriteRenderer, SimpleSpriteAnimation>();

        for (const entt::entity entity : view)
        {
            const auto& [sRenderer, animation] = view.get<SpriteRenderer, SimpleSpriteAnimation>(entity);

            if (animation.paused) continue;

            animation.m_currentTime += Time::DeltaTime();

            if (animation.m_currentTime < animation.framesPerSecond * Time::DeltaTime()) continue;

            animation.m_currentTime = 0;

            if (animation.m_layout.empty())
            {
                sRenderer.sprite->Next();
                continue;
            }

            sRenderer.sprite->currentSubMesh = animation.m_layout[animation.m_currentLayoutIndex];

            animation.m_currentLayoutIndex++;
            if (animation.m_currentLayoutIndex == animation.m_layout.size())
                animation.m_currentLayoutIndex = 0;
        }
    }
}
