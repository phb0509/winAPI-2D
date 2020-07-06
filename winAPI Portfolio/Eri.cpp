#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(100), isRight(true), isGround(true), gravity(980),
	jumpPower(0), isStand(true), isRightButton(false), isLeftButton(false),
	des_positionY(0), dir_y(1)
{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 250, 1750, 2, 14);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 1450, 50, 29, 1);

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
	GroundPixelCollision(); // 픽셀충돌되면 isGround = true; 아니면 무조건 떨어짐
	CheckStand(); // 왼쪽,오른쪽키 둘다 안눌러져있으면 isStand = true; 아니면 false;
	if (isStand && isGround) { SetAction(R_IDLE); }

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


	if (KEYDOWN(0x53) && !isJump) // 애니메이션만 Set 해주고 실제 좌표이동은 다른곳에서...
								  // 점프중 아닐때만 키입력 받을 수 있게(이중 점프되면 안되니까)
	{
		des_positionY = lowerBody_rect->center.y + 200;
		dir_y = -1;

		if (isStand) // 제자리에서 점프했을 때
		{
			isJump = true;
			isGround = false;
			SetAction(R_STAND_JUMP);

		}

		else if (!isStand) // Walk하면서 점프했을 때
		{
			isJump = true;
			isGround = false;
			SetAction(R_WALK_JUMP);
		}
	}


	if (isJump) // 점프를 하고있는 상태, 일정위치까지 y좌표를 -해야하는 상태.
	{

		if (lowerBody_rect->center.y == des_positionY) 
		{ 
			dir_y = 1; 
		}

		if (isGround) 
		{
			isJump = false;
		};
	}

}

void Eri::GroundPixelCollision()
{
	color = GetPixel(GM->GetNormalBackGround().collision_texture->GetMemDC(), lowerBody_rect->center.x, lowerBody_rect->center.y - BG_TOP + 26);
	colision_color = RGB(240, 0, 174);

	if (color == colision_color)
	{
		isGround = true;
		dir_y = 0;
	}

	upperBody_rect->center.y += gravity * DELTA * dir_y;
	lowerBody_rect->center.y += gravity * DELTA * dir_y;
	
}

void Eri::Jump()
{
	if (!isJump && KEYDOWN(0x53))
	{
		jumpPower = 500;
		isJump = true;
	}
}

void Eri::CheckStand()
{
	if (KEYUP(VK_RIGHT)) { isRightButton = false; };
	if (KEYUP(VK_LEFT)) { isLeftButton = false; }

	if (!isRightButton && !isLeftButton) { isStand = true; }
	else { isStand = false; }
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
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[R_WALK_JUMP]->SetPart(22, 27, true, true);
		lowerBody_actions[R_WALK_JUMP]->SetPart(23, 28, true);
	}

	{//L_WALK_JUMP
		upperBody_actions.emplace_back(new Animation(upperBody_texture));
		lowerBody_actions.emplace_back(new Animation(lowerBody_texture, 0.05));

		upperBody_actions[L_WALK_JUMP]->SetPart(22, 27, true, true);
		lowerBody_actions[L_WALK_JUMP]->SetPart(23, 28, true);
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

