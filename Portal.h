#pragma once
#include "Object.h"
class Portal :
    public Object
{
public:
	Portal();
	Portal(Vec2 _Pos, SCENE_TYPE _NextLevel);
	virtual ~Portal();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	SCENE_TYPE NextLevel;

	class Object* Player;

	ULONGLONG CollisionTick;
	bool IsCollision;

private:
	bool CollisionCheck();
};

