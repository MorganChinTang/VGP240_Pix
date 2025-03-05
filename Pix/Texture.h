#pragma once
#include "XEngine.h"

enum class AddressMode
{
    Border,
    Clamp,
    Wrap,
    Mirror
};

class Texture
{
public:
    void Load(const std::string& fileName);
    const std::string& GetFileName() const;
    X::Color GetPixel(float u, float v, bool filter, AddressMode addressMode) const;

    int GetWidth() const;
    int GetHeight() const;
    //texel coords
    X::Color GetPixel(int u, int v) const;

private:
    std::string mFileName;
    std::unique_ptr<X::Color[]> mPixels;
    int mWidth = 0;
	int mHeight = 0;
    bool filter = false;

};

