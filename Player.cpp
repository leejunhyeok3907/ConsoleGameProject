#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "GameManager.h"

Player::Player()
    : m_Pos(5, 5)
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
    if (KeyManager::GetInst()->GetKeyState(KEY_TYPE::LEFT) == KEY_STATE::HOLD)
    {
        if (m_Pos.x > 0)
        {
            m_Pos.x--;
        }
    }
    if (KeyManager::GetInst()->GetKeyState(KEY_TYPE::RIGHT) == KEY_STATE::HOLD)
    {
        if (m_Pos.x < 20)
        {
            m_Pos.x++;
        }
    }
    if (KeyManager::GetInst()->GetKeyState(KEY_TYPE::UP) == KEY_STATE::HOLD)
    {
        if (m_Pos.y > 0)
        {
            m_Pos.y--; 
        }
    }
    if (KeyManager::GetInst()->GetKeyState(KEY_TYPE::DOWN) == KEY_STATE::HOLD)
    {
        if (m_Pos.y < 15)
        {
            m_Pos.y++;
        }
    }
}

void Player::render()
{
	GameManager::GetInst()->PrintScreen(m_Pos.x, m_Pos.y, L"a");
}
