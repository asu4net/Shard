#pragma once
#include "Entity.h"
#include "Rendering/Font.h"
#include "Rendering/Sprite.h"
#include "box2d/b2_polygon_shape.h"
#include "box2d/b2_body.h"

namespace Shard::Ecs
{
    struct String
    {
        std::string name;
        std::string tag;
        
        String(std::string name, std::string tag)
            : name(std::move(name))
            , tag(std::move(tag))
        {}
    };
    
    struct Transform
    {
        Math::Vector3 position;
        glm::quat rotation = IdentityQuat;
        Math::Vector3 scale = Math::Vector3::one;
        Entity parent;
        
        Math::Vector3 Right() const { return m_right; }
        Math::Vector3 Up() const { return m_up; }
        Math::Vector3 Forward() const { return m_forward; }
        glm::mat4 Model() const { return m_model; }

    private:
        Math::Vector3 m_worldPosition;
        glm::quat m_worldRotation = IdentityQuat;
        Math::Vector3 m_worldScale = Math::Vector3::one;
        Math::Vector3 m_right, m_up, m_forward;
        glm::mat4 m_model{1};
        
        friend class TransformSystem;
        friend class CollisionSystem;
        friend class Physics2DSystem;
    };

    struct Camera
    {
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

    struct QuadRenderer
    {
        Math::Color color;
        bool enabled = true;
        
        QuadRenderer(const Math::Color& theColor = Math::Color::White)
            : color(theColor) {}
    };
    
    struct CircleRenderer
    {
        Math::Color color;
        float thickness;
        float fade;
        bool enabled = true;
        
        CircleRenderer(const Math::Color& theColor = Math::Color::White
            , const float theThickness = 1.f
            , const float theFade = 0.005f)
            : color(theColor), thickness(theThickness), fade(theFade) {}
    };

    struct SpriteRenderer
    {
        std::shared_ptr<Rendering::Sprite> sprite;
        std::shared_ptr<Rendering::Shader> shader;
        int orderInLayer = 0;
        Math::Color color = Math::Color::White;
        bool enabled = true;
        
        SpriteRenderer(const std::string& texturePath = "",
            const std::string& vertexLoc = "",
            const std::string& fragmentLoc = "")
        {
            if (vertexLoc.empty() || fragmentLoc.empty())
                shader = std::make_shared<Rendering::Shader>();
            else
                shader = std::make_shared<Rendering::Shader>(vertexLoc.c_str(), fragmentLoc.c_str());

            sprite = std::make_shared<Rendering::Sprite>(texturePath, shader);
        }
    };
    
    struct TextRenderer
    {
        std::shared_ptr<Rendering::Font> font;
        float spacing = .3f;
        Math::Color color;
        bool enabled = true;
        
        TextRenderer(std::string text = "", const Math::Color& color = Math::Color::Black, const std::string& fontPath = "res/Fonts/Orange.ttf")
            : font(std::make_shared<Rendering::Font>(fontPath))
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
    struct SimpleSpriteAnimation
    {
        float framesPerSecond = 8.f;
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

    struct CircleCollider
    {
        float radius = 1;
        Math::Vector2 center;

        CircleCollider() = default;
        CircleCollider(float radius, Math::Vector2 center = Math::Vector3::zero)
            : radius(radius),  center(center)
        {}
    };

    struct BoxCollider2D
    {
        Math::Vector2 size{1, 1};
        Math::Vector2 center;
        
        float density = 1.0f;
        float friction = 0.5f;
        float bounciness = 0.0f;
        float bouncinessThreshold = 0.5f; //velocity to stop calculating bouncing 

        BoxCollider2D() = default;
        BoxCollider2D(Math::Vector2 size, Math::Vector2 center = Math::Vector3::zero)
            : size(size), center(center)
        {}

    private:
        b2PolygonShape* m_shape;
    };

    struct Physicbody2D
    {
        enum class BodyType { Static, Kinematic, Dynamic };
        BodyType bodyType = BodyType::Dynamic;

        Physicbody2D() = default;

    private:
        b2Body* m_body;

        friend class Physics2DSystem;
    };
}
