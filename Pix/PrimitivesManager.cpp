#include "PrimitivesManager.h"
#include"Rasterizer.h"

PrimitivesManager* PrimitivesManager::Get()
{
	static PrimitivesManager sInstance;
	return &sInstance;
}
//PrimitivesManager::PrimitivesManager()
//{
//
//}

bool PrimitivesManager::BeginDraw(Topology topology)
{
	mTopology= topology;
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
			Rasterizer::Get()->DrawPoint(mVertexBuffer[i]);
		}
	}
	break;
	case Topology::Line:
		//Rasterizer::Get()->DrawLine(mVertexBuffer);
		break;
	case Topology::Triangle:
		//Rasterizer::Get()->DrawTriangle(mVertexBuffer);
		break;
	default:
		break;
	}

	mBeginDraw = false;
	return true;
}
