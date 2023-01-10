#pragma once
#include "Shard.h"

using namespace Shard;

class MainScript : public SceneScript
{
    SHARD_OBJECT(MainScript, SceneScript)
public:
    Entity bee;
    
    void Start() override
    {
        const std::string parallaxFolder = "res/Textures/Parallax/";

        bee = CreateEntity();
        bee.Add<Logic>().AddScript<BeeController>();
        
        {
            const Entity mainCamera = CameraSystem::GetMainCameraEntity();
            Logic& logic = mainCamera.Add<Logic>();
            logic.AddScript<CameraController>();
            FollowEntity& followEntity = logic.AddScript<FollowEntity>();
            followEntity.target = bee;
            mainCamera.Get<Camera>().size = 2.5f;
        }
        
        {
            const Entity background = CreateEntity("Background");
            background.Add<SpriteRenderer>(parallaxFolder + "Background.png");
            background.Add<Logic>().AddScript<Parallax>();
            auto& transform = background.Get<Transform>();
            transform.scale = { 800, 7, 1};
        }

        {
            const Entity trees = CreateEntity("Trees");
            auto& sprite = trees.Add<SpriteRenderer>(parallaxFolder + "Trees.png");
            auto& parallax = trees.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.4f, 0.0f};
            sprite.orderInLayer = -2;
            auto& transform = trees.Get<Transform>();
            transform.scale = { 30, 10, 1};
            sprite.sprite->uvMultiplier.x = 3;
        }

        {
            const Entity mountains = CreateEntity("Mountains");
            auto& sprite = mountains.Add<SpriteRenderer>(parallaxFolder + "Mountains.png");
            auto& parallax = mountains.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.6f, 0.f};
            sprite.orderInLayer = -1;
            auto& transform = mountains.Get<Transform>();
            transform.scale = { 30, 10, 1};
            sprite.sprite->uvMultiplier.x = 3;
        }

        {
            const Entity platform = CreateEntity("Platform");
            auto& sprite = platform.Add<SpriteRenderer>(parallaxFolder + "Platform.png");
            sprite.sprite->uvMultiplier.x = 30.f;
            sprite.orderInLayer = -3;
            auto& transform = platform.Get<Transform>();
            transform.scale = { 30, 1.5f, 1.5f};
            transform.position += Vector3::down * 2.f;
        }

        {
            const Entity clouds = CreateEntity("Clouds");
            auto& sprite = clouds.Add<SpriteRenderer>(parallaxFolder + "Clouds.png");
            auto& parallax = clouds.Add<Logic>().AddScript<Parallax>();
            parallax.scrollScale = {.5f, .3f};
            sprite.orderInLayer = -1;
            auto& transform = clouds.Get<Transform>();
            transform.scale = { 20, 20, 20};
            transform.position += Vector3::up * 1.5f;
        }    
    }
};
