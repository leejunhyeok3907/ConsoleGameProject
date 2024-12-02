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
	Vec2 m_Pos;
};

