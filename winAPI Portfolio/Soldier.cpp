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
	{//L_IDLE
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[L_IDLE]->SetPart(0, 3, true, true);
	}

	{//R_IDLE
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[R_IDLE]->SetPart(4, 7, true, true);
	}


	{//L_WALK
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[L_WALK]->SetPart(8, 19, true);
	}
	{//R_WALK
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[R_WALK]->SetPart(20, 31, true);
	}

	{//L_DIE
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[L_DIE]->SetPart(32, 43, true);
	}

	{//R_DIE
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[R_DIE]->SetPart(44, 55, true);
	}

	{//L_ATTACK
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[L_DIE]->SetPart(56, 62, true);
	}

	{//R_ATTACK
		soldier_actions.emplace_back(new Animation(soldier_texture));
		soldier_actions[L_DIE]->SetPart(63, 69, true);
	}


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
