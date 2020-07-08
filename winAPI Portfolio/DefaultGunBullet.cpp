#include "Framework.h"

DefaultGunBullet::DefaultGunBullet()
{
	bullet_texture = TEX->BitmapAdd(L"Textures/Effects/DefaultGun_Bullet.bmp", 10,6);
	bullet_rect = new Rect({ -10,-10 }, bullet_texture->Size());
}

DefaultGunBullet::~DefaultGunBullet()
{
	delete bullet_rect;
}

void DefaultGunBullet::Update()
{
	bullet_rect->center.x += 500 * DELTA;
}

void DefaultGunBullet::Render()
{
	bullet_texture->Render(bullet_rect);
}
