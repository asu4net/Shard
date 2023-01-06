#pragma once
#ifdef PRACTICE_06

class Game final : public Application 
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 06 - Alejandro :D");
        window.SetBackgroundColor(Color::DarkGray);

        scene.GetMainCameraEntity().Add<Logic>().AddScript<CameraController>();
        
        const std::string parallaxFolder = "res/Textures/Parallax/";
        
        {
            const Entity background = scene.CreateEntity("Background");
            auto& sprite = background.Add<SpriteRenderer>(parallaxFolder + "Background.png");
            auto& transform = background.Get<Transform>();
            transform.scale = { 800, 7, 1};
        }

        {
            const Entity trees = scene.CreateEntity("Trees");
            auto& sprite = trees.Add<SpriteRenderer>(parallaxFolder + "Trees.png");
            sprite.orderInLayer = -2;
            auto& transform = trees.Get<Transform>();
            transform.scale = { 10, 10, 10};
        }

        {
            const Entity mountains = scene.CreateEntity("Mountains");
            auto& sprite = mountains.Add<SpriteRenderer>(parallaxFolder + "Mountains.png");
            sprite.orderInLayer = -1;
            auto& transform = mountains.Get<Transform>();
            transform.scale = { 10, 10, 10};
        }

        {
            const Entity platform = scene.CreateEntity("Platform");
            auto& sprite = platform.Add<SpriteRenderer>(parallaxFolder + "Platform.png");
            sprite.sprite->uvMultiplier = 20.f;
            sprite.orderInLayer = -3;
            auto& transform = platform.Get<Transform>();
            transform.scale = { 3, 3, 3};
            transform.position += Vector3::down * 2.35f;
        }
    }
};

SHARD_CREATE(Game)
#endif