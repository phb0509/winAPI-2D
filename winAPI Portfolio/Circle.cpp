#include "Framework.h"

Circle::Circle()
	: center(0, 0), radius(0)
{
}

Circle::Circle(Vector2 center, double radius)
	: center(center), radius(radius)
{
}

Circle::~Circle()
{
}

void Circle::Render(HDC hdc)
{
	if (!isActive)
		return;

	Ellipse(hdc,
		int(center.x - radius),//Left
		int(center.y - radius),//Top
		int(center.x + radius),//Right
		int(center.y + radius)//Bottom
	);
}

bool Circle::Collision(Vector2 pos)
{
	double x = center.x - pos.x;
	double y = center.y - pos.y;

	double distance = sqrt(x * x + y * y);

	if (radius > distance)
		return true;

	return false;
}

bool Circle::Collision(Circle* circle)
{
	double x = center.x - circle->center.x;
	double y = center.y - circle->center.y;

	double distance = sqrt(x * x + y * y);

	if (radius + circle->radius > distance)
		return true;

	return false;
}

bool Circle::Collision(Rect* rect)
{
	return rect->Collision(this);
}

void Circle::Set(Vector2 center, double radius)
{
	this->center = center;
	this->radius = radius;
}
