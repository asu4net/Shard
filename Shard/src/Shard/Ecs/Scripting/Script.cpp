#include "shpch.h"
#include "Script.h"

#include "Ecs/Components.h"

namespace Shard
{
    Vector3 Script::ScreenToWorldPoint(const Vector2& screenPos)
    {
        const Camera& camera = GetMainCameraEntity().Get<Camera>();
        return m_scene->GetWindow()->ScreenToWorldPoint(screenPos, camera.Projection(), camera.View());
    }
}
