#include "framework.h"

Weapon::Weapon()
{
}

Weapon::Weapon(string _weaponName, double _attackDelay, int _numBullet) : weaponName(_weaponName), attackDelay(_attackDelay), numBullet(_numBullet)
{
}

Weapon::~Weapon()
{
}
