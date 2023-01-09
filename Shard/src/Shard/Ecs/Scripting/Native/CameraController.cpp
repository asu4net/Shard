#include "shpch.h"
#include "CameraController.h"

#include "Input.h"
#include "TimeData.h"
#include "Ecs/Components.h"
#include "Ecs/Systems/CameraSystem.h"

namespace Shard
{
    void CameraController::Update()
    {
        const Entity mainCamera = CameraSystem::GetMainCameraEntity();
        auto& transform = mainCamera.Get<Transform>();
        auto& camera = mainCamera.Get<Camera>();
        
        if (Input::GetKeyPressed(KEY_W))
            transform.position += Vector3::up * Time::DeltaTime();
        if (Input::GetKeyPressed(KEY_S))
            transform.position += Vector3::down * Time::DeltaTime();
        if (Input::GetKeyPressed(KEY_A))
            transform.position += Vector3::left * Time::DeltaTime();
        if (Input::GetKeyPressed(KEY_D))
            transform.position += Vector3::right * Time::DeltaTime();

        if (Input::GetKeyPressed(KEY_UP))
            camera.size -= zoomSpeed * Time::DeltaTime();

        if (Input::GetKeyPressed(KEY_DOWN))
            camera.size += zoomSpeed * Time::DeltaTime();
        
    }
}
