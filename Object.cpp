#include "pch.h"
#include "Object.h"
#include "GameManager.h"

Object::Object()
	: m_Pos{}
	, m_bAlive(true)
{
}

Object::~Object()
{
}

bool Object::IsInScreen(int _nx, int _ny)
{
	Vec2 ScreenSize = GameManager::GetInst()->GetScreenSize();
	
	return ((_nx >= 0 && _nx < ScreenSize.x)
		&& (_ny >= 0 && _ny < ScreenSize.y));
}
