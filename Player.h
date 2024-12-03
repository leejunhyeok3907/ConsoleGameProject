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

	Vec2 UnderCollision;
};

