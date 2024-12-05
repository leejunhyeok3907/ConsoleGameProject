#include "pch.h"
#include "Portal.h"
#include "Scene.h"
#include "SceneManager.h"
#include "GameManager.h"

Portal::Portal()
{
}

Portal::Portal(Vec2 _Pos, SCENE_TYPE _NextLevel)
{
	m_Pos = _Pos;

	NextLevel = _NextLevel;
}

Portal::~Portal()
{
}

void Portal::init()
{
	Player = SceneManager::GetInst()->GetCurScene()->GetPlayer();
}

void Portal::update()
{
	ULONGLONG CurrentTick = GetTickCount64();

	if (IsCollision==false && CollisionCheck())
	{
		IsCollision = true;

		SceneManager::GetInst()->ChangeScene(NextLevel);
	}
}

void Portal::render()
{
	GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::YELLOW, ConsoleRenderingType::TEXT);

	GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y-2, "[ | ]");
	GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y-1, "[ | ]");
	GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y,   "[ | ]");

	GameManager::GetInst()->ResumeRenderColor();
}

bool Portal::CollisionCheck()
{
	if (Player)
	{
		Vec2 Pos = Player->GetPos();

		return ((Pos.x >= m_Pos.x - 1 && Pos.x <= m_Pos.x + 1)
			&& (Pos.y >= m_Pos.y - 2 && Pos.y <= m_Pos.y));
	}

	return false;
}
