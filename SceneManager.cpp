#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

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
