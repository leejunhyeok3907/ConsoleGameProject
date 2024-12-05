#pragma once
#include "Scene.h"
class GameOverScene : public Scene
{
private:
	using SUPER = Scene;

public:
	GameOverScene();
	virtual ~GameOverScene();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

