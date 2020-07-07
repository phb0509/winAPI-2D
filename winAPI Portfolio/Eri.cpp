#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(100), isRight(true), isGround(true), gravity(980),
	jumpPower(0), isStand(true), isRightButton(false), isLeftButton(false), isAttack(false),curWeapon("DefaultGunBullet")
{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 500, 1250, 4, 10);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 1450, 50, 29, 1);

	upperBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 40 }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 50 }, lowerBody_texture->Size());

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
	delete upperBody_rect;
	delete lowerBody_rect;

	for (Animation* upperBody_action : upperBody_actions)
		delete upperBody_action;

	for (Animation* lowerBody_action : lowerBody_actions)
		delete lowerBody_action;
}

void Eri::Update()
{
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
	GroundPixelCollision();
	CheckStand();

	if (isStand && isGround)
	{
		if (isRight)SetAction(R_IDLE);
		else  SetAction(L_IDLE);
	}

	if (KEYDOWN(0x41)) // 공격키 누르면
	{
		Fire(curWeapon);
		/*if (isStand && isGround)
		{
			if (isRight)SetAction(R_STAND_ATTACK);
			else  SetAction(L_STAND_ATTACK);
		}*/

	}

	if (KEYPRESS(VK_RIGHT))
	{
		isRight = true;
		isRightButton = true;

		upperBody_rect->center.x += speed * DELTA;
		lowerBody_rect->center.x += speed * DELTA;

		if (!isJump)
		{
			SetAction(R_WALK);
		}
	}

	if (KEYPRESS(VK_LEFT))
	{
		isRight = false;
		isLeftButton = true;

		upperBody_rect->center.x -= speed * DELTA;
		lowerBody_rect->center.x -= speed * DELTA;

		if (!isJump)
		{
			SetAction(L_WALK);
		}
	}

	Jump();
}

void Eri::Jump()
{
	if (KEYDOWN(0x53) && !isJump) // 애니메이션만 Set 해주고 실제 좌표이동은 다른곳에서...
								  // 점프중 아닐때만 키입력 받을 수 있게(이중 점프되면 안되니까)
	{
		jumpPower = 400;

		if (isStand) // 제자리에서 점프했을 때
		{
			isJump = true;
			isGround = false;

			if (isRight)SetAction(R_STAND_JUMP);
			else SetAction(L_STAND_JUMP);

		}

		else if (!isStand) // Walk하면서 점프했을 때
		{
			isJump = true;
			isGround = false;
			if (isRight)SetAction(R_WALK_JUMP);
			else SetAction(L_WALK_JUMP);
		}
	}

	if (isJump) // 점프를 하고있는 상태
	{
		if (isGround)
		{
			isJump = false;
		};
	}
}

void Eri::GroundPixelCollision()
{
	jumpPower -= gravity * DELTA;
	upperBody_rect->center.y -= jumpPower * DELTA;
	lowerBody_rect->center.y -= jumpPower * DELTA;

	color = GetPixel(GM->GetNormalBackGround().collision_texture->GetMemDC(), lowerBody_rect->center.x, lowerBody_rect->center.y - BG_TOP + 26);
	colision_color = RGB(240, 0, 174);

	if (color == colision_color)
	{
		isGround = true;
		jumpPower = 0;
		gravity = 0;
	}
	else
	{
		gravity = 980;
	}
}



void Eri::Fire(string curWeapon)
{
	tmp_bulletPool = GM->GetBulletPool(curWeapon);
	for (int i = 0; i < tmp_bulletPool.size(); i++)
	{
		if (tmp_bulletPool[i]->GetActive())
		{
			tmp_bulletPool[i]->SetActive(false);
			tmp_bulletPool[i]->SetBulletPosition(Vector2(upperBody_rect->center.x+25, upperBody_rect->center.y+5));
			break;
		}
	}
}






void Eri::CheckStand()
{
	if (KEYUP(VK_RIGHT)) { isRightButton = false; };
	if (KEYUP(VK_LEFT)) { isLeftButton = false; }

	if (!isRightButton && !isLeftButton) { isStand = true; }
	else { isStand = false; }
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

	{//R_STAND_JUMP
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[R_STAND_JUMP]->SetPart(16, 21, false, true);
		lowerBody_actions[R_STAND_JUMP]->SetPart(17, 22, false, true);
	}

	{//L_STAND_JUMP
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[L_STAND_JUMP]->SetPart(16, 21, true, true);
		lowerBody_actions[L_STAND_JUMP]->SetPart(17, 22, false, true);
	}

	{//R_WALK_JUMP
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.2));

		upperBody_actions[R_WALK_JUMP]->SetPart(22, 27);
		lowerBody_actions[R_WALK_JUMP]->SetPart(23, 28);
	}

	{//L_WALK_JUMP
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.2));

		upperBody_actions[L_WALK_JUMP]->SetPart(22, 27);
		lowerBody_actions[L_WALK_JUMP]->SetPart(23, 28);
	}


	{//R_STAND_ATTACK
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[R_STAND_ATTACK]->SetPart(28, 37);
		lowerBody_actions[R_STAND_ATTACK]->SetPart(0, 0);
	}

	{//L_STAND_ATTACK
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture));

		upperBody_actions[L_STAND_ATTACK]->SetPart(28, 37);
		lowerBody_actions[L_STAND_ATTACK]->SetPart(0, 0);
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

void Eri::SetIdle()
{
	if (isRight)
		SetAction(R_IDLE);
	else
		SetAction(L_IDLE);

	//Vector2 pos = { rect->center.x, rect->Bottom() }; // 이펙트 재생위치
	//EFFECT->Play("Slash", pos, { 50, 50 });
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

