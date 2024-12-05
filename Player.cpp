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

    if (CheckPlayerDead())
    {
        if (PlayerDead == false)
        {
            PlayerDead = true;
            DeadTick = Current_tick;
        }
    }

    if (PlayerDead == false && EnableKeyInput)
    {
        KeyInput(Current_tick);
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
        if (HitTick + 300 <= Current_tick)
        {
            if(UseSkill==false) Hited = false;
            CurrentPlayerColor = PlayerDefaultColor;
        }
    }

    if (DamageTextExist)
    {
        if (HitTextTick + 200 <= Current_tick)
        {
            DamageTextExist = false;
        }
    }

    if (UseSkill)
    {
        CheckSkillHit();

        if (SkillMotionTick + 100 <= Current_tick)
        {
            {
                Health += 1.f;
                Mana -= 1.f;

                if (Health > MaxHealth) Health = MaxHealth;
            }

            SkillMotionIndex = (SkillMotionIndex + 1) % 2;
        }

        if (UseSkillTick + 1000 <= Current_tick
            || Mana <= 0.f)
        {
            UseSkill = false;
            Hited = false;
            EnableKeyInput = true;
        }
    }

    if (IsCooltime)
    {
        if (SkillCoolTime + 2000 <= Current_tick)
        {
            IsCooltime = false;
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

    if (PlayerDead)
    {
        if (DeadTick + 2000 <= Current_tick)
        {
            SceneManager::GetInst()->ChangeScene(SCENE_TYPE::GAMEOVER);
        }
    }
}

void Player::render()
{
    GameManager::GetInst()->ChangeRenderColor(CurrentPlayerColor, ConsoleRenderingType::TEXT);
	

    DrawCharacter();
    //GameManager::GetInst()->PrintScreen(m_Pos.x, m_Pos.y, L"a");

    if (DamageTextExist)
    {
        string str = to_string(TakeDamage);

        GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::RED, ConsoleRenderingType::TEXT);
        GameManager::GetInst()->PrintScreen(HitedPos.x, HitedPos.y - 3, str);
    }

    GameManager::GetInst()->ResumeRenderColor();
}

void Player::DrawCharacter()
{
    if (PlayerDead)
    {
        GameManager::GetInst()->PrintScreen(m_Pos.x - 3, m_Pos.y,     ")-/-O");
    }
    else if (UseSkill)
    {
        if (SkillMotionIndex == 0)
        {
            GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::DARKGREEN, ConsoleRenderingType::TEXT);

            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 3, "^^^^^^^^^^^");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 2, "(         )");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 1, "{         }");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y,     "(         )");
        }
        else if (SkillMotionIndex == 1)
        {
            GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::DARKMAGENTA, ConsoleRenderingType::TEXT);

            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 3, "***********");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 2, "{         }");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y - 1, "(         )");
            GameManager::GetInst()->PrintScreen(m_Pos.x - 4, m_Pos.y,     "{         }");
        }

        GameManager::GetInst()->ChangeRenderColor(ConsoleRenderingColor::YELLOW, ConsoleRenderingType::TEXT);
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 2, "  O  ");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y - 1, "-{|}-");
        GameManager::GetInst()->PrintScreen(m_Pos.x - 1, m_Pos.y,     " -^- ");

        GameManager::GetInst()->ResumeRenderColor();
    }
    else
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
                    Mon->OnHited((rand() % 25) + 25.f);
                    break;
                }
            }
        }
    }
}

void Player::CheckSkillHit()
{
    const vector<Object*>& Monsters = SceneManager::GetInst()->GetCurScene()->
        GetGroupObject(GROUP_TYPE::MONSTER);

    for (auto Obj : Monsters)
    {
        Monster* Mon = dynamic_cast<Monster*>(Obj);

        if (Mon)
        {
            bool HitCheck = false;

            for (int i = -5; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (Mon->Collision({ m_Pos.x + i, m_Pos.y + j }))
                    {
                        Mon->OnHited(25.f);
                        HitCheck = true;
                        break;
                    }
                }
                if (HitCheck) break;
            }
        }
    }
}

int Player::GetRandomDamage(int _MaxDamage, int _MinDamage)
{
    int Damage = rand() % static_cast<int>(_MaxDamage - _MinDamage) + _MinDamage;

    return Damage;
}

bool Player::CheckPlayerDead()
{
    bool Check = IsInScreen(m_Pos.x, m_Pos.y) == false
        || Health <= 0;

    return Check;
}

void Player::KeyInput(int _CurrentTick)
{
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
                JumpTick = ReduceJumpPowerTick = _CurrentTick;
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
            AttackTick = _CurrentTick;
            Attacking = true;

            CheckAttack();
        }
    }

    if (KEY_TAP(KEY_TYPE::X))
    {
        if (IsCooltime == false && Mana > 0.f)
        {
            IsCooltime = true;
            UseSkill = true;
            Hited = true;

            EnableKeyInput = false;

            UseSkillTick = _CurrentTick;
            SkillCoolTime = _CurrentTick;

            SkillMotionTick = _CurrentTick;
            SkillMotionIndex = 0;
        }
    }
}

bool Player::Collision(Vec2 _Pos)
{
    return (_Pos.x >= m_Pos.x - CollisionOffset.x && _Pos.x <= m_Pos.x + CollisionOffset.x
        && _Pos.y >= m_Pos.y - CollisionOffset.y && _Pos.y <= m_Pos.y);
}

void Player::OnHited(int _Damage)
{
    if (Hited == false && PlayerDead == false)
    {
        Hited = true;
        HitTick = GetTickCount64();

        Health -= _Damage;
        TakeDamage = _Damage;

        HitedPos = m_Pos;

        CurrentPlayerColor = PlayerHitColor;

        HitTextTick = GetTickCount64();
        DamageTextExist = true;
    }
}

float Player::GetHPRatio()
{
    return (Health / MaxHealth) * 10;
}

float Player::GetMPRatio()
{
    return (Mana / MaxMana) * 10;
}
