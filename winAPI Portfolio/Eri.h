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

		R_STAND_JUMP,
		L_STAND_JUMP,

		R_WALK_JUMP,
		L_WALK_JUMP
	};

	Eri();
	~Eri();

	void Update();
	void Render();

	void Move();
	void Jump();
	void CheckStand();

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
	COLORREF colision_color;
	HDC collisionBackGround_DC;



	double speed;
	double gravity;
	double jumpPower;
	double des_positionY;
	double dir_y;

	bool isRight;
	bool isAttack;
	bool isGround;
	bool isJump;

	bool isRightButton;
	bool isLeftButton;
	bool isStand;
	

	//FX* effect;
	
};