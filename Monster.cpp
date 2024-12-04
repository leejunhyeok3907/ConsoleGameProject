#include "pch.h"
#include "Monster.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Ground.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::init()
{
    Target = SceneManager::GetInst()->GetCurScene()->GetPlayer();

    MoveTick = GetTickCount64();

    NextMove = rand() % 1400 + 200;
}

void Monster::update()
{
    ULONGLONG Current_tick = GetTickCount64();

    if (Hited == false)
    {
        if (MoveTick + NextMove <= Current_tick)
        {
            NextMove = (rand() % 1400) + 600;

            MoveTick = Current_tick;

            if (Jumping == false && IsGrounded)
            {
                JumpTick = ReduceJumpPowerTick = Current_tick;
                Jumping = true;
                JumpPower = 0.45f;
                Gravity = 0.f;
            }
        }
    }
    else
    {
        JumpTick = ReduceJumpPowerTick = Current_tick;
        Jumping = true;
        JumpPower = 0.25f;
        Gravity = 0.f;
    }

    if (Jumping)
    {
        if (Hited == false)
        {
            m_Pos.x -= (Target->GetPos().x < m_Pos.x) ? 1.f : -1.f;
        }
        else
        {
            m_Pos.x -= (Target->GetPos().x < m_Pos.x) ? -1.f : 1.f;
        }

        m_Pos.y -= JumpPower;

        if (ReduceJumpPowerTick + 30 <= Current_tick)
        {
            ReduceJumpPowerTick = GetTickCount64();
            JumpPower = (JumpPower - 0.1f > 0) ? JumpPower - 0.1f : 0.f;
        }

        if (JumpTick + 100 <= Current_tick)
        {
            Jumping = false;
        }
    }

    if (Hited)
    {
        if (HitTick + 100 <= Current_tick)
        {
            Hited = false;
            Jumping = false;
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

void Monster::render()
{
    DrawCharacter();
}

void Monster::DrawCharacter()
{
    if (IsGrounded)
    {
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y - 2, " ___ ");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y - 1, "(   )");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y,     "-----");
    }
    else
    {
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y - 2, " ___ ");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y - 1, "[   ]");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 2, m_Pos.y,     "'---'");
    }
}

bool Monster::Collision(Vec2 _Pos)
{
    return (_Pos.x >= m_Pos.x - CollisionOffset.x && _Pos.x <= m_Pos.x + CollisionOffset.x
        && _Pos.y >= m_Pos.y - CollisionOffset.y && _Pos.y <= m_Pos.y);
}

void Monster::OnHited(float _Damage)
{
    if (Hited == false)
    {
        Hited = true;
        HitTick = GetTickCount64();
        MoveTick = GetTickCount64();
    }
}
