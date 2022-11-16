#include "shpch.h"
#include "BasicShapesSystem.h"
#include "Components.h"
#include "Rendering/Renderer.h"
#include "CameraSystem.h"
#include "Scene.h"

namespace Shard::Ecs
{
    void BasicShapesSystem::DrawBasicShapes(entt::registry& registry)
    {
        const auto circleView = registry.view<Circle, Transform>();

        //TODO: Refactor
        const Camera& mainCamera = registry.get<Camera>(CameraSystem::MainCameraEntityHandler());
        
        for(const entt::entity entity : circleView)
        {
            const auto& [circle, circleTransform] = circleView.get<Circle, Transform>(entity);
            
            Math::MvpData mvp{circleTransform.Model(), mainCamera.View(), mainCamera.Projection()};
            Rendering::Renderer::DrawCircle(mvp, circle.color, circle.thickness, circle.fade);
        }
        
        const auto quadView = registry.view<Quad, Transform>();
        
        for(const entt::entity entity : quadView)
        {
            const auto& [quad, quadTransform] = quadView.get<Quad, Transform>(entity);
            
            Math::MvpData mvp{quadTransform.Model(), mainCamera.View(), mainCamera.Projection()};
            Rendering::Renderer::DrawQuad(Rendering::Renderer::GetDefaultQuad(), mvp,
                Rendering::Renderer::GetDefaultShader(), quad.color);
        }
    }
}
