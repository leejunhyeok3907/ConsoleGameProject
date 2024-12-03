#include "pch.h"
#include "StartScene.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::init()
{
}

void StartScene::update()
{
	SUPER::update();

	if (KEY_TAP(KEY_TYPE::Z))
	{
		SceneManager::GetInst()->ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void StartScene::render()
{
	SUPER::render();

	GameManager::GetInst()->PrintScreen(20.f, 5.f, "asdf");
}

void StartScene::Enter()
{
}

void StartScene::Exit()
{
	

	DeleteAll();
}
