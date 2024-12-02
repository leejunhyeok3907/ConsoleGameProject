#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "GameManager.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
}

void Player::update()
{
    if (KEY_HOLD(KEY_TYPE::LEFT))
    {
        if (IsInScreen(m_Pos.x - 1, m_Pos.y))
        {
            m_Pos.x--;
        }
    }
    if (KEY_HOLD(KEY_TYPE::RIGHT))
    {
        if (IsInScreen(m_Pos.x + 1, m_Pos.y))
        {
            m_Pos.x++;
        }
    }
    if (KEY_HOLD(KEY_TYPE::UP))
    {
        if (IsInScreen(m_Pos.x, m_Pos.y - 1))
        {
            m_Pos.y--; 
        }
    }
    if (KEY_HOLD(KEY_TYPE::DOWN))
    {
        if (IsInScreen(m_Pos.x, m_Pos.y + 1))
        {
            m_Pos.y++;
        }
    }
}

void Player::render()
{
    GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::BLUE, ConsoleRenderingType::TEXT);
	GameManager::GetInst()->PrintScreen(m_Pos.x, m_Pos.y, L"a");
}
