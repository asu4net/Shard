#pragma once
#include "System.h"

namespace Shard::Ecs
{
    struct TextRenderer;
    struct Transform;
    struct Camera;
    
    class TextSystem : public System
    {
        void OnSceneUpdate() override;
        void OnComponentAdded(EntityArgs args) override;
        
        static void SetText(TextRenderer& textRenderer, const std::string& newText);
        
    private:
        static void RenderText(const TextRenderer& textRenderer, const Transform& transform, const Camera& mainCamera);
    };
}


