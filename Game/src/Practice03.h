#pragma once
#ifdef PRACTICE_03

class Game final : public Application
{
    void OnRenderReady(RenderReadyArgs args) override
    {
        window.SetTitle("Practice 03 - Alejandro :D");
        scene.GetMainCameraEntity().Get<Camera>().size = 5.f;
        
        //Text rendering
        {
            const Entity textEntity = scene.CreateEntity("Test Text");
            auto& textRenderer = textEntity.Add<TextRenderer>("Hello world", Color::LightBlue, "res/Fonts/transformers.ttf");
            textEntity.Get<Transform>().position += Vector3::left * 2.f;
        }
        
        //Font sprite
        {
            const Entity fontEntity = scene.CreateEntity();

            auto& spriteRend = fontEntity.Add<SpriteRenderer>();
            spriteRend.color = Color::LightRed;

            auto& transform = fontEntity.Get<Transform>();
            const Font font{"res/Fonts/transformers.ttf"};
            spriteRend.sprite->AddTexture(font.GetPixelsRgb());
            transform.position += {-1, -1, 0};
            transform.scale = Vector2::one * 10.f;
        }
        
    }
};
SHARD_CREATE(Game)
#endif