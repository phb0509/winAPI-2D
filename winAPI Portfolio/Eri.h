#pragma once

class Eri
{
public:
	enum State
	{
		R_IDLE,
		L_IDLE,
		R_WALK,
		L_WALK,
	};

	Eri();
	~Eri();

	void Update();
	void Render();

	void Move();

	void SetIdle();

	void CreateActions();

	void SetAction(State value);

	void GroundPixelCollision();

private:

	Texture* upperBody_texture;
	Texture* lowerBody_texture;
	State state;
	Rect* upperBody_rect;
	Rect* lowerBody_rect;
	Rect* colliderRect;

	vector<Animation*> upperBody_actions;
	vector<Animation*> lowerBody_actions;

	Animation* upperBody_curAction;
	Animation* lowerBody_curAction;

	


	COLORREF color;
	COLORREF c_color;
	HDC collisionBackGround_DC;






	double speed;
	bool isRight;
	bool isAttack;

	//FX* effect;
	
};