#include "shpch.h"
#include "Application.h"

namespace Shard
{
	Application::Application()
		:scene(&window)
	{
		printf("Shard Application constructed.\n");
	}

	Application::~Application()
	{
		printf("Shard Application destroyed.\n");
	}
	
	void Application::PreInitialize() {}

	void Application::Initialize()
	{
		printf("Shard Application created.\n");
		window.StartLoop();
	}
}