#pragma once
#include "Vector2.h"

struct Vector3
{
public:
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	Vector3() {}
	Vector3(float x, float y, float z);
	Vector3(const Vector2& vector2);

	Vector3 operator+(const Vector3& other) const;
	Vector3 operator-(const Vector3& other) const;
	Vector3 operator*(float scalar) const;
	Vector3 operator/(float scalar) const;
};