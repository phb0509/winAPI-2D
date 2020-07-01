#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(300), velocity(0), decelerate(3), accelate(5),
	jumpPower(0), gravity(980), isJump(false), isRight(true),
	alpha(0)
{
	texture = TEX->PlusmapAdd(L"Textures/mario.png", 8, 4);
	//texture = TEX->BitmapAdd(L"Textures/mario.bmp", 512, 328, 8, 4);

	rect = new Rect({ 100, CENTER_Y }, texture->Size());

	CreateActions();

	curAction = actions[state];
	curAction->Play();

	//Texture* expTex = TEX->PlusmapAdd(L"Textures/Effects/Explosion.png", 4, 4);
	//effect = new FX(expTex);
}

Eri::~Eri()
{
	delete rect;

	for (Animation* action : actions)
		delete action;

	//delete effect;
}

void Eri::Update()
{
	alpha--;
	if (alpha < 0)
		alpha = 255;

	Move2();
	//Jump();
	Attack();

	curAction->Update();
	//effect->Update();
}

void Eri::Render()
{
	texture->AlphaRender(rect, curAction->GetFrame(), alpha);
	//effect->Render();
}


void Eri::Move2()
{
	if (isAttack)
		return;

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

void Eri::Jump()
{
	if (!isJump && KEYDOWN(VK_UP))
	{
		jumpPower = 800;
		isJump = true;

		//SOUND->Play("Jump");

		if (isRight)
			SetAction(R_JUMPUP);
		else
			SetAction(L_JUMPUP);
	}

	//if (!isJump)
		//return;

	jumpPower -= gravity * DELTA;
	rect->center.y -= jumpPower * DELTA;

	if (landscape->PushCollider(rect))
	{
		if (isJump)
			SetIdle();

		isJump = false;
		jumpPower = 0;
	}
	else
	{
		TextureRect* block = nullptr;
		Math::Dir dir = landscape->BlockCollider(rect, block);

		switch (dir)
		{
		case Math::LEFT:
			break;
		case Math::RIGHT:
			break;
		case Math::UP:
			if (jumpPower > 0)
			{
				jumpPower = 0;
				block->SetActive(false);

				//effect->Play(block->GetRect()->center);
				EFFECT->Play("Exp", block->GetRect()->center);
				SOUND->Play("Exp");
			}
			break;
		case Math::DOWN:
			if (jumpPower <= 0)
			{
				if (isJump)
					SetIdle();

				isJump = false;
				jumpPower = 0;
			}
			break;
		case Math::NONE:
			isJump = true;
			break;
		default:
			break;
		}
	}



	if (jumpPower < 0)
	{
		if (isRight)
			SetAction(R_JUMPDOWN);
		else
			SetAction(L_JUMPDOWN);
	}
}

void Eri::Attack()
{
	if (isJump)
		return;

	if (KEYDOWN(VK_SPACE))
	{
		isAttack = true;

		if (isRight)
			SetAction(R_ATTACK);
		else
			SetAction(L_ATTACK);
	}
	/*
	if (state == R_ATTACK || state == L_ATTACK)
	{
		if (!curAction->GetPlay())
		{
			SetIdle();
			isAttack = false;
		}
	}*/
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
		actions.emplace_back(new Animation(texture));
		int arr[] = { 24 };
		actions[R_IDLE]->SetArray(arr, 1, true);
	}
	{//L_IDLE
		actions.emplace_back(new Animation(texture));
		int arr[] = { 28 };
		actions[L_IDLE]->SetArray(arr, 1, true);
	}
	{//R_WALK
		actions.emplace_back(new Animation(texture, 0.3));
		actions[R_WALK]->SetPart(0, 1, true);
	}
	{//L_WALK
		actions.emplace_back(new Animation(texture, 0.3));
		actions[L_WALK]->SetPart(4, 5, true);
	}
	{//R_RUN
		actions.emplace_back(new Animation(texture));
		actions[R_RUN]->SetPart(9, 11, true);
	}
	{//L_RUN
		actions.emplace_back(new Animation(texture));
		actions[L_RUN]->SetPart(13, 15, true);
	}
	{//R_JUMPUP
		actions.emplace_back(new Animation(texture));
		actions[R_JUMPUP]->SetPart(2, 2);
	}
	{//L_JUMPUP
		actions.emplace_back(new Animation(texture));
		actions[L_JUMPUP]->SetPart(6, 6);
	}
	{//R_JUMPDOWN
		actions.emplace_back(new Animation(texture));
		actions[R_JUMPDOWN]->SetPart(3, 3);
	}
	{//L_JUMPDOWN
		actions.emplace_back(new Animation(texture));
		actions[L_JUMPDOWN]->SetPart(7, 7);
	}
	{//R_ATTACK
		actions.emplace_back(new Animation(texture));
		actions[R_ATTACK]->SetPart(16, 19);
		actions[R_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
	}
	{//L_ATTACK
		actions.emplace_back(new Animation(texture));
		actions[L_ATTACK]->SetPart(20, 23);
		actions[L_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
	}
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
