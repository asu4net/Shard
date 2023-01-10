#pragma once
#include "Shard.h"

class FollowEntity : public Shard::EntityScript
{
    SHARD_OBJECT(FollowEntity, EntityScript)
public:
    Shard::Entity target;
    float reachDistance = .1f;
    float speed = 15.f;
    
    void Update() override;
};