#include "Framework.h"

Rect::Rect()
	: center(0, 0), size(0, 0)
{
}

Rect::Rect(Vector2 center, Vector2 size)
	: center(center), size(size)
{
}

Rect::Rect(double left, double top, double right, double bottom)
{
	SetRect(left, top, right, bottom);
}

Rect::~Rect()
{
}

void Rect::Render(HDC hdc)
{
	Rectangle(hdc,
		(int)Left(),
		(int)Top(),
		(int)Right(),
		(int)Bottom()
	);
}

bool Rect::Collision(Vector2 pos)
{
	if (pos.x > Left() && pos.x < Right())
	{
		if (pos.y > Top() && pos.y < Bottom())
		{
			return true;
		}
	}

	return false;
}

void Rect::Set(Vector2 center, double radius)
{
	this->center = center;
	size = { radius, radius };
}

bool Rect::Collision(Circle* circle)
{
	//원이 네모의 상하좌우에 위치한 경우
	if ((circle->center.x > Left() && circle->center.x < Right()) ||
		(circle->center.y > Top() && circle->center.y < Bottom()))
	{
		Vector2 size = { circle->radius * 2, circle->radius * 2 };
		Rect temp(circle->center, size);

		if (Collision(&temp))
			return true;
	}
	else//대각선에 위치한 경우
	{
		Vector2 edges[4];
		edges[0] = { Left(), Top() };
		edges[1] = { Right(), Top() };
		edges[2] = { Left(), Bottom() };
		edges[3] = { Right(), Bottom() };

		for (Vector2 edge : edges)
			if (circle->Collision(edge))
				return true;
	}

	return false;
}

bool Rect::Collision(Rect* rect)
{
	if (rect->Left() < Right() && rect->Right() > Left())
	{
		if (rect->Top() < Bottom() && rect->Bottom() > Top())
			return true;
	}

	return false;
}

bool Rect::Collision(OUT Rect* overlap, IN Rect* rect)
{
	double left = max(rect->Left(), Left());
	double right = min(rect->Right(), Right());

	double top = max(rect->Top(), Top());
	double bottom = min(rect->Bottom(), Bottom());

	if (right - left > 0 && bottom - top > 0)
	{
		if (overlap != nullptr)
			overlap->SetRect(left, top, right, bottom);
		return true;
	}

	return false;
}

bool Rect::Collision(Object* object)
{
	Circle* circle = dynamic_cast<Circle*>(object);

	if (circle != nullptr)
		return Collision(circle);
	else
	{
		Rect* rect = dynamic_cast<Rect*>(object);
		return Collision(rect);
	}
}

void Rect::SetRect(double left, double top, double right, double bottom)
{
	center.x = (left + right) * 0.5;
	center.y = (top + bottom) * 0.5;

	size.x = abs(right - left);
	size.y = abs(bottom - top);
}
