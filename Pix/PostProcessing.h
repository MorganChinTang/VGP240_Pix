#pragma once
#include "RenderTarget.h"
#include "PostProcessing.h"
enum class EffectType 
{
    None,
    MonoChrome,
    Invert,
    Mirror, 
    Blur,
    ColorMaskR,
    ColorMaskG,
    ColorMaskB,
    Sepia,
    Wave,
    FishEye
};

class PostProcessing final
{
public:
    static PostProcessing* Get();

    void Initialize(int width, int height, const X::Color& clearColor = X::Colors::Black);
    void OnNewFrame();
    void SetEffectType(EffectType effectType);
    void BeginDraw();
    bool Draw(int x, int y, const X::Color& color);
    void EndDraw();

private:
    bool mDrawBegin = false;
    void DrawPixel(int x, int y);
    X::Color mClearColor = X::Colors::Black;
    RenderTarget mRenderTarget;
    EffectType mEffectType = EffectType::None;
};

