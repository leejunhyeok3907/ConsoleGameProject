#include "pch.h"
#include "PlayerUI.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Player.h"
#include "GameManager.h"

PlayerUI::PlayerUI()
{
}

PlayerUI::~PlayerUI()
{
}

void PlayerUI::init()
{
	UITarget = dynamic_cast<Player*>(SceneManager::GetInst()->GetCurScene()->GetPlayer());
}

void PlayerUI::update()
{
	ULONGLONG CurrentTick = GetTickCount64();

	if (UITarget->GetHPRatio() < 3)
	{
		if (Alert == false)
		{
			Alert = true;
			AlertTick = CurrentTick;
			TransientHP = false;
		}
	}
	else
	{
		Alert = false;

		TransientHP = false;
	}

	if (Alert)
	{
		if (AlertTick + 100 <= CurrentTick)
		{
			TransientHP = TransientHP ? false : true;

			AlertTick = CurrentTick;
		}
	}
}

void PlayerUI::render()
{
	if (UITarget == nullptr) return;

	GameManager::GetInst()->PrintScreen(0, 0, "========================");
	GameManager::GetInst()->PrintScreen(0, 1, "=                      =");
	GameManager::GetInst()->PrintScreen(0, 2, "=                      =");
	GameManager::GetInst()->PrintScreen(0, 3, "========================");

	int MAXCount = 10;
	int HP_Count = UITarget->GetHPRatio();
	int MP_Count = UITarget->GetMPRatio();

	Vec2 HP_Pos = { 2, 1 };
	Vec2 MP_Pos = { 2, 2 };

	if (TransientHP == false)
	{
		GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::RED, ConsoleRenderingType::TEXT);
		for (int i = 0; i < 10; i++)
		{
			string DrawStr = (HP_Count > i) ? "бс" : "бр";

			GameManager::GetInst()->PrintScreen(HP_Pos.x + (i * 2), HP_Pos.y, DrawStr);
		}
	}

	GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::BLUE, ConsoleRenderingType::TEXT);
	for (int i = 0; i < 10; i++)
	{
		string DrawStr = (MP_Count > i) ? "бс" : "бр";

		GameManager::GetInst()->PrintScreen(MP_Pos.x + (i * 2), MP_Pos.y, DrawStr);
	}

	GameManager::GetInst()->ResumeRenderColor();
}
