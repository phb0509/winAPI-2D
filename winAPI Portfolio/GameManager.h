#pragma once

struct TextureObject
{
	Texture* texture;
	Texture* collision_texture;
	Rect* rect;
	Rect* collision_rect;
};


class GameManager
{
public:
	GameManager();
	~GameManager();

	static GameManager* Get()
	{
		static GameManager instance;
		return &instance;
	}

	void Initialize_Object();  // 
	void Setting_FirstScene(); // 에리,플레이어 위치 설정.

	Eri* GetEri() { return eri; }
	//Texture* GetNormalBackground(){ return normalStage_BackGround; }
	TextureObject GetNormalBackGround();

private:
	Eri* eri;

	Texture* normalStage_BackGround;
	Rect* normalStage_BackGround_Rect;

	Texture* normalStage_BackGroundCollision;
	Rect* normalStage_BackGroundCollision_Rect;



	TextureObject texture_Object;
	//Soldier* soldier;
};

