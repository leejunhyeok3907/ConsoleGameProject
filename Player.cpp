#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Ground.h"
#include "Monster.h"

Player::Player()
{
}

Player::~Player()
{
}

void Player::init()
{
    CurrentPlayerColor = PlayerDefaultColor;
}

void Player::update()
{
    ULONGLONG Current_tick = GetTickCount64();

    if (KEY_HOLD(KEY_TYPE::LEFT))
    {
        if (IsInScreen(m_Pos.x - 0.5f, m_Pos.y))
        {
            m_DirRight = false;
            m_Pos.x -= 0.5f;
        }
    }
    if (KEY_HOLD(KEY_TYPE::RIGHT))
    {
        if (IsInScreen(m_Pos.x + 0.5f, m_Pos.y))
        {
            m_DirRight = true;
            m_Pos.x += 0.5f;
        }
    }
    if (KEY_HOLD(KEY_TYPE::UP))
    {
        if (IsInScreen(m_Pos.x, m_Pos.y - 1))
        {
            if (Jumping == false && IsGrounded)
            {
                JumpTick = ReduceJumpPowerTick = Current_tick;
                Jumping = true;
                JumpPower = 0.75f;
                Gravity = 0.f;
            }
        }
    }

    if (KEY_TAP(KEY_TYPE::Z))
    {
        if (Attacking == false)
        {
            AttackTick = Current_tick;
            Attacking = true;

            CheckAttack();
        }
    }

    if (Jumping)
    {
        m_Pos.y -= JumpPower;

        if (ReduceJumpPowerTick + 30 <= Current_tick)
        {
            ReduceJumpPowerTick = GetTickCount64();
            JumpPower = (JumpPower - 0.1f > 0) ? JumpPower - 0.1f : 0.f;
        }

        if (JumpTick + 300 <= Current_tick)
        {
            Jumping = false;
        }
    }

    if (Attacking)
    {
        if (AttackTick + 100 <= Current_tick)
        {
            Attacking = false;
        }
    }

    if (Hited)
    {
        if (HitTick + 100 <= Current_tick)
        {
            Hited = false;
            CurrentPlayerColor = PlayerDefaultColor;
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

                if (Jumping == false)
                {
                    m_Pos.y = _Ground->GetLeftTop().y - 1;
                }
                break;
            }
        }
    }
    
    if (IsGrounded == false && Jumping == false)
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
    GameManager::GetInst()->ChangeRenderColor(CurrentPlayerColor, ConsoleRenderingType::TEXT);
	

    DrawCharacter();
    //GameManager::GetInst()->PrintScreen(m_Pos.x, m_Pos.y, L"a");

    GameManager::GetInst()->ResumeRenderColor();
}

void Player::DrawCharacter()
{
    if (Attacking == false)
    {
        if (m_DirRight == false)
        {
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, "  O  ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, " o|) ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y,     " _^_ ");
        }
        else
        {
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, "  O  ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, " (|o ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y,     " _^_ ");
        }

        if (!m_EquipWeapon)
        {
            string drawWeapon = WeaponArr[m_DirRight ? 0 : 1][2];
            int AddOffset = 0;

            if (m_DirRight)
            {
                AddOffset = 3;
            }
            else
            {
                AddOffset = drawWeapon.size() * -1;
            }

            GameManager::GetInst()->PrintScreen(m_Pos.x + AddOffset, m_Pos.y - 1, drawWeapon);
        }
    }
    else
    {
        if (m_DirRight == false)
        {
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, "  O  ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, "o=|) ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y,     " _^_ ");
        }
        else
        {
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, "  O  ");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, " (|=o");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y,     " _^_ ");
        }

        if (!m_EquipWeapon)
        {
            string drawWeapon = WeaponArr[m_DirRight ? 0 : 1][WeaponIndex];
            int AddOffset = 0;

            if (m_DirRight)
            {
                AddOffset = 4;
            }
            else
            {
                AddOffset = -1 + drawWeapon.size() * -1;
            }

            GameManager::GetInst()->PrintScreen(m_Pos.x + AddOffset, m_Pos.y - 1, drawWeapon);     
        }
    }
}

void Player::CheckAttack()
{
    int WeaponSize = WeaponArr[0][WeaponIndex].size();

    const vector<Object*>& Monsters = SceneManager::GetInst()->GetCurScene()->
        GetGroupObject(GROUP_TYPE::MONSTER);

    for (auto Obj : Monsters)
    {
        Monster* Mon = dynamic_cast<Monster*>(Obj);

        if (Mon)
        {
            int AddOffset = m_DirRight ? 4 : -1;

            for (int i = 0; i < WeaponSize; i++)
            {
                int RangeOffset = m_DirRight ? i : i * -1;

                if (Mon->Collision({ m_Pos.x + AddOffset + RangeOffset, m_Pos.y }))
                {
                    Mon->OnHited(50.f);
                    break;
                }
            }
        }
    }
}

bool Player::Collision(Vec2 _Pos)
{
    return (_Pos.x >= m_Pos.x - CollisionOffset.x && _Pos.x <= m_Pos.x + CollisionOffset.x
        && _Pos.y >= m_Pos.y - CollisionOffset.y && _Pos.y <= m_Pos.y);
}

void Player::OnHited(float _Damage)
{
    if (Hited == false)
    {
        Hited = true;
        HitTick = GetTickCount64();

        CurrentPlayerColor = PlayerHitColor;
    }
}
