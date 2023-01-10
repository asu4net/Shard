﻿#pragma once
#include "Shard.h"

class BeeController : public Shard::EntityScript
{
    SHARD_OBJECT(BeeController, EntityScript)
public:
    float mouseFollowSpeed = 3.f;
    float rotationSpeed = 32.f;
    Shard::Vector3 prevBeePosition;
    float currentDegrees = 0.f;

    bool goingRight = false;
    bool stopped = false;
    
    void Start() override;
    void Update() override;
};