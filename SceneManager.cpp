#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "StartScene.h"
#include "Stage01.h"
#include "Stage02.h"
#include "Stage03.h"
#include "Stage04.h"
#include "Stage05.h"
#include "EndScene.h"
#include "GameOverScene.h"

SceneManager::SceneManager()
	: m_arrScene{}
	, m_CurScene(nullptr)
{

}

SceneManager::~SceneManager()
{
	//Scene 전부 삭제

	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; i++)
	{
		if (nullptr != m_arrScene[i])
		{
			delete m_arrScene[i];
		}
	}
}

void SceneManager::Init()
{
	m_arrScene[(UINT)SCENE_TYPE::START] = new StartScene;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new Stage01;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new Stage02;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_03] = new Stage03;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_04] = new Stage04;

	m_arrScene[(UINT)SCENE_TYPE::STAGE_05] = new Stage05;

	m_arrScene[(UINT)SCENE_TYPE::WIN] = new EndScene;

	m_arrScene[(UINT)SCENE_TYPE::GAMEOVER] = new GameOverScene;

	m_CurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_CurScene->Enter();
}

void SceneManager::Update()
{
	if (m_CurScene)
	{
		m_CurScene->update();
	}
}

void SceneManager::Render()
{
	if(m_CurScene)
	{
		m_CurScene->render();
	}
}

void SceneManager::ChangeScene(SCENE_TYPE _eNext)
{
	m_CurScene->Exit();

	m_CurScene = m_arrScene[(UINT)_eNext];

	m_CurScene->Enter();
}
