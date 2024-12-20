#include "pch.h"
#include "Monster.h"
#include "KeyManager.h"
#include "GameManager.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Ground.h"
#include "Player.h"

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

    CurrentColor = DefaultColor;
}

void Monster::update()
{
    if (Health <= 0.f)
    {
        m_bAlive = false;
    }

    ULONGLONG Current_tick = GetTickCount64();

    if (IsInScreen(m_Pos.x, m_Pos.y) == false) m_bAlive = false;

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

    if (Jumping)
    {
        if (Target)
        {
            if (Hited == false)
            {
                m_Pos.x -= (Target->GetPos().x < m_Pos.x) ? 1.f : -1.f;
            }
            else
            {
                m_Pos.x -= (Target->GetPos().x < m_Pos.x) ? -1.f : 1.f;
            }
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
            CurrentColor = DefaultColor;
        }
    }

    if (DamageTextExist)
    {
        if (HitTextTick + 200 <= Current_tick)
        {
            DamageTextExist = false;
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

    Player* p = dynamic_cast<Player*>(Target);

    if (p)
    {
        bool Check = false;

        for (int i = 0; i <= CollisionOffset.y; i++)
        {
            for (int j = -CollisionOffset.x; j <= CollisionOffset.x; j++)
            {
                if (p->Collision({ m_Pos.x + j, m_Pos.y + i }))
                {
                    p->OnHited(GetRandomDamage(30, 10));

                    Check = true;
                    break;
                }
            }

            if (Check) break;
        }
    }
}

void Monster::render()
{
    GameManager::GetInst()->ChangeRenderColor(CurrentColor, ConsoleRenderingType::TEXT);

    DrawCharacter();

    if (DamageTextExist)
    {
        string str = to_string(TakeDamage);

        GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::RED, ConsoleRenderingType::TEXT);
        GameManager::GetInst()->PrintScreen(HitedPos.x, HitedPos.y - 3, str);
    }

    GameManager::GetInst()->ResumeRenderColor();
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

int Monster::GetRandomDamage(int _MaxDamage, int _MinDamage)
{
    int Damage = rand() % static_cast<int>(_MaxDamage - _MinDamage) + _MinDamage;

    return Damage;
}

bool Monster::Collision(Vec2 _Pos)
{
    return (_Pos.x >= m_Pos.x - CollisionOffset.x && _Pos.x <= m_Pos.x + CollisionOffset.x
        && _Pos.y >= m_Pos.y - CollisionOffset.y && _Pos.y <= m_Pos.y);
}

void Monster::OnHited(int _Damage)
{
    ULONGLONG Current_tick = GetTickCount64();

    if (Hited == false)
    {
        Hited = true;
        HitTick = Current_tick;
        MoveTick = Current_tick;
        HitTextTick = Current_tick;
        DamageTextExist = true;

        HitedPos = m_Pos;

        JumpTick = ReduceJumpPowerTick = Current_tick;
        Jumping = true;
        JumpPower = 0.55f;
        Gravity = 0.f;

        Health -= _Damage;

        CurrentColor = HitColor;

        TakeDamage = _Damage;
    }
}
