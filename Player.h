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
	void CheckSkillHit();
	int GetRandomDamage(int _MaxDamage, int _MinDamage);
	bool CheckPlayerDead();
	void KeyInput(int _CurrentTick);

private:
	bool m_DirRight = false;
	bool m_EquipWeapon = false;

	string WeaponArr[2][3] = {
		{"----", "+--->", "-]===>"},
		{"----", "<---+", "<===[-"}
	};

	float MaxHealth = 200.f;
	float Health = 200.f;

	float MaxMana = 100.f;
	float Mana = 100.f;

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

	Vec2 CollisionOffset = { 1, 2 };

	ULONGLONG HitTick;
	bool Hited = false;

	ULONGLONG DeadTick;
	bool PlayerDead = false;

	ULONGLONG HitTextTick;
	bool DamageTextExist = false;

	int TakeDamage;
	Vec2 HitedPos;

	bool UseSkill = false;
	bool IsCooltime = false;

	bool EnableKeyInput = true;

	ULONGLONG UseSkillTick;
	ULONGLONG SkillMotionTick;
	int SkillMotionIndex = 0;
	ULONGLONG SkillCoolTime;

	ConsoleRenderingColor CurrentPlayerColor;
	ConsoleRenderingColor PlayerDefaultColor = ConsoleRenderingColor::DARKBLUE;
	ConsoleRenderingColor PlayerHitColor = ConsoleRenderingColor::RED;

public:
	bool Collision(Vec2 _Pos);

	void OnHited(int _Damage);

	float GetHPRatio();
	float GetMPRatio();
};

