#pragma once
#ifdef PRACTICE_04

//I created the SmoothTranslation method and the SimpleSpriteAnimation for this practice.
class Game final : public Application 
{
    Entity bee;
    //Note: The exercise requires 128 pixels per second, but I'm using world space coords.
    float mouseFollowSpeed = 3.f;
    float rotationSpeed = 32.f;
    Vector3 prevBeePosition;
    float currentDegrees = 0.f;

    bool goingRight = false;
    bool stopped = false;
    
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
        Transform& beeTransform = bee.Get<Transform>();
        
        //Bee translation
        const Camera& mainCam = scene.GetMainCameraEntity().Get<Camera>();
        const Vector3 mouseWorld = window.ScreenToWorldPoint(Input::GetMousePosition(), mainCam.Projection(), mainCam.View());
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

    void OnImGuiReady(ImGuiReadyArgs args) override
    {
        ImGui::SetWindowSize("Bee info:", {300, 200});
    }

    void OnImGuiRender(ImGuiRenderArgs args) override
    {
        ImGui::Begin("Bee info:");
        std::string state = goingRight ? "Going right." : "Going left.";
        if (stopped) state = "Stopped.";
        ImGui::Text("Move state: %s", state.c_str());
        ImGui::Text("Current degrees: %f", static_cast<double>(currentDegrees));
        ImGui::End();
    }
};

SHARD_CREATE(Game)
#endif