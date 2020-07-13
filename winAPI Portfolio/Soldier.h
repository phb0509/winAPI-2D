#pragma once

class Soldier : public Enemy
{
	enum State
	{
		R_IDLE,
		L_IDLE,
		R_WALK,
		L_WALK,
		R_ATTACK,
		L_ATTACK,
		R_DIE,
		L_DIE
	};


public:
	Soldier();
	~Soldier();

	void Update();
	void Render();

	void CheckStand();
	void Move();
	void SetIdle();

	void CreateActions();
	void SetAction(State value);
	void GroundPixelCollision();

	void Fire();
	void UpdateAttackDelay();

private:

	Texture* soldier_texture;
	State soldier_state;

	Rect* soldier_texture_rect;

	Rect* collider_rect;

	vector<Animation*> soldier_actions;
	Animation* soldier_curAction;


	COLORREF color;
	COLORREF colision_color;

	double speed;
	double gravity;

	bool isRight;
	bool isAttack;
	bool isGround;
	bool isStand;

	bool isFire;
	bool isFireUpdate;
	double fireStandardTime;

	double standardTime;

};

