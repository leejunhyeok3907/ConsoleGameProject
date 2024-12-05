#include "pch.h"
#include "EndScene.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"

EndScene::EndScene()
{
}

EndScene::~EndScene()
{
}

void EndScene::init()
{
}

void EndScene::update()
{
	SUPER::update();

	if (KEY_TAP(KEY_TYPE::Z))
	{
		SceneManager::GetInst()->ChangeScene(SCENE_TYPE::START);
	}
}

void EndScene::render()
{
	SUPER::render();

	GameManager::GetInst()->PrintScreen(23.f, 5.f, "#   #  ###  #   #  ");
	GameManager::GetInst()->PrintScreen(23.f, 6.f, "#   # #   # #   #  ");
	GameManager::GetInst()->PrintScreen(23.f, 7.f, " # #  #   # #   #  ");
	GameManager::GetInst()->PrintScreen(23.f, 8.f, "  #   #   # #   #  ");
	GameManager::GetInst()->PrintScreen(23.f, 9.f, "  #    ###   ###   ");

	GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::DARKBLUE, ConsoleRenderingType::TEXT);
	GameManager::GetInst()->PrintScreen(46.f, 5.f, "#  #  # ##### ##    #  ##");
	GameManager::GetInst()->PrintScreen(46.f, 6.f, "#  #  #   #   # #   #  ##");
	GameManager::GetInst()->PrintScreen(46.f, 7.f, "#  #  #   #   #  #  #  ##");
	GameManager::GetInst()->PrintScreen(46.f, 8.f, " # # #    #   #   # #    ");
	GameManager::GetInst()->PrintScreen(46.f, 9.f, "  # #   ##### #    ##  ##");

	GameManager::GetInst()->ResumeRenderColor();
	GameManager::GetInst()->PrintScreen(37.f, 20.f, "Press Z to Title");
}

void EndScene::Enter()
{
}

void EndScene::Exit()
{
}
