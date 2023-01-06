#pragma once
#include "Entity.h"
#include "Rendering/Font.h"
#include "Rendering/Sprite.h"
#include "box2d/b2_body.h"
#include "Ecs/Systems/PhysicMaterial.h"
#include "Ecs/Scripting/Script.h"

namespace Shard
{
    struct BaseComponent : public Object
    {
    SHARD_OBJECT(BaseComponent, Object)
    //TODO: Implement enabled, entt::entity and so on
    };

    struct Tag : public BaseComponent
    {
    SHARD_OBJECT(Tag, BaseComponent) 
    public:
        std::string name;
        std::string tag;
        
        Tag() = default;

        Tag(std::string name, std::string tag)
            : name(std::move(name))
            , tag(std::move(tag))
        {}
    };
    
    struct Transform : public BaseComponent
    {
    SHARD_OBJECT(Transform, BaseComponent)
    public:
        Vector3 position;
        glm::quat rotation = IdentityQuat;
        Vector3 scale = Vector3::one;
        Entity parent;
        
        Vector3 Right() const { return m_right; }
        Vector3 Up() const { return m_up; }
        Vector3 Forward() const { return m_forward; }
        glm::mat4 Model() const { return m_model; }
        Vector3 WorldPosition() const { return m_worldPosition; }
        glm::quat WorldRotation() const { return m_worldRotation; }
        
    private:
        Vector3 m_worldPosition;
        glm::quat m_worldRotation = IdentityQuat;
        Vector3 m_worldScale = Vector3::one;
        Vector3 m_right, m_up, m_forward;
        glm::mat4 m_model{1};
        
        friend class TransformSystem;
        friend class CollisionSystem;
        friend class Physics2DSystem;
    };

    struct Camera : public BaseComponent
    {
    SHARD_OBJECT(Camera, BaseComponent) 
    public:
        enum class Mode { Perspective, Orthographic };
        
        Mode mode = Mode::Orthographic;
        float size = 3.f;
        float fov = 45.f;
        float nearPlane = -100.f;
        float farPlane = 100.f;
        int priority = 0;
        
        glm::mat4 Projection() const { return m_projection; }
        glm::mat4 View() const { return m_view; }

    private:
        glm::mat4 m_projection{1}, m_view{1};
        friend class CameraSystem;
    };

    struct QuadRenderer : public BaseComponent
    {
    SHARD_OBJECT(QuadRenderer, BaseComponent) 
    public:
        Color color;
        bool enabled = true;
        
        QuadRenderer(const Color& theColor = Color::White)
            : color(theColor) {}
    };
    
    struct CircleRenderer : public BaseComponent
    {
    SHARD_OBJECT(CircleRenderer, BaseComponent) 
    public:
        Color color;
        float thickness;
        float fade;
        bool enabled = true;
        
        CircleRenderer(const Color& theColor = Color::White
            , const float theThickness = 1.f
            , const float theFade = 0.005f)
            : color(theColor), thickness(theThickness), fade(theFade) 
        {
        }
    };

    struct SpriteRenderer : public BaseComponent
    {
    SHARD_OBJECT(SpriteRenderer, BaseComponent) 
    public:
        std::shared_ptr<Sprite> sprite;
        std::shared_ptr<Shader> shader;
        int orderInLayer = 0;
        Color color = Color::White;
        bool enabled = true;
        
        SpriteRenderer(const Color& color)
            : color(color)
        {
            shader = std::make_shared<Shader>();
            sprite = std::make_shared<Sprite>("", shader);
        }
        
        SpriteRenderer(const std::string& texturePath = "",
            const std::string& vertexLoc = "",
            const std::string& fragmentLoc = "")
        {
            if (vertexLoc.empty() || fragmentLoc.empty())
                shader = std::make_shared<Shader>();
            else
                shader = std::make_shared<Shader>(vertexLoc.c_str(), fragmentLoc.c_str());

            sprite = std::make_shared<Sprite>(texturePath, shader);
        }
    };
    
    struct TextRenderer : public BaseComponent
    {
    SHARD_OBJECT(TextRenderer, BaseComponent) 
    public:
        std::shared_ptr<Font> font;
        float spacing = .3f;
        Color color;
        bool enabled = true;
        
        TextRenderer(std::string text = "", const Color& color = Color::Black, const std::string& fontPath = "res/Fonts/Orange.ttf")
            : font(std::make_shared<Font>(fontPath))
            , color(color)
            , m_text(std::move(text))
        {}
        
        std::string Text() const { return m_text; }
        
    private:
        std::string m_text;
        std::vector<std::string> m_charMeshes;

        friend class TextSystem;
    };

    //Requires SpriteRenderer component attached with multiple layout.
    struct SimpleSpriteAnimation : public BaseComponent
    {
    SHARD_OBJECT(SimpleSpriteAnimation, BaseComponent) 
    public:
        float rate = 0.08f;
        bool paused = false;
        
        SimpleSpriteAnimation(std::vector<int> layout = {})
            : m_layout(std::move(layout))
        {}

        int CurrentIndex() const { return m_currentLayoutIndex; }
        
    private:
        std::vector<int> m_layout;
        int m_currentLayoutIndex = 0;
        float m_currentTime = 0;

        friend class SimpleSpriteAnimationSystem;
    };

    struct CircleCollider : public BaseComponent
    {
    SHARD_OBJECT(CircleCollider, BaseComponent) 
    public:
        float radius = 1;
        Vector2 center;
        PhysicMaterial physicMaterial;

        b2Fixture& RuntimeFixture() { return *m_fixture; }

        CircleCollider() = default;
        CircleCollider(float radius, Vector2 center = Vector3::zero)
            : radius(radius),  center(center)
        {}

    private:
        b2Fixture* m_fixture = nullptr;
        float m_prevRadius = 0;

        friend class Physics2DSystem;
    };

    struct BoxCollider2D : public BaseComponent
    {
    SHARD_OBJECT(BoxCollider2D, BaseComponent) 
    public:
        Vector2 size{1, 1};
        Vector2 center;
        PhysicMaterial physicMaterial;

        BoxCollider2D() = default;

        b2Fixture& RuntimeFixture() { return *m_fixture; }

        BoxCollider2D(Vector2 size, Vector2 center = Vector3::zero)
            : size(size), center(center)
        {}

    private:
        b2Fixture* m_fixture = nullptr;
        Vector2 m_prevSize;

        friend class Physics2DSystem;
    };
    
    struct Physicbody2D : public BaseComponent
    {
    SHARD_OBJECT(Physicbody2D, BaseComponent) 
    public:
        enum class BodyType { Static, Kinematic, Dynamic };
        BodyType bodyType = BodyType::Dynamic;
        float mass = 1.f;
        float gravityScale = 1.f;

        b2Body& RuntimeBody() { return *m_body; }

        Physicbody2D() = default;

    private:
        b2Body* m_body = nullptr;
        BodyType m_prevBodyType;

        friend class Physics2DSystem;
    };

    struct Logic : public BaseComponent
    {
    SHARD_OBJECT(Logic, BaseComponent) 
    public:
        Logic() = default;

        template<typename T>
        T& AddScript()
        {
            T* script = new T();
            script->m_entity = m_entity;
            script->m_scene = m_scene;
            m_scripts.push_back(script);
            script->Awake();
            return *script;
        }
        
    private:
        std::vector<Script*> m_scripts;
        Entity m_entity;
        Scene* m_scene = nullptr;
        //TODO: Awake, onCollision, destroy

        friend class LogicSystem;
        friend class Physics2DSystem;
    };
}
