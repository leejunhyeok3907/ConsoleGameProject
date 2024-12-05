#include "pch.h"
#include "DispearGround.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameManager.h"
#include "Player.h"

DispearGround::DispearGround()
{
}

DispearGround::DispearGround(Vec2 _LeftTop, Vec2 _RightBottom)
	: Ground(_LeftTop, _RightBottom)
{
}

DispearGround::~DispearGround()
{
}

void DispearGround::init()
{
	player = SceneManager::GetInst()->GetCurScene()->GetPlayer();

	CurrentColor = ConsoleRenderingColor::GRAY;
}

void DispearGround::update()
{
	ULONGLONG CurrentTick = GetTickCount64();

	Vec2 Pos = player->GetPos();

	if (Collision == false && IsCollision(Vec2(Pos.x, Pos.y + 1)))
	{
		Collision = true;
		DisapearTick = CurrentTick;
		ChangeColorTick = CurrentTick;
	}

	if (Collision)
	{
		if (ChangeColorTick + 150 <= CurrentTick)
		{
			ChangeColorTick = CurrentTick;
			CurrentColor = bChanged ? ConsoleRenderingColor::GRAY : ConsoleRenderingColor::DARKGRAY;
			bChanged = bChanged ? false : true;
		}

		if (Regen == false)
		{
			if (DisapearTick + 3000 <= CurrentTick)
			{
				BeforeLeftTop = m_LeftTop;
				BeforeRightBottom = m_RightBottom;

				m_LeftTop = Vec2({ 0, 0 });
				m_RightBottom = Vec2({ 0, 0 });

				RegenTick = CurrentTick;
				Regen = true;
			}
		}
	}

	if (Regen)
	{
		if (RegenTick + 5000 <= CurrentTick)
		{
			Regen = false;
			Collision = false;
			CurrentColor = ConsoleRenderingColor::GRAY;

			m_LeftTop = BeforeLeftTop;
			m_RightBottom = BeforeRightBottom;
		}
	}
}

void DispearGround::render()
{
	GameManager::GetInst()->ChangeRenderColor(CurrentColor, ConsoleRenderingType::TEXT);

	for (int y = m_LeftTop.y; y <= m_RightBottom.y; y++)
	{
		for (int x = m_LeftTop.x; x <= m_RightBottom.x; x += 2)
		{
			GameManager::GetInst()->PrintScreen(x, y, "бр");
		}
	}

	GameManager::GetInst()->ResumeRenderColor();
}
