#include "pch.h"
#include "Vector2.h"

Vector2 Vector2::operator+(const Vector2& other) const
{
	return { x + other.x, y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return { x - other.x, y - other.y };
}

Vector2 Vector2::operator*(float scalar) const
{
	return { x * scalar, y * scalar };
}

Vector2 Vector2::operator/(float scalar) const
{
	return { x / scalar, y / scalar };
}

Vector2 Vector2::GetPerpindicular(const Vector2& vector)
{
	return { vector.y, -vector.x };
}

Vector2 Vector2::LineIntersection(const Vector2& p1, const Vector2& d1, const Vector2& p2, const Vector2& d2)
{
	float t2 = (d1.x * p2.y - d1.x * p1.y - d1.y * p2.x + d1.y * p1.x) / (d1.y * d2.x - d1.x * d2.y);
	return p2 + (d2 * t2);
}

bool Vector2::PointIsRightOfLine(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point)
{
	float v = (point.x - lineStart.x) * (lineEnd.y - lineStart.y) - (lineEnd.x - lineStart.x) * (point.y - lineStart.y);
	return v > 0;
	return false;
}

int Vector2::SortDirection(const Vector2& other) const
{
	if (x < other.x)
	{
		return -1;
	}
	else if (x > other.x)
	{
		return 1;
	}
	else if (y < other.y)
	{
		return -1;
	}
	else if (y > other.y)
	{
		return 1;
	}
	return 0;
}
