#include "Framework.h"

DefaultGunBullet::DefaultGunBullet()
{
	bullet = TEX->BitmapAdd(L"Textures/Effects/DefaultGun_Bullet.bmp", 10,6);
	bullet_rect = new Rect({ -10,-10 }, bullet->Size());
}

DefaultGunBullet::~DefaultGunBullet()
{
}
