#include "shpch.h"
#include "Application.h"

namespace Shard
{
	Application::Application()
		: imGuiLayer(&window)

	{
		printf("Shard Application created.\n");
	}

	Application::~Application()
	{
		
		printf("Shard Application destroyed.\n");
	}

	void Application::Start()
	{
		printf("Shard Application started.\n");

		window.OnRenderReady.ADD_LISTENER(Application, OnRenderReady);
		window.OnRenderFrame.ADD_LISTENER(Application, OnRenderFrame);

		window.StartLoop();
	}
	
	void Application::OnRenderReady(Rendering::OnRenderReadyEventArgs args) {}
	void Application::OnRenderFrame(Rendering::OnRenderFrameEventArgs args) {}
}