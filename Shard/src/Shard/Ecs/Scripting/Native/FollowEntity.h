#pragma once
#include "Shard.h"

class FollowEntity : public Shard::Script
{
    SHARD_OBJECT(FollowEntity, Script)
public:
    Shard::Entity target;
    float reachDistance = .1f;
    float speed = 15.f;
    
    void Update() override;
};