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
		R_RUN,
		L_RUN,
		R_JUMPUP,
		L_JUMPUP,
		R_JUMPDOWN,
		L_JUMPDOWN,
		R_ATTACK,
		L_ATTACK
	};

	Eri();
	~Eri();

	void Update();
	void Render();

	void Move();
	void Move2();
	void Jump();
	void Attack();

	void SetIdle();

	void CreateActions();

	void SetAction(State value);

private:
	Texture* texture;
	Rect* rect;

	vector<Animation*> actions;
	Animation* curAction;

	State state;


	double speed;
	double velocity;
	double accelate;
	double decelerate;

	double jumpPower;
	double gravity;

	bool isJump;
	bool isRight;
	bool isAttack;

	//FX* effect;
	int alpha;
};