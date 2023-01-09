#pragma once
#ifdef PRACTICE_06
#include "Scripts/BeeController.h"

class Game final : public Application 
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 06 - Alejandro :D");
        window.SetBackgroundColor(Color::DarkGray);

        const Entity mainCamera = scene.GetMainCameraEntity();
        mainCamera.Add<Logic>().AddScript<CameraController>();
        mainCamera.Get<Camera>().size = 2.5f;

        const Entity bee = scene.CreateEntity();
        bee.Add<Logic>().AddScript<BeeController>();
        
        const std::string parallaxFolder = "res/Textures/Parallax/";
        
        {
            const Entity background = scene.CreateEntity("Background");
            auto& sprite = background.Add<SpriteRenderer>(parallaxFolder + "Background.png");
            background.Add<Logic>().AddScript<Parallax>();
            auto& transform = background.Get<Transform>();
            transform.scale = { 800, 7, 1};
        }

        {
            const Entity trees = scene.CreateEntity("Trees");
            auto& sprite = trees.Add<SpriteRenderer>(parallaxFolder + "Trees.png");
            auto& parallax = trees.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.4f, 0.0f};
            sprite.orderInLayer = -2;
            auto& transform = trees.Get<Transform>();
            transform.scale = { 30, 10, 1};
            sprite.sprite->uvMultiplier.x = 3;
        }

        {
            const Entity mountains = scene.CreateEntity("Mountains");
            auto& sprite = mountains.Add<SpriteRenderer>(parallaxFolder + "Mountains.png");
            auto& parallax = mountains.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.6f, 0.f};
            sprite.orderInLayer = -1;
            auto& transform = mountains.Get<Transform>();
            transform.scale = { 30, 10, 1};
            sprite.sprite->uvMultiplier.x = 3;
        }

        {
            const Entity platform = scene.CreateEntity("Platform");
            auto& sprite = platform.Add<SpriteRenderer>(parallaxFolder + "Platform.png");
            sprite.sprite->uvMultiplier.x = 30.f;
            sprite.orderInLayer = -3;
            auto& transform = platform.Get<Transform>();
            transform.scale = { 30, 1.5f, 1.5f};
            transform.position += Vector3::down * 2.f;
        }

        {
            const Entity clouds = scene.CreateEntity("Clouds");
            auto& sprite = clouds.Add<SpriteRenderer>(parallaxFolder + "Clouds.png");
            auto& parallax = clouds.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.5f, 0.f};
            sprite.orderInLayer = -1;
            auto& transform = clouds.Get<Transform>();
            transform.scale = { 20, 20, 20};
            transform.position += Vector3::up * 1.5f;
        }
    }
};

SHARD_CREATE(Game)
#endif