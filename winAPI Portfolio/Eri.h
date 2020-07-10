#pragma once

class Eri
{
public:
	enum UpperState
	{
		U_R_IDLE,
		U_L_IDLE,

		U_R_WALK,
		U_L_WALK,


		U_R_STAND_ATTACK, // ������ ��� ����� ���, IDLE�϶��� WALK�ϋ��� JUMP�϶��� �� �Ȱ����ѵ� //�����̺�Ʈ�� �� �ٸ��� ������ ���� �����߰�
		U_L_STAND_ATTACK,

		// ���� ����, ���� �� �Ʒ��� ���� , ������� �ѽ��(�Ʒ�����Ű �� ����), ��ź������, 
	};

	enum LowerState
	{
		L_R_IDLE,
		L_L_IDLE,

		L_R_WALK,
		L_L_WALK,

		L_R_STAND_JUMP,
		L_L_STAND_JUMP,

		L_R_WALK_JUMP,
		L_L_WALK_JUMP,
	};

	Eri();
	~Eri();

	void Update();
	void Render();

	void CheckStand();
	void Move();
	void Jump();
	void SetUpperIdle();
	void SetLowerIdle();

	void CreateActions();
	void SetUpperAction(UpperState value);
	void SetLowerAction(LowerState value);
	void GroundPixelCollision();

	void Fire(string curWeapon, double delay);
	void FireUpdate(double delay);
	void ChangeWeapon(string weapon) { curWeapon = weapon; }; 
	string GetCurWeapon() { return curWeapon; }

private:

	Texture* upperBody_texture;
	Texture* lowerBody_texture;

	UpperState upperState;
	LowerState lowerState;

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

	bool isFire;
	bool isFireUpdate;
	double fireStandardTime;

	double standardTime;
	string curWeapon;
	vector<Bullet*> tmp_bulletPool;
	

	//FX* effect;
	
};