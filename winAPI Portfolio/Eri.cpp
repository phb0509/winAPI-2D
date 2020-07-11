#include "Framework.h"

Eri::Eri()
	: upperState(U_R_IDLE), lowerState(L_L_IDLE), speed(100), isRight(true), isGround(true), gravity(980), standardTime(0),
	jumpPower(0), isStand(true), isRightButton(false), isLeftButton(false), isAttack(false), isFire(true), isFireUpdate(false)

{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 500, 1250, 4, 10);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 1450, 50, 29, 1);

	upperBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 40 }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X - 150, CENTER_Y + 50 }, lowerBody_texture->Size());

	curWeapon = Weapon("DefaultGunBullet", 0.1f, 10000);

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
	UpdateAttackDelay();
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
			if (!isAttack)
			{
				SetUpperAction(U_R_IDLE);
				SetLowerAction(L_R_IDLE);
			}

			if (isFire)
			{
				if (KEYDOWN(0x41)) 
				{
					isAttack = true;
					Fire();
					SetUpperAction(U_R_STAND_ATTACK); 
				}
			}
		}

		else // 왼쪽 보고있는 경우
		{
			if (!isAttack)
			{
				SetUpperAction(U_L_IDLE);
				SetLowerAction(L_L_IDLE);
			}

			if (KEYDOWN(0x41)) // 공격키 누르면
			{
				isAttack = true;
				Fire();
				SetUpperAction(U_L_STAND_ATTACK);
			}
		}
	}


	if (KEYPRESS(VK_RIGHT))
	{
		isRight = true;
		isRightButton = true;

		upperBody_rect->center.x += speed * DELTA;
		lowerBody_rect->center.x += speed * DELTA;

		if (!isJump && !isAttack)
		{
			SetUpperAction(U_R_WALK);
			SetLowerAction(L_R_WALK);
		}

		else if (!isJump && isAttack)
		{
			SetUpperAction(U_R_STAND_ATTACK);
			SetLowerAction(L_R_WALK);
			Fire();
		}
	}

	if (KEYPRESS(VK_LEFT))
	{
		isRight = false;
		isLeftButton = true;

		upperBody_rect->center.x -= speed * DELTA;
		lowerBody_rect->center.x -= speed * DELTA;

		if (!isJump && !isAttack)
		{
			SetUpperAction(U_L_WALK);
			SetLowerAction(L_L_WALK);
		}

		else if (!isJump && isAttack)
		{
			SetUpperAction(U_L_STAND_ATTACK);
			SetLowerAction(L_L_WALK);
			Fire();
		}

	}


	// 

	Jump();
}

void Eri::Jump()
{
	if (KEYDOWN(0x53) && !isJump)
	{
		jumpPower = 400;

		if (isStand) // 제자리에서 점프했을 때
		{
			isJump = true;
			isGround = false;

			if (isRight)
			{
				SetLowerAction(L_R_STAND_JUMP);
			}
			else
			{
				SetLowerAction(L_L_STAND_JUMP);
				if (KEYDOWN(0x41)) // 공격키 누르면
				{
					SetUpperAction(U_L_STAND_ATTACK);
					Fire();
				}
			}
		}

		else if (!isStand) // Walk하면서 점프했을 때
		{
			isJump = true;
			isGround = false;

			if (isRight)
			{
				SetLowerAction(L_R_WALK_JUMP);
			}
			else
			{
				SetLowerAction(L_L_WALK_JUMP);
			}
		}
	}


	if (isJump) // 점프를 하고있는 상태
	{
		if (KEYDOWN(0x41)) // 공격키 누르면
		{
			Fire();

			if (isRight)
			{
				SetUpperAction(U_R_STAND_ATTACK);
			}
			else
			{
				SetUpperAction(U_L_STAND_ATTACK);
			}
		}

		if (isGround)
		{
			isJump = false;
			if (isRight)
			{
				SetUpperAction(U_R_IDLE);
				SetLowerAction(L_R_IDLE);
			}
			else
			{
				SetUpperAction(U_L_IDLE);
				SetLowerAction(L_L_IDLE);
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



void Eri::Fire()
{
	isFire = false;
	fireStandardTime = CURTIME + curWeapon.getAttackDelay();
	tmp_bulletPool = GM->GetBulletPool(curWeapon.getWeaponName());
	for (int i = 0; i < tmp_bulletPool.size(); i++)
	{
		if (tmp_bulletPool[i]->GetActive())
		{
			tmp_bulletPool[i]->SetActive(false);
			tmp_bulletPool[i]->SetBulletPosition(Vector2(upperBody_rect->center.x + 25, upperBody_rect->center.y));
			break;
		}
	}
	isFireUpdate = true;
}



void Eri::UpdateAttackDelay()
{
	if (!isFireUpdate) return;

	if (CURTIME >= fireStandardTime)
	{
		isFire = true;
		isFireUpdate = false;
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
			upperBody_actions[U_R_IDLE]->SetPart(0, 3, true, true);
		}

		{//L_IDLE
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[U_L_IDLE]->SetPart(0, 3, true, true);
		}

		{//R_WALK
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[U_R_WALK]->SetPart(4, 15, true, true);
			//upperBody_actions[R_WALK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}

		{//L_WALK
			upperBody_actions.emplace_back(new Animation(upperBody_texture));
			upperBody_actions[U_L_WALK]->SetPart(4, 15, true, true);
			//upperBody_actions[L_WALK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}

		{//R_STAND_ATTACK
			upperBody_actions.emplace_back(new Animation(upperBody_texture, 0.02));
			upperBody_actions[U_R_STAND_ATTACK]->SetPart(28, 37);
			upperBody_actions[U_R_STAND_ATTACK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}

		{//L_STAND_ATTACK
			upperBody_actions.emplace_back(new Animation(upperBody_texture, 0.02));
			upperBody_actions[U_L_STAND_ATTACK]->SetPart(28, 37);
			upperBody_actions[U_L_STAND_ATTACK]->SetEndEvent(bind(&Eri::SetUpperIdle, this));
		}
	}



	//LowerBody CreateActions
	{
		{//R_IDLE
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_R_IDLE]->SetPart(0, 0);
		}

		{//L_IDLE
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_L_IDLE]->SetPart(0, 0);
		}


		{//R_WALK
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_R_WALK]->SetPart(5, 16, true);
		}

		{//L_WALK
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_L_WALK]->SetPart(5, 16, true);
		}


		{//R_STAND_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_R_STAND_JUMP]->SetPart(17, 22, false, true);
		}

		{//L_STAND_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));
			lowerBody_actions[L_L_STAND_JUMP]->SetPart(17, 22, false, true);
		}


		{//R_WALK_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_R_WALK_JUMP]->SetPart(23, 28);
		}

		{//L_WALK_JUMP
			lowerBody_actions.emplace_back(new Animation(lowerBody_texture));
			lowerBody_actions[L_L_WALK_JUMP]->SetPart(23, 28);
		}
	}
}

void Eri::SetUpperAction(UpperState value)
{
	int a = (int)value;

	if (a >= 4 && a <= 5)
	{
		upperState = value;
		upperBody_curAction = upperBody_actions[value];
		upperBody_curAction->Play();
	}

	else
	{
		if (upperState != value)
		{
			upperState = value;
			upperBody_curAction = upperBody_actions[value];
			upperBody_curAction->Play();
		}
	}


}

void Eri::SetLowerAction(LowerState value)
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
	//if (isRight)
	//	SetUpperAction(U_R_IDLE);
	//else
	//	SetUpperAction(U_L_IDLE);

	isAttack = false;
	//Vector2 pos = { rect->center.x, rect->Bottom() }; // 이펙트 재생위치
	//EFFECT->Play("Slash", pos, { 50, 50 });
}

void Eri::SetLowerIdle()
{
	if (isRight)
		SetLowerAction(L_R_IDLE);
	else
		SetLowerAction(L_L_IDLE);
}








