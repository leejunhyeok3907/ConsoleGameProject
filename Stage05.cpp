#include "pch.h"
#include "Stage05.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"
#include "PlayerUI.h"
#include "Portal.h"
#include "DispearGround.h"
#include "Boss.h"

Stage05::Stage05()
{
}

Stage05::~Stage05()
{
}

void Stage05::init()
{
	SUPER::init();
}

void Stage05::update()
{
	SUPER::update();

	if (GameBoss)
	{
		if (WinCheck == false)
		{
			if (GameBoss->IsDead())
			{
				WinCheck = true;
				DelayTick = GetTickCount64();
			}
		}
	}

	if (WinCheck)
	{
		if (DelayTick + 1000 <= GetTickCount64())
		{
			SceneManager::GetInst()->ChangeScene(SCENE_TYPE::WIN);
		}
	}
}

void Stage05::render()
{
	SUPER::render();
}

void Stage05::Enter()
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(15.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new PlayerUI;
	AddObject(Obj, GROUP_TYPE::UI);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 16, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 9), Vec2(15.f, ScreenSize.y - 8));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 15), Vec2(15.f, ScreenSize.y - 14));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(ScreenSize.x - 16, ScreenSize.y - 21), Vec2(ScreenSize.x - 1, ScreenSize.y - 20));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(66.f, ScreenSize.y - 18), Vec2(74.f, ScreenSize.y - 17));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(46.f, ScreenSize.y - 18), Vec2(54.f, ScreenSize.y - 17));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(26.f, ScreenSize.y - 18), Vec2(34.f, ScreenSize.y - 17));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Boss;

	Obj->SetstrName(L"Boss");
	Obj->SetPos(Vec2(55.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	GameBoss = Obj;

	init();
}

void Stage05::Exit()
{
	DeleteAll();
}
