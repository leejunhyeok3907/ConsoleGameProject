#pragma once
class GameManager
{
private:
	GameManager() = default;

public:
	~GameManager() = default;

public:
	static GameManager GetInst()
	{
		static GameManager Instance;

		return Instance;
	}

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

