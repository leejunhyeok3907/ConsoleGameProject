#include "pch.h"
#include "GameOverScene.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

GameOverScene::GameOverScene()
{
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::init()
{
}

void GameOverScene::update()
{
	SUPER::update();

	if (KEY_TAP(KEY_TYPE::Z))
	{
		SceneManager::GetInst()->ChangeScene(SCENE_TYPE::STAGE_01);
	}
}

void GameOverScene::render()
{
	SUPER::render();

	GameManager::GetInst()->PrintScreen(23.f, 5.f, " ####   #    #### ####      ###  #   # #### #### ");
	GameManager::GetInst()->PrintScreen(23.f, 6.f, "#      # #  # # # #        #   # #   # #    #   # ");
	GameManager::GetInst()->PrintScreen(23.f, 7.f, "#  #  ##### # # # ####     #   #  # #  #### ####  ");
	GameManager::GetInst()->PrintScreen(23.f, 8.f, "#   # #   # # # # #        #   #  # #  #    #   # ");
	GameManager::GetInst()->PrintScreen(23.f, 9.f, " ###  #   # # # # ####      ###    #   #### #    #");

	GameManager::GetInst()->PrintScreen(37.f, 20.f, "Press Z to ReStart");
}

void GameOverScene::Enter()
{
}

void GameOverScene::Exit()
{
}
