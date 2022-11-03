#pragma once

#include "Application.h"

#ifdef SHARD_PLATFORM_WINDOWS

void main()
{
	const auto app = Shard::CreateApplication();
	app->Start();
	delete app;
}

#endif
