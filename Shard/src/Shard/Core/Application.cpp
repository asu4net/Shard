#include "Application.h"
#include <stdio.h>
#include "ShardEvents/Event.h"

namespace Shard
{
	Application::Application()
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

		m_Window.OnRenderReady.ADD_LISTENER(Application, OnRenderReady);
		m_Window.OnRenderFrame.ADD_LISTENER(Application, OnRenderFrame);

		m_Window.StartLoop();
	}
	void Application::OnRenderReady(ShardEvents::OnRenderReadyEventArgs _Args)
	{

	}
	void Application::OnRenderFrame(ShardEvents::OnRenderFrameEventArgs _Args)
	{

	}
}