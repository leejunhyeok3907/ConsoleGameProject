#pragma once
#include "Manager.h"

class GameManager : public Manager
{
	SINGLE(GameManager);

public:
	void Progress();

	virtual void Init() override;

	virtual void Update() override;

	virtual void Render() override;

	void Release();

private:
	void DoubleBuffering();

	void ClearScreen();

public:
	void PrintScreen(int _x, int _y, wstring _string);

	void MovePosition(int _x, int _y);

	void ChangeRenderColor(ConsoleRenderingColor _Color, ConsoleRenderingType _Type);

private:
	void ReleaseScreen();

private:
	Vec2 ScreenSize = { 96, 32 };

	int m_ScreenIndex = 0;

	int m_DelayTime = 10;

	HWND m_Console = nullptr;

	CONSOLE_SCREEN_BUFFER_INFO m_outputScreenBufferInfo;

	HANDLE m_Screen[2] = { 0, };

	bool m_GameLoop = true;

public:
	void ChangeTitle(const wstring& _str);

	HWND GetConsoleHWND() const { return m_Console; }

	HANDLE GetCurrentScreen() const { return m_Screen[m_ScreenIndex]; }

	const Vec2& GetScreenSize() const { return ScreenSize; }
};

