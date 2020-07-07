#pragma once

class NormalStageScene : public Scene
{
public:
	NormalStageScene();
	~NormalStageScene();

	virtual void Update() override;
	virtual void Render(HDC hdc) override;
	
private:
	Eri* eri;

	Texture* bg;
	Rect* bg_rect;

	Texture* collision_bg;
	Rect* collision_bg_rect;

	vector<Bullet*> tmp_bulletPool;
};

