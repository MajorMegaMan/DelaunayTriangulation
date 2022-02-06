#pragma once
#include "DelPoint.h"

struct DelTri
{
private:
	const DelPoint* vertices[3];

public:
	DelTri* neighbours[3];

	int index = 0;

	DelTri();

	void SetDelPoints(const DelPoint& a, const DelPoint& b, const DelPoint& c);

	const DelPoint* GetPoint(int index) const;

	Vector2 CalcCircumcentre() const;
	bool FindWindingOrder() const;

	bool FindIsDelaunayTriangle(const Vector2& pointD) const;
	static Vector3 GetFancyNumberThing(const Vector2& triPoint, const Vector2& pointD);

	// Static Functions

	// Checks if it is a delaunay triangle.
	// triangle points must be counter clockwise direction
	static bool FindIsDelaunayTriangle(const Vector2& triPoint1, const Vector2& triPoint2, const Vector2& triPoint3, const Vector2& pointD);

	// Returns true if the winding order of these points are clockwise
	static bool FindWindingOrder(const Vector2& triPoint1, const Vector2& triPoint2, const Vector2& triPoint3);
};
