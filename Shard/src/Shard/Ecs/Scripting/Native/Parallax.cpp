#include "shpch.h"
#include "Parallax.h"
#include "Ecs/Components.h"
#include "Ecs/Entity.h"
#include "Ecs/Systems/CameraSystem.h"

namespace Shard
{
    void Parallax::Start()
    {
        if (!Has<SpriteRenderer>())
            assert(false);
    }
    
    void Parallax::Update()
    {
        const Entity mainCamera = CameraSystem::GetMainCameraEntity();
        if (!mainCamera.IsValid()) return;

        const Vector3 currentCameraPosition = mainCamera.Get<Transform>().position;
        Vector3 deltaMovement = currentCameraPosition - lastCameraPosition;
        lastCameraPosition = currentCameraPosition;
        deltaMovement.x *= scrollScale.x;
        deltaMovement.y *= scrollScale.y;
        
        Get<Transform>().position += deltaMovement;
    }
}