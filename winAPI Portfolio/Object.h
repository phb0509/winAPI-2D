#pragma once

class Object
{
public:
	Object();
	~Object();

	virtual void Render(HDC hdc) = 0;
	virtual bool Collision(Vector2 pos) { return true; };

	virtual void Set(Vector2 center, double radius) {};

	void Active(bool value) { isActive = value; }
	bool Active() { return isActive; }

protected:
	bool isActive;
};
