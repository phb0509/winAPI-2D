#pragma once

class Rect;

class Circle : public Object
{
public:
	Circle();
	Circle(Vector2 center, double radius);
	~Circle();

	void Render(HDC hdc);

	double Left() { return center.x - radius; }
	double Right() { return center.x + radius; }
	double Top() { return center.y - radius; }
	double Bottom() { return center.y + radius; }

	bool Collision(Vector2 pos);
	bool Collision(Circle* circle);
	bool Collision(Rect* rect);

	void Set(Vector2 center, double radius);

	Vector2 center;
	double radius;
};