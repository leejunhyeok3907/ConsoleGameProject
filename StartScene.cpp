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
	SUPER::init();
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

	GameManager::GetInst()->PrintScreen(28.f, 5.f,  "###  ###   ####    ####   #    #### ####");
	GameManager::GetInst()->PrintScreen(28.f, 6.f,  "#  # #  # #       #      # #  # # # #   ");
	GameManager::GetInst()->PrintScreen(28.f, 7.f,  "###  ###  #  #    #  #  ##### # # # ####");
	GameManager::GetInst()->PrintScreen(28.f, 8.f,  "#  # #    #   #   #   # #   # # # # #   ");
	GameManager::GetInst()->PrintScreen(28.f, 9.f,  "#  # #     ###     ###  #   # # # # ####");

	GameManager::GetInst()->PrintScreen(40.f, 20.f, "Press Z to Start");
}

void StartScene::Enter()
{
}

void StartScene::Exit()
{
	DeleteAll();
}
