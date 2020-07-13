#pragma once


class Enemy
{
public:
	Enemy() {};
	virtual ~Enemy() {};

	void Die() { isDead = true; }
	bool IsDead() { return isDead; }

private:
	double damage = 0;
	double hp = 0;
	bool isDead = false;
};

