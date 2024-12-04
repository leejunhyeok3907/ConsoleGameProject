#include "pch.h"
#include "Ground.h"
#include "GameManager.h"

Ground::Ground()
{
}

Ground::Ground(Vec2 _LeftTop, Vec2 _RightBottom)
	: m_LeftTop(_LeftTop), m_RightBottom(_RightBottom)
{
}

Ground::~Ground()
{
}

void Ground::init()
{
}

void Ground::update()
{
}

void Ground::render()
{
	GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::DARKGREEN, ConsoleRenderingType::TEXT);

	for (int y = m_LeftTop.y; y <= m_RightBottom.y; y++)
	{
		for (int x = m_LeftTop.x; x <= m_RightBottom.x; x += 2)
		{
			GameManager::GetInst()->PrintScreen(x, y, "бр");
		}
	}

	GameManager::GetInst()->ResumeRenderColor();
}

bool Ground::IsCollision(const Vec2& _pos)
{
	return ((_pos.x >= m_LeftTop.x && _pos.x <= m_RightBottom.x)
		&& (_pos.y >= m_LeftTop.y && _pos.y <= m_RightBottom.y));
}
