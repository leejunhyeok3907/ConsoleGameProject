#pragma once
#include "Scene.h"
class Stage02 :
    public Scene
{
private:
	using SUPER = Scene;

public:
	Stage02();
	virtual ~Stage02();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

