#pragma once
#ifdef PRACTICE_04
#include "Scripts/BeeController.h"

//I created the SmoothTranslation method and the SimpleSpriteAnimation for this practice.
class Game final : public Application 
{
    Entity bee;
    
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 04 - Alejandro :D");
        window.SetBackgroundColor(Color::DarkGray);

        bee = scene.CreateEntity();
        bee.Add<Logic>().AddScript<BeeController>();
    }
    
    void OnImGuiReady(ImGuiReadyArgs args) override
    {
        ImGui::SetWindowSize("Bee info:", {300, 200});
    }

    void OnImGuiRender(ImGuiRenderArgs args) override
    {
        const BeeController& beeController = bee.Get<Logic>().GetScript<BeeController>();
        
        ImGui::Begin("Bee info:");
        std::string state = beeController.goingRight ? "Going right." : "Going left.";
        if (beeController.stopped) state = "Stopped.";
        ImGui::Text("Move state: %s", state.c_str());
        ImGui::Text("Current degrees: %f", static_cast<double>(beeController.currentDegrees));
        ImGui::End();
    }
};

SHARD_CREATE(Game)
#endif