#pragma once
#include "Vertex.h"

enum class Topology
{
	Point,
	Line,
	Triangle
};
class PrimitivesManager
{
public:
	static PrimitivesManager* Get();




	bool BeginDraw(Topology topology, bool applyTransform = false);
	void AddVertex(const Vertex& vertex);
	bool EndDraw();


private:
	PrimitivesManager() {};
	std::vector<Vertex> mVertexBuffer;
	Topology mTopology=Topology::Point;
	bool mBeginDraw = false;
	bool mApplyTransform = false;

};

