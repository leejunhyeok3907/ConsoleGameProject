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

            if (KEY_TAP(KEY_TYPE::Q)) break;
        }
    }
}

void GameManager::Init()
{
    char str[256];
    
    sprintf_s(str, "mode con:cols=%d lines=%d", (int)m_ScreenSize.x, (int)m_ScreenSize.y);

    system(str);

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
    SetConsoleActiveScreenBuffer(GetCurrentScreen());
    m_ScreenIndex = m_ScreenIndex ? 0 : 1;
}

void GameManager::ClearScreen()
{
    DWORD dw;
    COORD cd = { 0, 0 };

    FillConsoleOutputCharacter(GetCurrentScreen(), ' ', m_ScreenSize.x * m_ScreenSize.y, cd, &dw);

    MovePosition(cd.X, cd.Y);
}

void GameManager::PrintScreen(int _x, int _y, string _string)
{
    DWORD dw;
    COORD CursorPosition = { (SHORT)_x, (SHORT)_y };

    SetConsoleCursorPosition(GetCurrentScreen(), CursorPosition);
    WriteFile(GetCurrentScreen(), _string.c_str(), (DWORD)_string.size(), &dw, NULL);
}

void GameManager::MovePosition(int _x, int _y)
{
    DWORD dw;
    COORD CursorPosition = { (SHORT)_x, (SHORT)_y };

    SetConsoleCursorPosition(GetCurrentScreen(), CursorPosition);
}

void GameManager::ChangeRenderColor(ConsoleRenderingColor _Color, ConsoleRenderingType _Type)
{
    GetConsoleScreenBufferInfo(GetCurrentScreen(), &m_outputScreenBufferInfo);

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
    SetConsoleTextAttribute(GetCurrentScreen(), m_outputScreenBufferInfo.wAttributes);
}

void GameManager::ResumeRenderColor()
{
    ChangeRenderColor(ConsoleRenderingColor::WHITE, ConsoleRenderingType::TEXT);
    ChangeRenderColor(ConsoleRenderingColor::BLACK, ConsoleRenderingType::BACKGROUND);
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

