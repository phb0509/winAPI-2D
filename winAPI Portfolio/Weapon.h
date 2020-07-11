#pragma once

class Weapon
{
public:
	Weapon();
	Weapon(string weaponName, double attackDelay, int numBullet);
	~Weapon();

	string getWeaponName() { return weaponName; }
	double getAttackDelay() { return attackDelay; }
	int getNumBullet() { return numBullet; }

private:
	string weaponName;
	double attackDelay;
	int numBullet;
};

