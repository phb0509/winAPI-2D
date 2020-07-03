#include "Framework.h"

NormalStageScene::NormalStageScene()
{
	eri = GM->GetEri();
	bg = GM->GetNormalBackGround().texture;
	bg_rect = GM->GetNormalBackGround().rect;

	collision_bg = GM->GetNormalBackGround().collision_texture;
	collision_bg_rect = GM->GetNormalBackGround().collision_rect;

}

NormalStageScene::~NormalStageScene()
{
	
}

void NormalStageScene::Update()
{
	eri->Update();
}

void NormalStageScene::Render(HDC hdc)
{
	bg->Render(bg_rect);
	collision_bg->Render(collision_bg_rect);
	eri->Render();
}

