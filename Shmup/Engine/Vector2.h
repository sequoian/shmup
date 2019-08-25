#pragma once

#include <math.h>


class Vector2
{
public:
	// constructors
	Vector2();
	Vector2(float x, float y);

	// operator overloads
	Vector2 operator+(const Vector2& a) const;
	Vector2 operator-(const Vector2& a) const;
	Vector2 operator*(float s) const;
	Vector2 operator/(float s) const;

	float Length() const;
	float LengthSqr() const;
	Vector2 Normalized() const;
	float Dot(const Vector2& v) const;

public:
	float x, y;
};