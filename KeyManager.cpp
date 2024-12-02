#include "pch.h"
#include "KeyManager.h"
#include "GameManager.h"

int g_arrVk[(UINT)KEY_TYPE::END] = {
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,
	'Z',
	'X',
	'C',
	'Q',
	VK_SPACE,
};

KeyManager::KeyManager()
{

}

KeyManager::~KeyManager()
{

}

void KeyManager::Init()
{
	for (int i = 0; i < (UINT)KEY_TYPE::END; i++)
	{
		m_Keys.push_back(KeyInfo({ KEY_STATE::NONE, false }));
	}
}

void KeyManager::Update()
{
	HWND MainConsole = GameManager::GetInst()->GetConsoleHWND();

	for (int i = 0; i < (UINT)KEY_TYPE::END; i++)
	{
		if (GetAsyncKeyState(g_arrVk[i]) & 0x8000)
		{
			if (m_Keys[i].prevPushed)
			{
				m_Keys[i].state = KEY_STATE::HOLD;
			}
			else
			{
				m_Keys[i].state = KEY_STATE::TAP;
			}

			m_Keys[i].prevPushed = true;
		}
		else
		{
			if (m_Keys[i].prevPushed)
			{
				m_Keys[i].state = KEY_STATE::AWAY;
			}
			else
			{
				m_Keys[i].state = KEY_STATE::NONE;
			}

			m_Keys[i].prevPushed = false;
		}
	}
	//else
	//{
	//	for (int i = 0; i < (UINT)KEY_TYPE::END; i++)
	//	{
	//		if (m_Keys[i].state == KEY_STATE::TAP 
	//			|| m_Keys[i].state == KEY_STATE::HOLD)
	//		{
	//			m_Keys[i].state = KEY_STATE::AWAY;
	//		}
	//		else if (m_Keys[i].state == KEY_STATE::AWAY)
	//		{
	//			m_Keys[i].state = KEY_STATE::NONE;
	//		}
	//	}
	//}
}

void KeyManager::Render()
{
}