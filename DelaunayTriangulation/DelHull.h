#pragma once
#include "CycleLinkedList.h"
#include "DLinkedList.h"
#include "DelTri.h"
#include "DelDirectionalEdge.h"

struct NeighbourPair;

class DelHull
{
private:

	void ExpandHull(const DelPoint& point);

	DelTri* CreateHullTriangle(DLinkedList<DelTri>& tempTriangles, const DelPoint& edgeStart, const DelPoint& pointToAdd, const DelPoint& edgeEnd);

	// Returns the beginning of the triangle
	DelDirectionalEdge* CreateTriangle(const DelPoint* point1, const DelPoint* point2, const DelPoint* point3);

	// Returns the beginning of the triangle
	DelDirectionalEdge* CreateHullTriangle(DelDirectionalEdge* baseEdge, const DelPoint* pointToAdd);

	// called at the end of CreateTriangles
	void LinkNeighbours(DelTri*& out_triangleArray);

	void LegalisePair(DLinkedList<NeighbourPair>& neighbourCheckList, NeighbourPair& targetPair);

	CycleList<DelDirectionalEdge*> hull;
	DLinkedList<DelDirectionalEdge> allEdges;
	int triangleCount = 0;
public:
	void Create(DelPoint* pointArray, int pointCount);

	// Fills target array of the size of delHull's triangleCount
	void CreateTriangles(DelTri*& out_triangleArray, int& out_triangleCount);

	int GetTriangleCount()
	{
		return triangleCount;
	}

	void Clear()
	{
		hull.Clear();
		allEdges.Clear();
		triangleCount = 0;
	}
};

struct NeighbourPair
{
	DelDirectionalEdge* baseEdge;
	DelDirectionalEdge* reverseEdge;

	bool FindIsLegal()
	{
		DelDirectionalEdge* baseTriEdges[3] = { baseEdge, baseEdge->next, baseEdge->next->next };
		DelDirectionalEdge* reverseTriEdges[3] = { reverseEdge, reverseEdge->next, reverseEdge->next->next };
		return DelTri::FindIsDelaunayTriangle(*baseTriEdges[0]->start, *baseTriEdges[1]->start, *baseTriEdges[2]->start, *reverseTriEdges[2]->start);
	}

	void FlipTriangles(DLinkedList<NeighbourPair>& neighbourCheckList)
	{
		DelDirectionalEdge* baseTriEdges[3] = { baseEdge, baseEdge->next, baseEdge->next->next };
		DelDirectionalEdge* reverseTriEdges[3] = { reverseEdge, reverseEdge->next, reverseEdge->next->next };

		DelDirectionalEdge* quadEdges[4] = { baseTriEdges[1], baseTriEdges[2], reverseTriEdges[1], reverseTriEdges[2] };

		baseEdge->start = quadEdges[2]->end;
		baseEdge->end = quadEdges[1]->start;

		reverseEdge->start = baseEdge->end;
		reverseEdge->end = baseEdge->start;

		baseEdge->next = quadEdges[1];
		reverseEdge->next = quadEdges[3];

		quadEdges[1]->next = quadEdges[2];
		quadEdges[3]->next = quadEdges[0];

		quadEdges[2]->next = baseEdge;
		quadEdges[0]->next = reverseEdge;

		for (int i = 0; i < 4; i++)
		{
			if (quadEdges[i]->reverse != nullptr)
			{
				neighbourCheckList.PushBack({ quadEdges[i], quadEdges[i]->reverse });
			}
		}
	}
};