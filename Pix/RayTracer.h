#pragma once

#include "MathHelper.h"
#include <XEngine.h>

class RayTracer
{
public:
    static RayTracer* Get();

    void OnNewFrame();
    bool BeginDraw();
    bool EndDraw();

    void AddObject(const Sphere& sphere, const X::Color& color, float ri);
    void AddLight (const Vector3& position, const X::Color& color);

private:
    X::Color Trace(const Ray& ray, int depth);

    struct Object
    {
        Sphere sphere;
        X::Color color;
        float refractionIndex = 0.0f;

        bool IsOpaque() const
        {
            return MathHelper::IsEqual(refractionIndex, 0.0f);
        }
    };

    struct Light
    {
        Vector3 position;
        X::Color color;
        float attenC = 1.0f, attenL = 0.0f, attenQ = 0.0f;
    };

    std::vector<Object> mObjects;
    std::vector<Light> mLights;
    float mAmbient = 0.0f;
};

