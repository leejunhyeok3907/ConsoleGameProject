#pragma once
#include "Scene.h"
class Stage01 : public Scene
{
private:
	using SUPER = Scene;

public:
	Stage01();
	virtual ~Stage01();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

