#include "pch.h"
#include "Stage02.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"
#include "PlayerUI.h"
#include "Portal.h"

Stage02::Stage02()
{
}

Stage02::~Stage02()
{
}

void Stage02::init()
{
	SUPER::init();
}

void Stage02::update()
{
	SUPER::update();
}

void Stage02::render()
{
	SUPER::render();
}

void Stage02::Enter()
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(15.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new PlayerUI;
	AddObject(Obj, GROUP_TYPE::UI);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(65.f, 5.f));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Portal(Vec2(90.f, ScreenSize.y - 4), SCENE_TYPE::STAGE_03);

	AddObject(Obj, GROUP_TYPE::PORTAL);

	init();
}

void Stage02::Exit()
{
	DeleteAll();
}
