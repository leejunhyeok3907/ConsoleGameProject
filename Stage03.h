#pragma once
#include "Scene.h"
class Stage03 :
    public Scene
{
private:
	using SUPER = Scene;

public:
	Stage03();
	virtual ~Stage03();

	virtual void init() override;
	virtual void update() override;
	virtual void render() override;

	virtual void Enter() override;
	virtual void Exit() override;
};

