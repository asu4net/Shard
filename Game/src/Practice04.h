#pragma once
#ifdef PRACTICE_04

/**
 * \brief I created the SmoothTranslation function for this practice.
 */
class Game final : public Application
{
    Entity bee;
    float animationSpeed = 8.f;
    //Note: The exercise requires 128 pixels per second, but I'm using world space coords.
    float mouseFollowSpeed = 3.f;
    float currentSpeed = 0;
    
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
        
        const Camera& mainCam = scene.GetMainCameraEntity().Get<Camera>();
        const Vector3 mouseWorld = window.ScreenToWorldPoint(Input::GetMousePosition(), mainCam.Projection(), mainCam.View());
        TransformSystem::SmoothTranslation(bee.Get<Transform>(), mouseWorld, mouseFollowSpeed * Time::DeltaTime());
    }
    
    void AnimateBee()
    {
        currentSpeed += Time::DeltaTime();
        if (currentSpeed < animationSpeed * Time::DeltaTime()) return;
        bee.Get<SpriteRenderer>().sprite->Next();
        currentSpeed = 0;
    }
};

SHARD_CREATE(Game)
#endif