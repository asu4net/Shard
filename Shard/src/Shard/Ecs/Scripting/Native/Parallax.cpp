#include "shpch.h"
#include "Parallax.h"
#include "Ecs/Components.h"
#include "Ecs/Entity.h"

namespace Shard
{
    void Parallax::Start()
    {
        if (!Has<SpriteRenderer>())
            assert(false);
    }
    
    void Parallax::Update()
    {
        const Entity mainCamera = GetMainCameraEntity();
        if (!mainCamera.IsValid()) return;
        Get<Transform>().position += scrollRate + mainCamera.Get<Transform>().position;
    }
}