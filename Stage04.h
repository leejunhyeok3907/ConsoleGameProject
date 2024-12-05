#pragma once
#include "Scene.h"
class Stage04 :
    public Scene
{
private:
	using SUPER = Scene;

public:
	Stage04();
	virtual ~Stage04();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

