#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(300), velocity(0), decelerate(3), accelate(5),
	jumpPower(0), gravity(980), isJump(false), isRight(true),
	alpha(0)
{

	//texture = TEX->BitmapAdd(L"Textures/mario.bmp", 512, 328, 8, 4);
	upperBody_texture = TEX->BitmapAdd(L"Textures/UpperBody_pack.bmp", 250, 1750, 2, 14);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/LowerBody_pack.bmp", 850, 50, 1, 17);

	//rect = new Rect({ 100, CENTER_Y }, texture->Size());
	upperBody_rect = new Rect({ CENTER_X, CENTER_Y }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X, CENTER_Y + 30 }, lowerBody_texture->Size());


	CreateActions();

	curAction = actions[state]; //vector[enum 정수값] // default값이 IDLE인듯.
	curAction->Play();

	//Texture* expTex = TEX->PlusmapAdd(L"Textures/Effects/Explosion.png", 4, 4);
	//effect = new FX(expTex);
}

Eri::~Eri()
{
	//delete rect;

	//for (Animation* action : actions)
	//	delete action;

	//delete effect;
}

void Eri::Update()
{
	Move();
	//Jump();
	//Attack();

	//curAction->Update();
	upperBody_curAction->Update();
	lowerBody_curAction->Update();

	//effect->Update();
}

void Eri::Render()
{
	upperBody_texture->Render(upperBody_rect, upperBody_curAction->GetFrame());
	lowerBody_texture->Render(lowerBody_rect, lowerBody_curAction->GetFrame());
	//effect->Render();
}


void Eri::Move()
{

	if (KEYPRESS(VK_RIGHT))
	{
		velocity += accelate * DELTA;
		if (velocity > 1.0)
			velocity = 1.0;
	}
	if (KEYPRESS(VK_LEFT))
	{
		velocity -= accelate * DELTA;
		if (velocity < -1.0)
			velocity = -1.0;
	}

	if (velocity < 0)
	{
		isRight = false;

		velocity += DELTA * decelerate;
		if (velocity >= 0)
		{
			velocity = 0;
			if (!isJump)
				SetAction(L_IDLE);
		}
		else
		{
			if (!isJump)
			{
				if (abs(velocity) > 0.9)
					SetAction(L_RUN);
				else
					SetAction(L_WALK);
			}
		}
	}
	else if (velocity > 0)
	{
		isRight = true;

		velocity -= DELTA * decelerate;
		if (velocity <= 0)
		{
			velocity = 0;
			if (!isJump)
				SetAction(R_IDLE);
		}
		else
		{
			if (!isJump)
			{
				if (abs(velocity) > 0.9)
					SetAction(R_RUN);
				else
					SetAction(R_WALK);
			}
		}
	}

	rect->center.x += velocity * speed * DELTA;
}



void Eri::SetIdle()
{
	if (isRight)
		SetAction(R_IDLE);
	else
		SetAction(L_IDLE);

	isAttack = false;

	Vector2 pos = { rect->center.x, rect->Bottom() };
	//EFFECT->Play("Slash", pos, { 50, 50 });
}

void Eri::CreateActions()
{
	{//R_IDLE
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[R_IDLE]->SetPart(0, 3, true, true);
		lowerBody_actions[R_IDLE]->SetPart(0, 0, true, true);
	}

	{//L_IDLE //  L_IDLE 팩에 추가안해서 일단 R_IDLE로
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[L_IDLE]->SetPart(0, 3, true, true);
		lowerBody_actions[L_IDLE]->SetPart(0, 0, true, true);
	}

	{//R_WALK
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[R_WALK]->SetPart(4, 15, true);
		lowerBody_actions[R_WALK]->SetPart(1, 16, true);
	}

	{//L_WALK // L_WALK 팩에 추가 안해서 일단 R_WALK로
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[L_WALK]->SetPart(4, 15, true);
		lowerBody_actions[L_WALK]->SetPart(1, 16, true);
	}
	


	//{//R_ATTACK
	//	actions.emplace_back(new Animation(texture));
	//	actions[R_ATTACK]->SetPart(16, 19);
	//	actions[R_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
	//}
	//{//L_ATTACK
	//	actions.emplace_back(new Animation(texture));
	//	actions[L_ATTACK]->SetPart(20, 23);
	//	actions[L_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
	//}
}

void Eri::SetAction(State value)
{
	if (state != value)
	{
		state = value;
		curAction = actions[value];
		curAction->Play();
	}
}
