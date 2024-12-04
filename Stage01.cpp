#include "pch.h"
#include "Stage01.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"


Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::init()
{
	SUPER::init();
}

void Stage01::update()
{
	SUPER::update();
}

void Stage01::render()
{
	SUPER::render();
}

void Stage01::Enter()
{
	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(15.f, 5.f));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(65.f, 5.f));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(70.f, 5.f));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(75.f, 5.f));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Obj = new Monster;

	Obj->SetstrName(L"Slime");
	Obj->SetPos(Vec2(80.f, 5.f));

	AddObject(Obj, GROUP_TYPE::MONSTER);

	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(25.f, ScreenSize.y - 8), Vec2(35.f, ScreenSize.y - 7));

	AddObject(Obj, GROUP_TYPE::GROUND);

	init();
}

void Stage01::Exit()
{
	DeleteAll();
}
