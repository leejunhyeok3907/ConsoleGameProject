#pragma once
#include "Object.h"
class Player : public Object
{
public:
	Player();
	virtual ~Player();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	void DrawCharacter();
	void CheckAttack();

private:
	bool m_DirRight = false;
	bool m_EquipWeapon = false;

	string WeaponArr[2][3] = {
		{"----", "+--->", "-]===>"},
		{"----", "<---+", "<===[-"}
	};

	float MaxGravity = 0.6f;
	float Gravity = 0.4f;
	bool IsGrounded = false;

	ULONGLONG JumpTick;
	bool Jumping = false;
	ULONGLONG ReduceJumpPowerTick;
	float JumpPower;

	ULONGLONG AttackTick;
	bool Attacking = false;

	int WeaponIndex = 2;

	Vec2 UnderCollision;
};

