#pragma once
#ifdef PRACTICE_03

class Game final : public Application
{
    float cameraSize = 7.f;
    Font font{&window, "res/Fonts/transformers.ttf"};
    Quad fontQuad;
    Text text;
        
    void OnRenderReady(RenderReadyArgs args) override
    {
        text = Text(&font, "[Buenas] paco", Color::LightBlue);
        text.SetContent("[Buenas] paco");
        StaticCamera::window = &window;
        StaticCamera::size = cameraSize;
        window.SetTitle("Practice 03 - Alejandro :D");
            
        fontQuad.AddTexture(font.GetPixelsRgb());
        fontQuad.position = fontQuad.position + Vector2::right * -6.f;
        fontQuad.color = Color::LightRed;
        fontQuad.scale = Vector2::one * 10.f;
    }

    void OnRenderFrame(RenderFrameArgs args) override
    {
        text.Draw();
        fontQuad.Draw();
        StaticCamera::CalculateMatrices();
    }
};
SHARD_CREATE(Game)
#endif