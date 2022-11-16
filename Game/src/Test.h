#pragma once
#ifdef TEST

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        const Entity circle = scene.CreateEntity();
        circle.Add<CircleRenderer>(Color::LightRed);
        circle.Get<Transform>().position += Vector3::right * 3;
        
        auto& a = scene.CreateEntity("A").Add<SpriteRenderer>("res/Textures/fire.png");
        auto& b = scene.CreateEntity("B").Add<SpriteRenderer>("res/Textures/wall.jpg");
        
        a.orderInLayer = 0;
        b.orderInLayer = 1;
    }
};

SHARD_CREATE(Game)
#endif