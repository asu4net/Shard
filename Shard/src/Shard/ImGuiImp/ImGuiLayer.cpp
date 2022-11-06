#include "shpch.h"

#include "ImGuiLayer.h"
#include "imgui.h"
#include "ImGuiGLFW.h"
#include "ImGuiOpenGL.h"

namespace Shard::ImGuiImp
{
    ImGuiLayer::ImGuiLayer(Rendering::Window* window)
    {
        window->OnRenderReady.ADD_LISTENER(ImGuiLayer, OnRenderReady);
        window->OnRenderFrame.ADD_LISTENER(ImGuiLayer, OnRenderFrame);
    }

    void ImGuiLayer::OnRenderReady(Rendering::OnRenderReadyEventArgs args)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        ImGui_ImplGlfw_InitForOpenGL(args.window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
    }

    void ImGuiLayer::OnRenderFrame(Rendering::OnRenderFrameEventArgs args)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
