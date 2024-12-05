#pragma once
#include "Ground.h"
class DispearGround :
    public Ground
{
public:
	DispearGround();
	DispearGround(Vec2 _LeftTop, Vec2 _RightBottom);
	virtual ~DispearGround();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	Vec2 BeforeLeftTop;
	Vec2 BeforeRightBottom;

	class Object* player;

	bool Collision = false;

	ULONGLONG ChangeColorTick;

	bool bChanged=false;

	ConsoleRenderingColor CurrentColor;

	bool Regen = false;

	ULONGLONG RegenTick;

	ULONGLONG DisapearTick;
};

