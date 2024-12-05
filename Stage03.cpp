#include "pch.h"
#include "Stage03.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"
#include "PlayerUI.h"
#include "Portal.h"

Stage03::Stage03()
{
}

Stage03::~Stage03()
{
}

void Stage03::init()
{
	SUPER::init();
}

void Stage03::update()
{
	SUPER::update();
}

void Stage03::render()
{
	SUPER::render();
}

void Stage03::Enter()
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(90.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new PlayerUI;
	AddObject(Obj, GROUP_TYPE::UI);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(37.f, ScreenSize.y - 9));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(15.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(35.f, ScreenSize.y - 8), Vec2(40.f, ScreenSize.y - 7));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(25.f, ScreenSize.y - 14), Vec2(30.f, ScreenSize.y - 13));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(15.f, ScreenSize.y - 20), Vec2(20.f, ScreenSize.y - 19));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Portal(Vec2(18.f, ScreenSize.y - 21), SCENE_TYPE::STAGE_04);

	AddObject(Obj, GROUP_TYPE::PORTAL);

	init();
}

void Stage03::Exit()
{
	DeleteAll();
}
