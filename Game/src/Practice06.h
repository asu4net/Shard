#pragma once
#ifdef PRACTICE_06
#include "Scripts/BeeController.h"
#include "Practice06/MainScript.h"

class Game final : public Application 
{
    //Entity bee;

    void PreInitialize() override
    {
        window.SetTitle("Practice 06 - Alejandro :D");
        scene.AddScript<MainScript>();
    }
};

SHARD_CREATE(Game)
#endif