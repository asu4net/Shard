#pragma once

namespace Shard
{
    class Entity;
    class Scene;
    
    class Script : public Object
    {
        SHARD_OBJECT(Script, Object)
    public:
        Script() = default;
        
        virtual void Awake() {}
        virtual void Start() {}
        virtual void Update() {}
        virtual void FixedUpdate() {}
        
        Entity CreateEntity(const std::string& name = "Entity", const std::string& tag = "Default");
        void DestroyEntity(Entity entity);
        
    private:
        Scene* m_scene = nullptr;
        
        friend struct Logic;
        friend class LogicSystem;
        friend class Scene;
    };
}
