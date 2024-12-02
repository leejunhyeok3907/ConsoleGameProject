#include "pch.h"
#include "GameManager.h"
#include "Functions.h"
#include "KeyManager.h"
#include "SceneManager.h"

GameManager::GameManager()
{

}

GameManager::~GameManager()
{
    Release();
}

void GameManager::Progress()
{
    ULONGLONG system_tick = GetTickCount64();

    while (m_GameLoop)
    {
        ULONGLONG CurrentTick = GetTickCount64();

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

    m_Console = GetConsoleWindow();

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &m_outputScreenBufferInfo);

    //Initalize Managers
    KeyManager::GetInst()->Init();
    SceneManager::GetInst()->Init();

}

void GameManager::Update()
{
    //Managers Update
    KeyManager::GetInst()->Update();
    SceneManager::GetInst()->Update();
}

void GameManager::Render()
{
    ClearScreen();
    //Managers Render
    KeyManager::GetInst()->Render();
    SceneManager::GetInst()->Render();

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

    MovePosition(cd.X, cd.Y);
}

void GameManager::PrintScreen(int _x, int _y, wstring _string)
{
    DWORD dw;
    COORD CursorPosition = { (SHORT)_x, (SHORT)_y };

    SetConsoleCursorPosition(m_Screen[m_ScreenIndex], CursorPosition);
    WriteFile(m_Screen[m_ScreenIndex], _string.c_str(), (DWORD)_string.size(), &dw, NULL);
}

void GameManager::MovePosition(int _x, int _y)
{
    DWORD dw;
    COORD CursorPosition = { (SHORT)_x, (SHORT)_y };

    SetConsoleCursorPosition(m_Screen[m_ScreenIndex], CursorPosition);
}

void GameManager::ChangeRenderColor(ConsoleRenderingColor _Color, ConsoleRenderingType _Type)
{
    WORD attr = m_outputScreenBufferInfo.wAttributes;

    if (_Type== ConsoleRenderingType::TEXT)
    {
        attr &= 0xFFF0;//하위 4비트만 가져오기
        attr |= static_cast<WORD>(_Color);
    }
    else if (_Type == ConsoleRenderingType::BACKGROUND)
    {
        attr &= 0xFF0F;//상위 4비트만 가져오기
        attr |= (static_cast<WORD>(_Color) << 4); //따라 상위 4비트만큼 이동
    }

    m_outputScreenBufferInfo.wAttributes = attr;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m_outputScreenBufferInfo.wAttributes);
}

void GameManager::ReleaseScreen()
{
    CloseHandle(m_Screen[0]);
    CloseHandle(m_Screen[1]);
}

void GameManager::ChangeTitle(const wstring& _str)
{
    SetWindowText(m_Console, _str.c_str());
}

