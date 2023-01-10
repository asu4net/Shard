#include "shpch.h"

#include "ImGuiRenderer.h"
#include "imgui.h"
#include "ImGuiGLFW.h"
#include "ImGuiOpenGL.h"
#include "TimeData.h"
#include "GLFW/glfw3.h"

namespace Shard
{
    void ImGuiRenderer::ListenWindowEvents(Window& window)
    {
        window.OnRenderReady.ADD_LISTENER(ImGuiRenderer, OnRenderReady);
        window.OnRenderFrameStart.ADD_LISTENER(ImGuiRenderer, OnRenderFrameStart);
        window.OnRenderFrameEnd.ADD_LISTENER(ImGuiRenderer, OnRenderFrameEnd);
    }

    void ImGuiRenderer::OnRenderReady(RenderReadyArgs args)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.Fonts->AddFontFromFileTTF("res/Fonts/AlbertSans-VariableFont_wght.ttf", 25);
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        
        ImGui_ImplGlfw_InitForOpenGL(args.windowHandler, true);
        ImGui_ImplOpenGL3_Init("#version 330");
        ImGui::StyleColorsDark();
        OnImGuiReady.Invoke({});
    }

    void ImGuiRenderer::OnRenderFrameStart(RenderFrameArgs args)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
        if (showDemo)
            ImGui::ShowDemoWindow(&showDemo);
        
        ImGuiIO& io = ImGui::GetIO();
        io.DeltaTime = Time::DeltaTime() > 0.f ? Time::DeltaTime() : 1.f / 60.f;
        io.DisplaySize = ImVec2(args.window->GetWidth(), args.window->GetHeight());

        OnImGuiRender.Invoke({});
        
        ImGui::Render();
    }
    
    void ImGuiRenderer::OnRenderFrameEnd(RenderFrameArgs args)
    {
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        
        const ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}
