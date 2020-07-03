#include "framework.h"

GameManager::GameManager()
{
	Initialize_Object();
}

GameManager::~GameManager()
{
	delete eri;
	delete normalStage_BackGround_Rect;
	delete normalStage_BackGroundCollision_Rect;
}

void GameManager::Initialize_Object()
{
	eri = new Eri();
	normalStage_BackGround = TEX->BitmapAdd(L"Textures/Background/NormalStageBackGround.bmp", 1255, 219);
	normalStage_BackGround_Rect = new Rect({ CENTER_X+300, CENTER_Y }, normalStage_BackGround->Size());

	normalStage_BackGroundCollision = TEX->BitmapAdd(L"Textures/Background/NormalStageBackGroundCollision.bmp", 1255, 219, RGB(255, 255, 255));
	normalStage_BackGroundCollision_Rect = new Rect({ CENTER_X + 300, CENTER_Y }, normalStage_BackGroundCollision->Size());

} 

void GameManager::Setting_FirstScene()
{

}

TextureObject GameManager::GetNormalBackGround()
{
	TextureObject textureObject;

	textureObject.texture = normalStage_BackGround;
	textureObject.rect = normalStage_BackGround_Rect;

	textureObject.collision_texture = normalStage_BackGroundCollision;
	textureObject.collision_rect = normalStage_BackGroundCollision_Rect;
	

	return textureObject;
}
