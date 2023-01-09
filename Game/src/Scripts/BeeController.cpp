#include "shpch.h"
#include "BeeController.h"

using namespace Shard;

void BeeController::Start()
{
    SpriteRenderer& beeRenderer = Add<SpriteRenderer>("res/Textures/bee_anim.png");
    beeRenderer.sprite->SetMultipleLayout({80, 80}, {1, 8});
    beeRenderer.orderInLayer = -5;
    Add<SimpleSpriteAnimation>();
}

void BeeController::Update()
{
    Transform& beeTransform = Get<Transform>();
        
    //Bee translation
    const Vector3 mouseWorld = CameraSystem::ScreenToWorldPoint(Input::GetMousePosition());
    TransformSystem::SmoothTranslation(beeTransform, mouseWorld, mouseFollowSpeed * Time::DeltaTime());
    
    //Bee rotation
    const Vector3 beeDisplacement = beeTransform.position - prevBeePosition;
    prevBeePosition = beeTransform.position;
    currentDegrees = glm::degrees(glm::eulerAngles(beeTransform.rotation).z);
    
    goingRight = beeDisplacement.x > 0;
    stopped = std::abs(beeDisplacement.x) < 0.0001f;
    
    if (stopped && glm::abs(currentDegrees) <= 0.15f) return;
    if (!stopped && goingRight && 15.f - currentDegrees <= 0.15f) return;
    if (!stopped && glm::abs(-15.f - currentDegrees) <= 0.15f) return;
    
    TransformSystem::Rotate(beeTransform, rotationSpeed * (goingRight ? 1.f : -1.f) * Time::DeltaTime(), Vector3::forward);
}
