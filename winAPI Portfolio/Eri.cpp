#include "Framework.h"

Eri::Eri()
	: state(R_IDLE), speed(150), isRight(true)
{

	upperBody_texture = TEX->BitmapAdd(L"Textures/Eri/UpperBody_pack.bmp", 250, 1750, 2, 14);
	lowerBody_texture = TEX->BitmapAdd(L"Textures/Eri/LowerBody_pack.bmp", 850, 50, 17, 1);

	upperBody_rect = new Rect({ CENTER_X-150, CENTER_Y + 50 }, upperBody_texture->Size());
	lowerBody_rect = new Rect({ CENTER_X-150, CENTER_Y + 60 }, lowerBody_texture->Size());

	CreateActions();

	upperBody_curAction = upperBody_actions[state];
	lowerBody_curAction = lowerBody_actions[state];

	upperBody_curAction->Play();
	lowerBody_curAction->Play();

	//char buff[100];
	//sprintf_s(buff, "주소값 : %f\n", &collisionBackGround_DC);
	//OutputDebugStringA(buff);



	//collisionBackGround_DC = GM->GetNormalBackGround().collision_texture->GetMemDC();




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
	GroundPixelCollision();
}

void Eri::Render()
{
	lowerBody_texture->Render(lowerBody_rect, lowerBody_curAction->GetFrame());
	upperBody_texture->Render(upperBody_rect, upperBody_curAction->GetFrame());


	//effect->Render();
}


void Eri::Move()
{

	if (KEYPRESS(VK_RIGHT))
	{
		isRight = true;
		upperBody_rect->center.x += speed * DELTA;
		lowerBody_rect->center.x += speed * DELTA;
		SetAction(R_WALK);

	}

	if (KEYPRESS(VK_LEFT))
	{
		isRight = false;
		upperBody_rect->center.x -= speed * DELTA;
		lowerBody_rect->center.x -= speed * DELTA;
		SetAction(L_WALK);
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

void Eri::GroundPixelCollision()
{
	color = GetPixel(GM->GetNormalBackGround().collision_texture->GetMemDC(), lowerBody_rect->center.x, lowerBody_rect->center.y - BG_TOP);
	// 검정색만 출력되는중.
	c_color = RGB(240, 0, 174);
	
	char buff[100];
	sprintf_s(buff, "하체 Y좌표 : %f , 테스트Y좌표 : %f \n", lowerBody_rect->center.x, lowerBody_rect->center.Y, lowerBody_rect->center.y - BG_TOP);
	//sprintf_s(buff, "TOP : %f \n", BG_TOP);
	OutputDebugStringA(buff);

	HBRUSH brush = CreateSolidBrush(color);
	SelectObject(GM->GetNormalBackGround().collision_texture->GetMemDC(), brush);
	Rectangle(GM->GetNormalBackGround().collision_texture->GetMemDC(), 100,100, 200, 200);

	if (color == c_color)
	{
		char buff[100];
		sprintf_s(buff, "뭐라도 좀 떠라떠랃떠라\n");
		OutputDebugStringA(buff);
	}
}
