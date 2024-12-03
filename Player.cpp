#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Ground.h"

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
            m_DirRight = false;
            m_Pos.x--;
        }
    }
    if (KEY_HOLD(KEY_TYPE::RIGHT))
    {
        if (IsInScreen(m_Pos.x + 1, m_Pos.y))
        {
            m_DirRight = true;
            m_Pos.x++;
        }
    }
    if (KEY_HOLD(KEY_TYPE::UP))
    {
        if (IsInScreen(m_Pos.x, m_Pos.y - 1))
        {
            IsGrounded = false;
            m_Pos.y--;
        }
    }

    UnderCollision = Vec2(m_Pos.x, m_Pos.y + 1);

    const vector<Object*>& Grounds = SceneManager::GetInst()->GetCurScene()->
        GetGroupObject(GROUP_TYPE::GROUND);

    IsGrounded = false;

    for (auto Obj : Grounds)
    {
        Ground* _Ground = dynamic_cast<Ground*>(Obj);

        if (_Ground)
        {
            if (_Ground->IsCollision({ UnderCollision.x, UnderCollision.y }))
            {
                Gravity = 0.f;
                IsGrounded = true;

                m_Pos.y = _Ground->GetLeftTop().y - 1;
                break;
            }
        }
    }

    if (IsGrounded == false)
    {
        if (Gravity < MaxGravity)
        {
            Gravity += 0.02f;

            if (Gravity > MaxGravity)
            {
                Gravity = MaxGravity;
            }
        }

        m_Pos.y += Gravity;
    }
}

void Player::render()
{
    GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::BLUE, ConsoleRenderingType::TEXT);
	

    DrawCharacter();
    //GameManager::GetInst()->PrintScreen(m_Pos.x, m_Pos.y, L"a");

    GameManager::GetInst()->ResumeRenderColor();
}

void Player::DrawCharacter()
{
    if (m_DirRight == false)
    {
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, " O ");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, "o|)");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y    , "_^_");
    }
    else
    {
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, " O ");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, "(|o");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y    , "_^_");
    }

    if (!m_EquipWeapon)
    {
        string drawWeapon = WeaponArr[m_DirRight ? 0 : 1][2];
        int AddOffset = 0;

        if (m_DirRight)
        {
            AddOffset = 2;
        }
        else
        {
            AddOffset = -2 - drawWeapon.size() + 1;
        }

        GameManager::GetInst()->PrintScreen(m_Pos.x + AddOffset, m_Pos.y - 1, drawWeapon);
    }
}
