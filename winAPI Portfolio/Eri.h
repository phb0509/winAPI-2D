#pragma once


class Eri : public Player
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

	void Fire();
	void UpdateAttackDelay();
	void ChangeWeapon(Weapon weapon) { curWeapon = weapon; }; 
	string GetCurWeapon() { return curWeapon.getWeaponName(); }

private:

	Texture* upperBody_texture;
	Texture* lowerBody_texture;

	UpperState upperState;
	LowerState lowerState;

	Rect* upperBody_rect;
	Rect* lowerBody_rect;
	Rect* collider_rect;

	vector<Animation*> upperBody_actions;
	vector<Animation*> lowerBody_actions;

	Animation* upperBody_curAction;
	Animation* lowerBody_curAction;

	COLORREF color;
	COLORREF colision_color;

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
	Weapon curWeapon;
	vector<Bullet*> tmp_bulletPool;
	

	//FX* effect;
	
};