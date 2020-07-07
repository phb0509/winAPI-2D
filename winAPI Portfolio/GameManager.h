#pragma once

struct TextureObject
{

public:
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
	void Initialize_Bullet();
	void Setting_FirstScene(); // 에리,플레이어 위치 설정.

	Eri* GetEri() { return eri; }
	TextureObject GetNormalBackGround();
	vector<Bullet*> GetBulletPool(string weaponName) { return bullet_pool[weaponName]; }


private:
	Eri* eri;

	Texture* normalStage_BackGround;
	Rect* normalStage_BackGround_Rect;

	Texture* normalStage_BackGroundCollision;
	Rect* normalStage_BackGroundCollision_Rect;

	TextureObject texture_Object;

	Bullet* bullet;
	map<string, vector<Bullet*> > bullet_pool;
	//Soldier* soldier;
};

