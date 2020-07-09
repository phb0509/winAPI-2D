#include "Framework.h"

Eri::Eri()
	: upperState(R_IDLE), lowerState(L_IDLE),speed(100), isRight(true), isGround(true), gravity(980),
	jumpPower(0), isStand(true), isRightButton(false), isLeftButton(false), isAttack(false), curWeapon("DefaultGunBullet")
{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 500, 1250, 4, 10);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 1450, 50, 29, 1);

	upperBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 40 }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 50 }, lowerBody_texture->Size());

	CreateActions();

	upperBody_curAction = upperBody_actions[upperState];
	lowerBody_curAction = lowerBody_actions[lowerState];

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
	lowerBody_curAction->Update(); // 애니메이션 클레스의 업데이트 실행
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
		if (isRight)
		{
			SetUpperAction(R_IDLE);
			SetLowerAction(R_IDLE); // 하체
			if (KEYDOWN(0x41)) // 공격키 누르면
			{
				SetUpperAction(R_STAND_ATTACK);
				Fire(curWeapon);
			}
		}

		else
		{
			SetUpperAction(L_IDLE);
			SetLowerAction(L_IDLE); // 하체
			if (KEYDOWN(0x41)) // 공격키 누르면
			{
				SetUpperAction(L_STAND_ATTACK);
				Fire(curWeapon);
			}
		}
	}


	if (KEYPRESS(VK_RIGHT))
	{
		isRight = true;
		isRightButton = true;

		upperBody_rect->center.x += speed * DELTA;
		lowerBody_rect->center.x += speed * DELTA;

		if (!isJump)
		{
			SetUpperAction(R_WALK);
			SetLowerAction(R_WALK);
		}

		if (KEYDOWN(0x41)) // 공격키 누르면
		{
			Fire(curWeapon);
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
			SetUpperAction(L_WALK);
			SetLowerAction(L_WALK);
		}

		if (KEYDOWN(0x41)) // 공격키 누르면
		{
			Fire(curWeapon);
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

			if (isRight)
			{
				SetLowerAction(R_STAND_JUMP);
			}
			else
			{
				SetLowerAction(L_STAND_JUMP);
			}
		}

		else if (!isStand) // Walk하면서 점프했을 때
		{
			isJump = true;
			isGround = false;
			if (isRight)
			{
				SetLowerAction(R_WALK_JUMP);
			}
			else
			{
				SetLowerAction(L_WALK_JUMP);
			}
		}
	}

	if (isJump) // 점프를 하고있는 상태
	{
		if (isGround)
		{
			isJump = false;
			if (isRight)
			{
				SetUpperAction(R_IDLE);
				SetLowerAction(R_IDLE);

			}
			else
			{
				SetUpperAction(L_IDLE);
				SetLowerAction(L_IDLE);
			}
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
			tmp_bulletPool[i]->SetBulletPosition(Vector2(upperBody_rect->center.x + 25, upperBody_rect->center.y));
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
	// UpperBody CreateActions
	{
		{//R_IDLE
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[R_IDLE]->SetPart(0, 3, true, true);
		}

		{//L_IDLE
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[L_IDLE]->SetPart(0, 3, true, true);
		}

		{//R_WALK
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[R_WALK]->SetPart(4, 15, true, true);
			//upperBody_actions[R_WALK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}

		{//L_WALK
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[L_WALK]->SetPart(4, 15, true, true);
			//upperBody_actions[L_WALK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}

		{//R_STAND_ATTACK
			upperBody_actions.emplace_back(new Animation(upperBody_texture, 0.02));

			upperBody_actions[R_STAND_ATTACK]->SetPart(28, 37);
			//upperBody_actions[R_STAND_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
		}

		{//L_STAND_ATTACK
			upperBody_actions.emplace_back(new Animation(upperBody_texture, 0.02));
			upperBody_actions[L_STAND_ATTACK]->SetPart(28, 37);
			//upperBody_actions[R_STAND_ATTACK]->SetEndEvent(bind(&Eri::SetIdle, this));
		}
	}



	//LowerBody CreateActions
	{
		{//R_IDLE
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[R_IDLE]->SetPart(0, 0);
		}

		{//L_IDLE
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_IDLE]->SetPart(0, 0);
		}


		{//R_WALK
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[R_WALK]->SetPart(5, 16, true);
		}

		{//L_WALK
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_WALK]->SetPart(5, 16, true);
		}


		{//R_STAND_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[R_STAND_JUMP]->SetPart(17, 22, false, true);
		}

		{//L_STAND_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_STAND_JUMP]->SetPart(17, 22, false, true);
		}


		{//R_WALK_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[R_WALK_JUMP]->SetPart(23, 28);
		}

		{//L_WALK_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_WALK_JUMP]->SetPart(23, 28);
		}
	}
}

void Eri::SetUpperAction(State value)
{
	//int a = (int)value;

	//if (a >= 8 && a <= 9)
	//{
	//	state = value;
	//	upperBody_curAction = upperBody_actions[value];
	//	upperBody_curAction->Play();
	//}

	//else
	//{
	//	if (state != value)
	//	{
	//		state = value;
	//		upperBody_curAction = upperBody_actions[value];
	//		upperBody_curAction->Play();
	//	}
	//}

	if (upperState != value)
	{
		upperState = value;
		upperBody_curAction = upperBody_actions[value];
		upperBody_curAction->Play();
	}
}

void Eri::SetLowerAction(State value)
{
	if (lowerState != value)
	{
		lowerState = value;
		lowerBody_curAction = lowerBody_actions[value];
		lowerBody_curAction->Play();
	}
}


void Eri::SetUpperIdle()
{
	if (isRight)
		SetUpperAction(R_IDLE);
	else
		SetUpperAction(L_IDLE);
	//Vector2 pos = { rect->center.x, rect->Bottom() }; // 이펙트 재생위치
	//EFFECT->Play("Slash", pos, { 50, 50 });
}

void Eri::SetLowerIdle()
{
	if (isRight)
		SetLowerAction(R_IDLE);
	else
		SetLowerAction(L_IDLE);
}








