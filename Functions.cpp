#include "pch.h"
#include "Functions.h"

void gotoxy(int _x, int _y)
{
	COORD Pos = { _x - 1, _y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
