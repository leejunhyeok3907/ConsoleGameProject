#pragma once
#include "Scene.h"
class StartScene : public Scene
{
public:
	StartScene();
	virtual ~StartScene();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

