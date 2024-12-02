#include "pch.h"
#include "GameManager.h"
#include "Functions.h"
#include "KeyManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
    Release();
}

void GameManager::Progress()
{
    unsigned int system_tick = GetTickCount64();

    while (m_GameLoop)
    {
        unsigned int CurrentTick = GetTickCount64();

        if (system_tick + m_DelayTime < CurrentTick)
        {
            system_tick = CurrentTick;

            Update();

            Render();

            if (KeyManager::GetInst()->GetKeyState(KEY_TYPE::Q) == KEY_STATE::HOLD)
            {
                break;
            }
        }
    }
}

void GameManager::Init()
{
    CONSOLE_CURSOR_INFO cci;

    m_Screen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    m_Screen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE,
        0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    cci.dwSize = 1;
    cci.bVisible = FALSE;
    SetConsoleCursorInfo(m_Screen[0], &cci);
    SetConsoleCursorInfo(m_Screen[1], &cci);

    //Initalize Managers
    KeyManager::GetInst()->Init();
}

void GameManager::Update()
{
    //Managers Update
    KeyManager::GetInst()->Update();
}

void GameManager::Render()
{
    ClearScreen();

    //Managers Render
    KeyManager::GetInst()->Render();

    DoubleBuffering();
}

void GameManager::Release()
{
    ReleaseScreen();
}

void GameManager::DoubleBuffering()
{
    SetConsoleActiveScreenBuffer(m_Screen[m_ScreenIndex]);
    m_ScreenIndex = m_ScreenIndex ? 0 : 1;
}

void GameManager::ClearScreen()
{
    DWORD dw;
    COORD cd = { 0, 0 };

    FillConsoleOutputCharacter(m_Screen[m_ScreenIndex], ' ', 80 * 25, cd, &dw);
}

void GameManager::PrintScreen(int _x, int _y, string _string)
{
    DWORD dw;
    COORD CursorPosition = { _x, _y };

    SetConsoleCursorPosition(m_Screen[m_ScreenIndex], CursorPosition);
    WriteFile(m_Screen[m_ScreenIndex], _string.c_str(), _string.size(), &dw, NULL);
}

void GameManager::ReleaseScreen()
{
    CloseHandle(m_Screen[0]);
    CloseHandle(m_Screen[1]);
}
