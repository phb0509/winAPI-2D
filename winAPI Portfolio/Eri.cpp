#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(150), isRight(true), isGround(true), gravity(980), jumpPower(0), isWalk(false)
{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 250, 1750, 2, 14);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 850, 50, 17, 1);

	upperBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 50 }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 60 }, lowerBody_texture->Size());

	CreateActions();

	upperBody_curAction = upperBody_actions[state];
	lowerBody_curAction = lowerBody_actions[state];

	upperBody_curAction->Play();
	lowerBody_curAction->Play();

	//collisionBackGround_DC = GM->GetNormalBackGround().collision_texture->GetMemDC();       // 여기가 문제.
	//Texture* expTex = TEX->PlusmapAdd(L"Textures/Effects/Explosion.png", 4, 4);
	//effect = new FX(expTex);
}

Eri::~Eri()
{

}

void Eri::Update()
{
	GroundPixelCollision();
	Move();
	lowerBody_curAction->Update();
	upperBody_curAction->Update();

	//effect->Update();
}

void Eri::Render()
{
	lowerBody_texture->Render(lowerBody_rect, lowerBody_curAction->GetFrame());
	upperBody_texture->Render(upperBody_rect, upperBody_curAction->GetFrame());


	//effect->Render();
}


void Eri::Move()
{
	Jump();

	if (KEYPRESS(VK_RIGHT))
	{
		isRight = true;
		isWalk = true;
		upperBody_rect->center.x += speed * DELTA;
		lowerBody_rect->center.x += speed * DELTA;
		SetAction(R_WALK);

	}

	if (KEYPRESS(VK_LEFT))
	{
		isRight = false;
		isWalk = true;
		upperBody_rect->center.x -= speed * DELTA;
		lowerBody_rect->center.x -= speed * DELTA;
		SetAction(L_WALK);
	}




	if (KEYUP(VK_RIGHT) && KEYUP(VK_LEFT))
	{
		isWalk = false;
	}



	//if (KEYPRESS(0x41)) // A키. 공격
	//{

	//}



	//if (KEYPRESS(0x43)) // D키. 폭탄
	//{

	//}
}

void Eri::GroundPixelCollision()
{
	color = GetPixel(GM->GetNormalBackGround().collision_texture->GetMemDC(), lowerBody_rect->center.x, lowerBody_rect->center.y - BG_TOP + 26);
	colision_color = RGB(240, 0, 174);

	if (color == colision_color)
	{
		isGround = true;
		isJump = false;
	}

	else
	{
		jumpPower -= gravity * DELTA;
		upperBody_rect->center.y -= jumpPower * DELTA;
		lowerBody_rect->center.y -= jumpPower * DELTA;
	}
}

void Eri::Jump()
{
	if (!isJump && KEYDOWN(0x53))
	{
		jumpPower = 500;
		isJump = true;
	}
}



void Eri::SetIdle()
{
	if (isRight)
		SetAction(R_IDLE);
	else
		SetAction(L_IDLE);

	//Vector2 pos = { rect->center.x, rect->Bottom() }; // 이펙트 재생위치
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
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[R_WALK]->SetPart(4, 15, true, true);
		lowerBody_actions[R_WALK]->SetPart(5, 16, true);
	}

	{//L_WALK // L_WALK 팩에 추가 안해서 일단 R_WALK로
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[L_WALK]->SetPart(4, 15, true, true);
		lowerBody_actions[L_WALK]->SetPart(5, 16, true);
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
		//curAction = actions[value];
		//curAction->Play();

		upperBody_curAction = upperBody_actions[value];
		lowerBody_curAction = lowerBody_actions[value];
		upperBody_curAction->Play();
		lowerBody_curAction->Play();
	}
}

