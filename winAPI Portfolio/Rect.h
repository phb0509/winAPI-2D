#pragma once

class Rect : public Object
{
public:
	Rect();
	Rect(Vector2 center, Vector2 size);
	Rect(double left, double top, double right, double bottom);
	~Rect();

	double Left() { return center.x - size.x * 0.5; }
	double Right() { return center.x + size.x * 0.5; }
	double Top() { return center.y - size.y * 0.5; }
	double Bottom() { return center.y + size.y * 0.5; }

	Vector2 Half() { return size * 0.5; }

	virtual void Render(HDC hdc) override;
	virtual bool Collision(Vector2 pos) override;
	virtual void Set(Vector2 center, double radius) override;

	bool Collision(Circle* circle);
	bool Collision(Rect* rect);
	bool Collision(OUT Rect* overlap, IN Rect* rect);
	bool Collision(Object* object);

	void SetRect(double left, double top, double right, double bottom);

	Vector2 center;
	Vector2 size;
};