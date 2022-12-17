#pragma once
#include "Entity.h"

namespace Shard::Ecs
{
    class Script
    {
    public:
        Script() = default;

        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}
        virtual void OnCollision(Entity other) {}

        //wrapper functions of entity...
    private:
        Entity m_entity;

        friend class LogicSystem;
    };
}