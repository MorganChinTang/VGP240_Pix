#pragma once
#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};

enum class CullMode
{
	None,
	Back,
	Front
};
class PrimitivesManager
{
public:
	static PrimitivesManager* Get();

	void OnNewFrame();
	void SetCullMode(CullMode mode);
	void SetCorrectUV(bool correctUV);

	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(const Vertex& vertex);
	bool EndDraw();


private:
	PrimitivesManager() {};

	std::vector<Vertex> mVertexBuffer;
	Topology mTopology=Topology::Point;

	CullMode mCullMode=CullMode::Back;

	bool mBeginDraw = false;
	bool mApplyTransform = false;
	bool mCorrectUV = false;
};

