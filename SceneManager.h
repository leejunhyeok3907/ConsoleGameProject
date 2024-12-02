#pragma once
#include "Manager.h"

class Scene;

class SceneManager : public Manager
{
	SINGLE(SceneManager);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;

private:
	Scene* m_arrScene[(UINT)SCENE_TYPE::END];//모든 Scene의 목록
	Scene* m_CurScene;//현재 Scene

public:
	Scene* GetCurScene() { return m_CurScene; }

	void ChangeScene(SCENE_TYPE _eNext);
};

