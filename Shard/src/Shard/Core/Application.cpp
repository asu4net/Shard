#include "Application.h"
#include <stdio.h>

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
	}
}