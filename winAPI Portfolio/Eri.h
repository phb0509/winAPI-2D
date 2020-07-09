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
		L_WALK_JUMP,

		R_STAND_ATTACK,
		L_STAND_ATTACK,
		R_WALK_ATTACK,
		L_WALK_ATTACK,
		//R_STAND_JUMP_ATTACK,
		//L_STAND_JUMP_ATTACK

	};

	Eri();
	~Eri();

	void Update();
	void Render();

	void CheckStand();
	void Move();
	void Jump();
	void SetIdle();

	void CreateActions();
	void SetUpperAction(State value);
	void SetLowerAction(State value);
	void GroundPixelCollision();

	void Fire(string curWeapon);
	void ChangeWeapon(string weapon) { curWeapon = weapon; }; 
	string GetCurWeapon() { return curWeapon; }

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

	bool isRight;
	bool isAttack;
	bool isGround;
	bool isJump;

	bool isRightButton;
	bool isLeftButton;
	bool isStand;

	string curWeapon;
	vector<Bullet*> tmp_bulletPool;
	

	//FX* effect;
	
};