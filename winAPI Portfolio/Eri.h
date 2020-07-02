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

private:
	Texture* texture; //�����



	Texture* upperBody_texture;
	Texture* lowerBody_texture;

	Rect* rect; // �����
	Rect* upperBody_rect;
	Rect* lowerBody_rect;
	Rect* colliderRect;


	vector<Animation*> actions; // �����
	vector<Animation*> upperBody_actions;
	vector<Animation*> lowerBody_actions;

	Animation* curAction; // �����
	Animation* upperBody_curAction;
	Animation* lowerBody_curAction;

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