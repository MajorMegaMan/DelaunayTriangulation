#include "pch.h"
#include "DelTri.h"

DelTri::DelTri()
{
	for (int i = 0; i < 3; i++)
	{
		vertices[i] = nullptr;
		neighbours[i] = nullptr;
	}
}

void DelTri::SetDelPoints(const DelPoint& a, const DelPoint& b, const DelPoint& c)
{
	vertices[0] = &a;
	vertices[1] = &b;
	vertices[2] = &c;
}

const DelPoint* DelTri::GetPoint(int index) const
{
	return vertices[index];
}

Vector2 DelTri::CalcCircumcentre() const
{
	const DelPoint* a = vertices[0];
	const DelPoint* b = vertices[1];
	const DelPoint* c = vertices[2];

	Vector2 aTob = *b - *a;
	Vector2 aToc = *c - *a;

	Vector2 dir1 = aTob / 2.0f;
	Vector2 dir2 = aToc / 2.0f;

	Vector2 point1 = *a + dir1;
	Vector2 point2 = *a + dir2;

	dir1 = Vector2::GetPerpindicular(dir1);
	dir2 = Vector2::GetPerpindicular(dir2);

	return Vector2::LineIntersection(point1, dir1, point2, dir2);
}

// returns true if winding order is clockwise
bool DelTri::FindWindingOrder() const
{
	return Vector2::PointIsRightOfLine(*vertices[0], *vertices[1], *vertices[2]);
}

bool DelTri::FindIsDelaunayTriangle(const Vector2& pointD) const
{
	Vector3 aFancy = GetFancyNumberThing(*vertices[0], pointD);
	Vector3 bFancy = GetFancyNumberThing(*vertices[1], pointD);
	Vector3 cFancy = GetFancyNumberThing(*vertices[2], pointD);

	// Find determinant
	float aPart = aFancy.x * (bFancy.y * cFancy.z - bFancy.z * cFancy.y);
	float bPart = aFancy.y * (bFancy.x * cFancy.z - bFancy.z * cFancy.x);
	float cPart = aFancy.z * (bFancy.x * cFancy.y - bFancy.y * cFancy.x);

	float determinant = aPart - bPart + cPart;

	bool isClockwise = FindWindingOrder();

	if (isClockwise)
	{
		return determinant > 0;
	}
	else
	{
		return determinant < 0;
	}
}

Vector3 DelTri::GetFancyNumberThing(const Vector2& triPoint, const Vector2& pointD)
{
	Vector3 result;
	result.x = triPoint.x - pointD.x;
	result.y = triPoint.y - pointD.y;
	result.z = result.x * result.x + result.y * result.y;

	return result;
}

bool DelTri::FindIsDelaunayTriangle(const Vector2& triPoint1, const Vector2& triPoint2, const Vector2& triPoint3, const Vector2& pointD)
{
	Vector3 aFancy = GetFancyNumberThing(triPoint1, pointD);
	Vector3 bFancy = GetFancyNumberThing(triPoint2, pointD);
	Vector3 cFancy = GetFancyNumberThing(triPoint3, pointD);

	// Find determinant
	float aPart = aFancy.x * (bFancy.y * cFancy.z - bFancy.z * cFancy.y);
	float bPart = aFancy.y * (bFancy.x * cFancy.z - bFancy.z * cFancy.x);
	float cPart = aFancy.z * (bFancy.x * cFancy.y - bFancy.y * cFancy.x);

	float determinant = aPart - bPart + cPart;

	// triangle points must be counter clockwise direction
	return determinant < 0;
}

// returns true if winding order is clockwise
bool DelTri::FindWindingOrder(const Vector2& triPoint1, const Vector2& triPoint2, const Vector2& triPoint3)
{
	return Vector2::PointIsRightOfLine(triPoint1, triPoint2, triPoint3);
}
