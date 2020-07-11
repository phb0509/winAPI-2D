#pragma once

class Weapon
{
public:
	Weapon();
	Weapon(string weaponName, double attackDelay, int bulletCount);
	~Weapon();

	string getWeaponName() { return weaponName; }
	double getAttackDelay() { return attackDelay; }
	int getNumBullet() { return bulletCount; }

private:
	string weaponName;
	double attackDelay;
	int bulletCount;
};

