#pragma once
#include "Object.h"
class PlayerUI :
    public Object
{
public:
	PlayerUI();
	virtual ~PlayerUI();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

private:
	class Player* UITarget;

private:
	ULONGLONG AlertTick;
	bool Alert;

	bool TransientHP;
	bool TransientMP;
};

