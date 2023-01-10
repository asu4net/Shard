#pragma once
#include "Ecs/Entity.h"

namespace Shard
{
    class Script : public Object
    {
        SHARD_OBJECT(Script, Object)
    public:
        Script() = default;
        
        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}
        
        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default")
        {
            return m_scene->CreateEntity();
        }
        
        void DestroyEntity(Entity entity) { m_scene->DestroyEntity(entity); }
        
    private:
        Scene* m_scene = nullptr;
        
        friend struct Logic;
        friend class LogicSystem;
    };
}
