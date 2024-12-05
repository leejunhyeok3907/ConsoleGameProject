#pragma once
#include "Scene.h"
class Stage05 :
    public Scene
{
private:
	using SUPER = Scene;

public:
	Stage05();
	virtual ~Stage05();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;

private:
	class Object* GameBoss;

	bool WinCheck = false;
	ULONGLONG DelayTick;
};

