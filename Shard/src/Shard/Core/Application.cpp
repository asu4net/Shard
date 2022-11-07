#include "shpch.h"
#include "Application.h"

namespace Shard
{
	Application::Application()
	{
		//Applications listens window
		window.OnRenderReady.ADD_LISTENER(Application, OnRenderReady);
		window.OnRenderFrame.ADD_LISTENER(Application, OnRenderFrame);

		//ImGui listens window
		imGuiRenderer.ListenWindowEvents(window);

		//Application listens ImGui
		imGuiRenderer.OnImGuiReady.ADD_LISTENER(Application, OnImGuiReady);
		imGuiRenderer.OnImGuiRender.ADD_LISTENER(Application, OnImGuiRender);
		
		printf("Shard Application created.\n");
	}

	Application::~Application()
	{
		printf("Shard Application destroyed.\n");
	}

	void Application::Start()
	{
		printf("Shard Application started.\n");
		window.StartLoop();
	}

	//Event listeners
	void Application::OnImGuiReady(ImGuiReadyArgs args){}
	void Application::OnImGuiRender(ImGuiRenderArgs args){}
	void Application::OnRenderReady(Rendering::RenderReadyArgs args) {}
	void Application::OnRenderFrame(Rendering::RenderFrameArgs args) {}
}