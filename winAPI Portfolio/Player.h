#pragma once

class Player
{
public:
	Player() {};
	virtual ~Player() {};

	void Die() { isDead = true; }
	bool IsDead() { return isDead; }

private:

	bool isDead = false;

};

