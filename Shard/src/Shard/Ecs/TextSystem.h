#pragma once
#include "entt.hpp"

namespace Shard::Ecs
{
    struct TextRenderer;
    struct Transform;
    struct Camera;
    
    class TextSystem
    {
    public:
        TextSystem() = default;
        void RenderTexts(entt::registry& registry);
        
        static void SetText(TextRenderer& textRenderer, const std::string& newText);
        
    private:
        static void RenderText(const TextRenderer& textRenderer, const Transform& transform, const Camera& mainCamera);
    };
}


