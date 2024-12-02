#include "pch.h"
#include "StartScene.h"
#include "Player.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::init()
{
}

void StartScene::update()
{
	Scene::update();
}

void StartScene::render()
{
	Scene::render();
}

void StartScene::Enter()
{
	Object* Obj = new Player;

	Obj->SetstrName(L"Player");
	Obj->SetPos(Vec2(5.f, 5.f));

	AddObject(Obj, GROUP_TYPE::PLAYER);

	RegisterPlayer(Obj);
}

void StartScene::Exit()
{
	DeleteAll();
}
