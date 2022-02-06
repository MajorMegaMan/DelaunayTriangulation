#pragma once

struct DelPoint;
struct DelTri;

struct DelDirectionalEdge
{
	const DelPoint* start = nullptr;
	const DelPoint* end = nullptr;

	// the index start will be in the triangle this creates
	// also the index it's neighbour will be
	int index = 0;

	// this will create the shape of the triangle
	DelDirectionalEdge* next = nullptr;

	// this is a shapes neighbour for this edge
	DelDirectionalEdge* reverse = nullptr;

	DelTri* createdTriangle = nullptr;
	bool processedTriangle = false;

	DelDirectionalEdge() {}
	DelDirectionalEdge(const DelPoint* start, const DelPoint* end, int index);

	bool PointOnRightSide(const DelPoint& point) const;

	bool CheckReverse(const DelDirectionalEdge& other) const;
	void ConnectReverse(DelDirectionalEdge* other);

	void LinkNeighbourInCreatedTri();

	static DelTri CreateTriangle(DelDirectionalEdge* triangleStart);
	static void AttachTriangle(DelDirectionalEdge* triangleStart, DelTri* createdTriangle);
};