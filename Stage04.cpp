#include "pch.h"
#include "Stage04.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"
#include "PlayerUI.h"
#include "Portal.h"
#include "DispearGround.h"

Stage04::Stage04()
{
}

Stage04::~Stage04()
{
}

void Stage04::init()
{
	SUPER::init();
}

void Stage04::update()
{
	SUPER::update();
}

void Stage04::render()
{
	SUPER::render();
}

void Stage04::Enter()
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(90.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new PlayerUI;
	AddObject(Obj, GROUP_TYPE::UI);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 21), Vec2(15.f, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(ScreenSize.x - 16, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(66.f, ScreenSize.y - 6), Vec2(74.f, ScreenSize.y - 5));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(46.f, ScreenSize.y - 12), Vec2(54.f, ScreenSize.y - 11));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new DispearGround(Vec2(26.f, ScreenSize.y - 18), Vec2(34.f, ScreenSize.y - 17));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(26.f, ScreenSize.y - 19));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Portal(Vec2(7.f, ScreenSize.y - 22), SCENE_TYPE::STAGE_05);

	AddObject(Obj, GROUP_TYPE::PORTAL);

	init();
}

void Stage04::Exit()
{
	DeleteAll();
}
