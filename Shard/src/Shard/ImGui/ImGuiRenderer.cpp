#include "shpch.h"

#include "ImGuiRenderer.h"
#include "imgui.h"
#include "ImGuiGLFW.h"
#include "ImGuiOpenGL.h"
#include "TimeData.h"

namespace Shard
{
    void ImGuiRenderer::ListenWindowEvents(Rendering::Window& window)
    {
        window.OnRenderReady.ADD_LISTENER(ImGuiRenderer, OnRenderReady);
        window.OnRenderFrame.ADD_LISTENER(ImGuiRenderer, OnRenderFrame);
    }

    void ImGuiRenderer::OnRenderReady(Rendering::RenderReadyArgs args)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        ImGui_ImplGlfw_InitForOpenGL(args.windowHandler, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        OnImGuiReady.Invoke({});
    }

    void ImGuiRenderer::OnRenderFrame(Rendering::RenderFrameArgs args)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = Time::DeltaTime() > 0.f ? Time::DeltaTime() : 1.f / 60.f;

        io.DisplaySize = ImVec2(args.window->GetWidth(), args.window->GetHeight());

        OnImGuiRender.Invoke({});
        
        if (showDemo)
            ImGui::ShowDemoWindow(&showDemo);
        
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
