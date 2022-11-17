#pragma once
#ifdef PRACTICE_04

class Game final : public Application
{
    Entity bee;
    float animationSpeed = 8.f;
    //Note: The exercise requires 128 pixels per second, but I'm using world space coords.
    float mouseFollowSpeed = 3.f;
    float currentSpeed = 0;
    float reachedDistance = 0.05f;
    
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 04 - Alejandro :D");
        window.SetBackgroundColor(Color::DarkGray);

        bee = scene.CreateEntity();
        const SpriteRenderer& beeRenderer = bee.Add<SpriteRenderer>("res/Textures/bee_anim.png");
        beeRenderer.sprite->SetMultipleLayout({80, 80}, {1, 8});
    }

    void OnRenderFrame(RenderFrameArgs args) override
    {
        AnimateBee();
        BeeMouseFollow();
    }
    
    void AnimateBee()
    {
        currentSpeed += Time::DeltaTime();
        if (currentSpeed < animationSpeed * Time::DeltaTime()) return;
        bee.Get<SpriteRenderer>().sprite->Next();
        currentSpeed = 0;
    }

    Vector3 MouseWorld()
    {
        const Camera& mainCam = scene.GetMainCameraEntity().Get<Camera>();
        return window.ScreenToWorldPoint(Input::GetMousePosition(), mainCam.Projection(), mainCam.View());
    }
    
    void BeeMouseFollow()
    {
        const Vector3 mouseWorld = MouseWorld();
        Transform& beeTransform = bee.Get<Transform>();
        const Vector3 moveDir = (mouseWorld - beeTransform.position).Normalized();
        const Vector3 newBeePos = beeTransform.position + moveDir * mouseFollowSpeed * Time::DeltaTime();
        
        if (Vector3::Distance(mouseWorld, newBeePos) <= reachedDistance)
            return;
        
        beeTransform.position = newBeePos;
    }
};

SHARD_CREATE(Game)
#endif