#include "framework.h"






Soldier::Soldier() : soldier_state(L_IDLE), speed(100), isRight(true), isGround(true), gravity(980), standardTime(0),
		isStand(true),  isAttack(false), isFire(true), isFireUpdate(false)
{
	soldier_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 500, 1250, 4, 10);


	soldier_rect = new Rect({ CENTER_X - 150, CENTER_Y + 40 }, soldier_texture->Size());


	CreateActions();

	upperBody_curAction = upperBody_actions[upperState];


	upperBody_curAction->Play();
	lowerBody_curAction->Play();
}

Soldier::~Soldier()
{
}

void Soldier::Update()
{
}

void Soldier::Render()
{
}

void Soldier::CheckStand()
{
}

void Soldier::Move()
{
}

void Soldier::SetIdle()
{
}

void Soldier::CreateActions()
{
}

void Soldier::SetAction(State value)
{
}

void Soldier::GroundPixelCollision()
{
}

void Soldier::Fire()
{
}

void Soldier::UpdateAttackDelay()
{
}
