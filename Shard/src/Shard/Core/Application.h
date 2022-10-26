#pragma once
#include "Core.h"

namespace Shard
{
    class SHARD_API Application
    {
    public:
        Application();
        virtual ~Application();

        virtual void Start();
    };

    //This must be implemented in the user side.
    extern Application* CreateApplication();
}
