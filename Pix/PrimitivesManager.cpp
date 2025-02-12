#include "PrimitivesManager.h"
#include"Rasterizer.h"
#include "Clipper.h"
#include "MatrixStack.h"
#include "Camera.h"

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
}

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}
void PrimitivesManager::OnNewFrame()
{
	mCullMode = CullMode::Back;
}

void PrimitivesManager::SetCullMode(CullMode mode)
{
	mCullMode = mode;
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
				Matrix4 matNDC = matWorld * matView * matProj;

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
