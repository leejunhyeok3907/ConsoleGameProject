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

	void PrintScreen(int _x, int _y, string _string);

	void ReleaseScreen();

private:
	int m_ScreenIndex = 0;

	int m_DelayTime = 30;

	HANDLE m_Screen[2];

	bool m_GameLoop = true;

	GetSet(int, m_ScreenIndex, ScreenIndex);
};

