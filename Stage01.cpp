#include "pch.h"
#include "Stage01.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"


Stage01::Stage01()
{
}

Stage01::~Stage01()
{
}

void Stage01::init()
{
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

	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Ground(Vec2(25.f, ScreenSize.y - 8), Vec2(35.f, ScreenSize.y - 7));

	AddObject(Obj, GROUP_TYPE::GROUND);
}

void Stage01::Exit()
{
	DeleteAll();
}
