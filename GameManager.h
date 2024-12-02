#pragma once
class GameManager
{
	SINGLE(GameManager);

public:
	void Init();

	void Progress();

	void Render();

	void Release();

private:
	void DoubleBuffering();

	void ClearScreen();

	void PrintScreen(int _x, int _y, string _string);

	void ReleaseScreen();

private:
	int m_ScreenIndex = 0;

	HANDLE m_Screen[2];

	bool m_GameLoop = true;

	GetSet(int, m_ScreenIndex, ScreenIndex);
};

