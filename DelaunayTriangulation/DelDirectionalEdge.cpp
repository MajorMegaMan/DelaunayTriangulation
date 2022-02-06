#include "pch.h"
#include "DelDirectionalEdge.h"
#include "DelTri.h"

DelDirectionalEdge::DelDirectionalEdge(const DelPoint* start, const DelPoint* end, int index)
{
	this->start = start;
	this->end = end;
	this->index = index;
}

bool DelDirectionalEdge::PointOnRightSide(const DelPoint& point) const
{
	return Vector2::PointIsRightOfLine(*start, *end, point);
}

bool DelDirectionalEdge::CheckReverse(const DelDirectionalEdge& other) const
{
	return (start == other.end && end == other.start);
}

void DelDirectionalEdge::ConnectReverse(DelDirectionalEdge* other)
{
	reverse = other;
	other->reverse = this;
}

void DelDirectionalEdge::LinkNeighbourInCreatedTri()
{
	if (reverse != nullptr)
	{
		createdTriangle->neighbours[index] = reverse->createdTriangle;
	}
}

DelTri DelDirectionalEdge::CreateTriangle(DelDirectionalEdge* triangleStart)
{
	DelDirectionalEdge* edges[3] = { triangleStart, triangleStart->next, triangleStart->next->next };

	DelTri triangle;
	triangle.SetDelPoints(*edges[0]->start, *edges[1]->start, *edges[2]->start);

	for (int i = 0; i < 3; i++)
	{
		edges[i]->processedTriangle = true;
		edges[i]->index = i;
	}

	return triangle;
}

void DelDirectionalEdge::AttachTriangle(DelDirectionalEdge* triangleStart, DelTri* createdTriangle)
{
	DelDirectionalEdge* edges[3] = { triangleStart, triangleStart->next, triangleStart->next->next };
	for (int i = 0; i < 3; i++)
	{
		edges[i]->createdTriangle = createdTriangle;
	}
}
