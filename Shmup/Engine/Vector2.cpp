#include "Vector2.h"


Vector2::Vector2()
{
	x = 0;
	y = 0;
}


Vector2::Vector2(float a, float b)
{
	x = a;
	y = b;
}


Vector2 Vector2::operator+(const Vector2& a) const
{
	Vector2 v;

	v.x = x + a.x;
	v.y = y + a.y;

	return v;
}


Vector2 Vector2::operator-(const Vector2& a) const
{
	Vector2 v;

	v.x = x - a.x;
	v.y = y - a.y;

	return v;
}


Vector2 Vector2::operator*(float s) const
{
	Vector2 v;

	v.x = x * s;
	v.y = y * s;

	return v;
}


Vector2 Vector2::operator/(float s) const
{
	Vector2 v;

	v.x = x / s;
	v.y = y / s;

	return v;
}


float Vector2::LengthSqr() const
{
	return x * x + y * y;
}


float Vector2::Length() const
{
	return sqrtf(LengthSqr());
}


Vector2 Vector2::Normalized() const
{
	return *this / Length();
}


float Vector2::Dot(const Vector2& v) const
{
	return x * v.x + y * v.y;
}