#pragma once

struct Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator*(float scalar) const;
	Vector2 operator/(float scalar) const;

	static Vector2 GetPerpindicular(const Vector2& vector);
	static Vector2 LineIntersection(const Vector2& p1, const Vector2& d1, const Vector2& p2, const Vector2& d2);

	static bool PointIsRightOfLine(const Vector2& lineStart, const Vector2& lineEnd, const Vector2& point);

	// returns -1 if evaluation is less than other
	// returns 1 if evaluation is greater than other
	// returns 0 if equal
	// compares x values, if x is equal compares y values
	int SortDirection(const Vector2& other) const;
};