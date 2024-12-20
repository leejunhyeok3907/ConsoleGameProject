#include "pch.h"
#include "Stage01.h"
#include "Player.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "KeyManager.h"
#include "Ground.h"
#include "Monster.h"
#include "PlayerUI.h"
#include "Portal.h"
#include "Boss.h"


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

	GameManager::GetInst()->PrintScreen(30.f, 10.f, "Key Menual");
	GameManager::GetInst()->PrintScreen(30.f, 11.f, "Left:�� Right:�� Jump:��");
	GameManager::GetInst()->PrintScreen(30.f, 12.f, "Attack: Z  Meditation : X");
}

void Stage01::Enter()
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();

	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(15.f, ScreenSize.y - 4));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);

	Obj = new PlayerUI;
	AddObject(Obj, GROUP_TYPE::UI);

	Obj = new Ground(Vec2(0.f, ScreenSize.y - 3), Vec2(ScreenSize.x - 1, ScreenSize.y - 1));

	AddObject(Obj, GROUP_TYPE::GROUND);

	Obj = new Portal(Vec2(90.f, ScreenSize.y - 4), SCENE_TYPE::STAGE_02);

	AddObject(Obj, GROUP_TYPE::PORTAL);

	init();
}

void Stage01::Exit()
{
	DeleteAll();
}
