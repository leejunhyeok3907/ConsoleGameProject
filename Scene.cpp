#include "pch.h"
#include "Scene.h"
#include "Object.h"
#include "Functions.h"

Scene::Scene()
	: m_Player(nullptr)
{
}

Scene::~Scene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_Obj[i].size(); j++)
		{
			// m_arrObj[i] 그룹 벡터의 j물체 삭제
			delete m_Obj[i][j];
			m_Obj[i][j] = nullptr;
		}
	}
}

void Scene::init()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_Obj[i].size(); j++)
		{
			m_Obj[i][j]->init();
		}
	}
}

void Scene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_Obj[i].size(); j++)
		{
			if (!m_Obj[i][j]->IsDead())
			{
				m_Obj[i][j]->update();
			}
		}
	}
}

void Scene::render()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		vector<Object*>::iterator iter = m_Obj[i].begin();

		for (; iter != m_Obj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render();
				iter++;
			}
			else
			{
				iter = m_Obj[i].erase(iter);
			}
		}
	}
}

void Scene::DeleteGroup(GROUP_TYPE _eType)
{
	Safe_Delete_Vec(m_Obj[(UINT)_eType]);
}

void Scene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}
