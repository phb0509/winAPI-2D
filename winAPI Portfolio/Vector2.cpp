#include "Framework.h"

Vector2::Vector2()
	: x(0), y(0)
{
}

Vector2::Vector2(double x, double y)
	: x(x), y(y)
{

}

double Vector2::Length() const
{
	return sqrt(x * x + y * y);
}

double Vector2::sqrLegnth() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normal() const
{
	double length = Length();
	return Vector2(x / length, y / length);
}

void Vector2::Normalize()
{
	double length = Length();
	x /= length;
	y /= length;
}

double Vector2::Angle() const
{
	return atan2(-y, x);
}

double Vector2::Cross(const Vector2& value)
{
	return x * value.y - y * value.x;
}
