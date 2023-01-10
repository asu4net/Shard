#include "shpch.h"
#include "Shard.h"
#include "Shard/Core/EntryPoint.h"

using namespace Shard;
#include "Practice06/MainScript.h"

class Game final : public Application 
{
    void PreInitialize() override
    {
        scene.AddScript<MainScript>();
    }
};

SHARD_CREATE(Game)