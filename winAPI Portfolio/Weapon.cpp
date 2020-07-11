#include "framework.h"

Weapon::Weapon()
{
}

Weapon::Weapon(string _weaponName, double _attackDelay, int _bulletCount) : weaponName(_weaponName), attackDelay(_attackDelay), bulletCount(_bulletCount)
{
}

Weapon::~Weapon()
{
}
