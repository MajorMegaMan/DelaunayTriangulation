#include "pch.h"
#include "DelHull.h"

void DelHull::ExpandHull(const DelPoint& point)
{
	DLinkedList<NeighbourPair> neighbourChecks;
	// Test point against hull faces
	auto hullFaceNode = hull.head;
	do
	{
		auto nextNode = hullFaceNode->next;
		auto baseEdge = hullFaceNode->value;
		if (baseEdge->PointOnRightSide(point))
		{
			//DelTri* hullTriangle = CreateHullTriangle(tempTriangles, *baseEdge->start, point, *baseEdge->end);

			auto edgePtrA = CreateHullTriangle(baseEdge, &point);
			auto edgePtrB = edgePtrA->next;
			auto edgePtrC = edgePtrB->next;

			if (edgePtrA->CheckReverse(*hullFaceNode->prev->value))
			{
				// are equal
				// existing edge needs to be removed
				edgePtrA->ConnectReverse(hullFaceNode->prev->value);
				neighbourChecks.PushBack({ edgePtrA, hullFaceNode->prev->value });
				hull.RemoveNode(hullFaceNode->prev);

				// new edge is added to hull
				hull.InsertAfter(edgePtrB, hullFaceNode);
			}
			else
			{
				// both new edges are added to hull
				hull.InsertAfter(edgePtrA, hullFaceNode);
				hull.InsertAfter(edgePtrB, hullFaceNode->next);
			}

			// hull base needs to be removed
			edgePtrC->ConnectReverse(hullFaceNode->value);
			neighbourChecks.PushBack({ edgePtrC, hullFaceNode->value });
			hull.RemoveNode(hullFaceNode);
		}
		hullFaceNode = nextNode;

	} while (hullFaceNode != hull.head);

	// legalise triangles
	auto neighbourCheckNode = neighbourChecks.head;
	while (neighbourCheckNode != nullptr)
	{
		// legalise pair
		LegalisePair(neighbourChecks, neighbourCheckNode->value);
		neighbourChecks.RemoveNode(neighbourCheckNode);
		neighbourCheckNode = neighbourChecks.head;
	}
}

void DelHull::LegalisePair(DLinkedList<NeighbourPair>& neighbourCheckList, NeighbourPair& neighbour)
{
	if (!neighbour.FindIsLegal())
	{
		// neighbour is not legal

		// need to flip triangles
		neighbour.FlipTriangles(neighbourCheckList);
		// add neighbours to checkList

	}
}

DelTri* DelHull::CreateHullTriangle(DLinkedList<DelTri>& tempTriangles, const DelPoint& edgeStart, const DelPoint& pointToAdd, const DelPoint& edgeEnd)
{
	DelTri hullTriangle;
	hullTriangle.SetDelPoints(edgeStart, pointToAdd, edgeEnd);
	tempTriangles.PushBack(hullTriangle);
	return &(tempTriangles.tail->value);
}

DelDirectionalEdge* DelHull::CreateTriangle(const DelPoint* point1, const DelPoint* point2, const DelPoint* point3)
{
	DelDirectionalEdge a(point1, point2, 0);
	DelDirectionalEdge b(point2, point3, 1);
	DelDirectionalEdge c(point3, point1, 2);

	DelDirectionalEdge* edgePtrA = allEdges.PushBack(a);
	DelDirectionalEdge* edgePtrB = allEdges.PushBack(b);
	DelDirectionalEdge* edgePtrC = allEdges.PushBack(c);

	edgePtrA->next = edgePtrB;
	edgePtrB->next = edgePtrC;
	edgePtrC->next = edgePtrA;

	triangleCount++;

	return edgePtrA;
}

DelDirectionalEdge* DelHull::CreateHullTriangle(DelDirectionalEdge* baseEdge, const DelPoint* pointToAdd)
{
	return CreateTriangle(baseEdge->start, pointToAdd, baseEdge->end);
}

void DelHull::Create(DelPoint* pointArray, int pointCount)
{
	Clear();

	// Create first Triangle from first three points
	DelDirectionalEdge* begin;
	if (!DelTri::FindWindingOrder(pointArray[0], pointArray[1], pointArray[2]))
	{
		// This is counter clockwise, no need to do anything
		begin = CreateTriangle(&pointArray[0], &pointArray[1], &pointArray[2]);
	}
	else
	{
		// This is clockwise, need to switch points
		begin = CreateTriangle(&pointArray[0], &pointArray[2], &pointArray[1]);
	}

	// initalise hull with the triangle edges
	hull.PushBack(begin);
	hull.PushBack(begin->next);
	hull.PushBack(begin->next->next);

	// add a point and the triangles that are made
	for (int i = 3; i < pointCount; i++)
	{
		ExpandHull(pointArray[i]);
	}
}

void DelHull::CreateTriangles(DelTri*& out_triangleArray, int& out_triangleCount)
{
	//out_triangleArray = new DelTri[triangleCount];
	out_triangleCount = triangleCount;
	int current = 0;
	auto edgeNode = allEdges.head;
	while (edgeNode != nullptr)
	{
		if (!edgeNode->value.processedTriangle)
		{
			out_triangleArray[current] = DelDirectionalEdge::CreateTriangle(&edgeNode->value);
			DelDirectionalEdge::AttachTriangle(&edgeNode->value, &out_triangleArray[current]);
			out_triangleArray[current].index = current;
			current++;
		}
		edgeNode = edgeNode->next;
	}

	LinkNeighbours(out_triangleArray);
}

void DelHull::LinkNeighbours(DelTri*& out_triangleArray)
{
	int current = 0;
	auto edgeNode = allEdges.head;
	while (edgeNode != nullptr)
	{
		edgeNode->value.LinkNeighbourInCreatedTri();
		current++;
		edgeNode = edgeNode->next;
	}
}