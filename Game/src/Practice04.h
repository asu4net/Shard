#pragma once
#ifdef PRACTICE_04

//I created the SmoothTranslation method and the SimpleSpriteAnimation for this practice.
class Game final : public Application 
{
    Entity bee;
    //Note: The exercise requires 128 pixels per second, but I'm using world space coords.
    float mouseFollowSpeed = 3.f;
    
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 04 - Alejandro :D");
        window.SetBackgroundColor(Color::DarkGray);

        bee = scene.CreateEntity();
        const SpriteRenderer& beeRenderer = bee.Add<SpriteRenderer>("res/Textures/bee_anim.png");
        beeRenderer.sprite->SetMultipleLayout({80, 80}, {1, 8});
        bee.Add<SimpleSpriteAnimation>();
    }
    
    void OnRenderFrame(RenderFrameArgs args) override
    {
        const Camera& mainCam = scene.GetMainCameraEntity().Get<Camera>();
        const Vector3 mouseWorld = window.ScreenToWorldPoint(Input::GetMousePosition(), mainCam.Projection(), mainCam.View());
        TransformSystem::SmoothTranslation(bee.Get<Transform>(), mouseWorld, mouseFollowSpeed * Time::DeltaTime());
    }
};

SHARD_CREATE(Game)
#endif