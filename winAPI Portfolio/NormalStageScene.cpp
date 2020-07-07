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
	tmp_bulletPool = GM->GetBulletPool(eri->GetCurWeapon());

	for (int i = 0; i < tmp_bulletPool.size(); i++)
	{
		if (!(tmp_bulletPool[i]->GetActive()))
		{
			tmp_bulletPool[i]->Update();
		}
	}
	eri->Update();
}

void NormalStageScene::Render(HDC hdc)
{
	bg->Render(bg_rect);
	collision_bg->Render(collision_bg_rect);
	eri->Render();

	for (int i = 0; i < tmp_bulletPool.size(); i++)
	{
		if ((!tmp_bulletPool[i]->GetActive()))
		{
			tmp_bulletPool[i]->Render();
		}
	}
}

