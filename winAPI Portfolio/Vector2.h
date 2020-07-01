#pragma once

class Vector2
{
public:
	Vector2();
	Vector2(double x, double y);

	double Length() const;
	double sqrLegnth() const;
	Vector2 Normal() const;
	void Normalize();

	double Angle() const;

	double Cross(const Vector2& value);

	Vector2 operator+(const Vector2& value) const
	{
		return Vector2(x + value.x, y + value.y);
	}
	Vector2 operator-(const Vector2& value) const
	{
		return Vector2(x - value.x, y - value.y);
	}
	Vector2 operator*(const Vector2& value) const
	{
		return Vector2(x * value.x, y * value.y);
	}
	Vector2 operator/(const Vector2& value) const
	{
		return Vector2(x / value.x, y / value.y);
	}

	Vector2 operator+(const double& value) const
	{
		return Vector2(x + value, y + value);
	}
	Vector2 operator-(const double& value) const
	{
		return Vector2(x - value, y - value);
	}
	Vector2 operator*(const double& value) const
	{
		return Vector2(x * value, y * value);
	}
	Vector2 operator/(const double& value) const
	{
		return Vector2(x / value, y / value);
	}

	void operator+=(const Vector2& value)
	{
		x += value.x;
		y += value.y;
	}
	void operator-=(const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
	}
	void operator*=(const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
	}
	void operator/=(const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
	}

	double x;
	double y;
};