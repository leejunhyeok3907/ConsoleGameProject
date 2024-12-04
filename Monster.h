#pragma once
#include "Object.h"
class Monster : public Object
{
public:
	Monster();
	virtual ~Monster();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	virtual void DrawCharacter();

private:
	float MaxGravity = 0.6f;
	float Gravity = 0.4f;
	bool IsGrounded = false;

	ULONGLONG JumpTick;
	bool Jumping = false;
	ULONGLONG ReduceJumpPowerTick;
	float JumpPower;

	ULONGLONG MoveTick;
	int NextMove = 2400;

	Vec2 UnderCollision;

	Vec2 CollisionOffset = { 2, 1 };

	Object* Target;

	ULONGLONG HitTick;
	bool Hited = false;

public:
	bool Collision(Vec2 _Pos);

	void OnHited(float _Damage);
};

