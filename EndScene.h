#pragma once
#include "Scene.h"
class EndScene :
    public Scene
{
private:
	using SUPER = Scene;

public:
	EndScene();
	virtual ~EndScene();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

