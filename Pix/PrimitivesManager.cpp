#include "PrimitivesManager.h"
#include"Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "LightManager.h"
extern float gResolutionX;
extern float gResolutionY;

namespace
{
    Matrix4 GetScreenTransform()
    {
        float hw = gResolutionX * 0.5f;
        float hh = gResolutionY * 0.5f;
        return Matrix4
        (
              hw, 0.0f, 0.0f, 0.0f,
            0.0f,  -hh, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
              hw,   hh, 0.0f, 1.0f
        );
    }

    bool CullTriangle(CullMode mode, const std::vector<Vertex>& triangleInNDC)
    {
        if (mode == CullMode::None)
        {
            return false;
        }

        Vector3 abDir = triangleInNDC[1].pos - triangleInNDC[0].pos;
        Vector3 bcDir = triangleInNDC[2].pos - triangleInNDC[0].pos;
        Vector3 faceNormNDC = MathHelper::Normalize(MathHelper::Cross(abDir, bcDir));

        if (mode == CullMode::Back)
        {
            return faceNormNDC.z > 0.0f;
        }

        if (mode == CullMode::Front)
        {
            return faceNormNDC.z < 0.0f;
        }

        return false;
    }

    Vector3 CreateFaceNormal(const std::vector<Vertex>& triangle)
    {
        Vector3 abDir=triangle[1].pos-triangle[0].pos;
		Vector3 acDir=triangle[2].pos-triangle[0].pos;
        Vector3 faceNormal = MathHelper::Normalize(MathHelper::Cross(abDir, acDir));
        return faceNormal;
    }
}

PrimitivesManager* PrimitivesManager::Get()
{
    static PrimitivesManager sInstance;
    return &sInstance;
}
void PrimitivesManager::OnNewFrame()
{
    mCullMode = CullMode::Back;
    mCorrectUV= false;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
    mCullMode = mode;
}

void PrimitivesManager::SetCorrectUV(bool correctUV)
{
    mCorrectUV = correctUV;
}

//PrimitivesManager::PrimitivesManager()
//{
//
//}

bool PrimitivesManager::BeginDraw(Topology topology, bool applyTransform)
{
    mTopology= topology;
    mApplyTransform = applyTransform;
    mBeginDraw = true;
    mVertexBuffer.clear();
    return true;
}
void PrimitivesManager::AddVertex(const Vertex& vertex)
{
    if(mBeginDraw)
        mVertexBuffer.push_back(vertex);
}
bool PrimitivesManager::EndDraw()
{
    if(!mBeginDraw)
        return false;

    

    switch(mTopology)
    {
    case Topology::Point:
    {
        for(size_t i = 0; i < mVertexBuffer.size(); i++)
        {
            if (!Clipper::Get()->ClipPoint(mVertexBuffer[i]))
            {
                Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
            }
        }
    }
    break;

    case Topology::Line:
    {
        for (size_t i = 1; i < mVertexBuffer.size(); i += 2)
        {
            if (!Clipper::Get()->ClipLine(mVertexBuffer[i - 1], (mVertexBuffer[i])))
            {
                Rasterizer::Get()->DrawLine(mVertexBuffer[i - 1], mVertexBuffer[i]);
            }
        }

    }
        break;

    case Topology::Triangle:
    {
        for (size_t i = 2; i < mVertexBuffer.size(); i += 3)
        {
            std::vector<Vertex>triangle = { mVertexBuffer[i - 2], mVertexBuffer[i - 1], mVertexBuffer[i] };
            
            if (mApplyTransform)
            {
                Matrix4 matWorld = MatrixStack::Get()->GetTransform();
                Matrix4 matView = Camera::Get()->GetViewMatrix();
                Matrix4 matProj = Camera::Get()->GetProjectionMatrix();
                Matrix4 matScreen = GetScreenTransform();
                Matrix4 matNDC = matView * matProj;
                ShadeMode shadeMode= Rasterizer::Get()->GetShadeMode();

                //transform position into world space
                for (size_t t=0;t<triangle.size();t++)
                {
                    triangle[t].pos = MathHelper::Transformcoord(triangle[t].pos, matWorld);
                    triangle[t].posWorld = triangle[t].pos;
                }

                //if we dont have a normal, add one
                if (MathHelper::IsEqual(MathHelper::MagnitudeSquared(triangle[0].norm), 0.0f))
                {
                    Vector3 faceNormal=CreateFaceNormal(triangle);
                    for (size_t t = 0; t < triangle.size(); t++)
                    {
                        triangle[t].norm = faceNormal;
                    }
                }
                //if we have, transform into world space
                else
                {
                    for(size_t t = 0; t < triangle.size(); t++)
					{
						triangle[t].norm = MathHelper::TransformNormal(triangle[t].norm, matWorld);
					}
                }

                //if color are UVs (z < 0.0f) do not apply flat or gouaud lighting
                //color is not a valid color
                if (triangle[0].color.z >= 0.0f)
                {

                    //apply light to vertices
                    //Lighting needs to be calculated in World Space (vertex lighting is in world space)

                    if (shadeMode == ShadeMode::Flat)
                    {
                        triangle[0].color *= LightManager::Get()->ComputeLightColor(triangle[0].pos, triangle[0].norm);
                        triangle[1].color = triangle[0].color;
                        triangle[2].color = triangle[0].color;

                    }
                    else if (shadeMode == ShadeMode::Gouraud)
                    {
                        for (size_t t = 0; t < triangle.size(); t++)
                        {
                            triangle[t].color *= LightManager::Get()->ComputeLightColor(triangle[t].pos, triangle[t].norm);
                        }
                    }
                }
                else if (mCorrectUV)
                {
                    //apply perspective uv correction in view space
                    for (size_t t = 0; t < triangle.size(); t++)
                    {
                        Vector3 viewSpacePos=MathHelper::Transformcoord(triangle[t].posWorld, matView);  
                        triangle[t].color.x /= viewSpacePos.z;
                        triangle[t].color.y /= viewSpacePos.z;
                        triangle[t].color.w /= viewSpacePos.z;
                    }
                }

                //transform position into NDC space
                for(size_t t=0;t<triangle.size();t++)
                {
                    triangle[t].pos = MathHelper::Transformcoord(triangle[t].pos, matNDC);

                }

                //check if the triangle should be culled in NDC space
                if (CullTriangle(mCullMode, triangle))
                {
                    continue;
                }

                //transform from NDC space to screen space
                for (size_t t = 0; t < triangle.size(); t++)
                {
                    triangle[t].pos = MathHelper::Transformcoord(triangle[t].pos, matScreen);
                    MathHelper::FlattenVectorScreenCoords(triangle[t].pos);
                }

            }

            if (!Clipper::Get()->ClipTriangle(triangle))
            {
                for (size_t v = 2; v < triangle.size(); ++v)
                {
                    Rasterizer::Get()->DrawTriangle(triangle[0], triangle[v - 1], triangle[v]);
                }
            }
        }
    }
        break;

    default:
        break;
    }

    mBeginDraw = false;
    return true;
}
