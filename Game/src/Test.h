#pragma once
#ifdef TEST

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        const Entity circle = scene.CreateEntity();
        circle.Add<CircleRenderer>(Color::LightRed);
        circle.Get<Transform>().position += Vector3::right * 3;
        
        // auto& a = scene.CreateEntity("A").Add<SpriteRenderer>("res/Textures/fire.png");
        // auto& b = scene.CreateEntity("B").Add<SpriteRenderer>("res/Textures/wall.jpg");
        //
        // a.orderInLayer = 0;
        // b.orderInLayer = 1;
        
        const Entity textEntity = scene.CreateEntity("Test Text");
        auto& textRenderer = textEntity.Add<TextRenderer>("Hello world", Color::LightBlue, "res/Fonts/transformers.ttf");
        textEntity.Get<Transform>().position += Vector3::left * 2.f;
    }
};

SHARD_CREATE(Game)
#endif