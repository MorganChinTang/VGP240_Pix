#include "TextureManager.h"

TextureManager* TextureManager::Get()
{
    static TextureManager sInstance;
    return &sInstance;
}

void TextureManager::Clear()
{
    mTextures.clear();
    mCurrentTexture = nullptr;
}
void TextureManager::SetTexture(const std::string& fileName)
{
    auto inter = std::find_if(mTextures.begin(), mTextures.end(),
        [fileName](auto& texture)
        {
            return texture->GetFileName() == fileName;
        });
    if (inter != mTextures.end())
    {
        mCurrentTexture = inter->get();
    }
    else
    {
        auto& texture = mTextures.emplace_back(std::make_unique<Texture>());
        texture->Load(fileName);
        mCurrentTexture = texture.get();
    }
}

X::Color TextureManager::SampleColor(const X::Color& uv) const
{
    X::Color color = uv;
    if(mCurrentTexture != nullptr)
    {
        float u = uv.x;
        float v = uv.y;
        color = mCurrentTexture->GetPixel(u, v);
    }
    return color;
}