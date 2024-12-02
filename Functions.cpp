#include "pch.h"
#include "Functions.h"

void gotoxy(int _x, int _y)
{
	COORD Pos = { (SHORT)_x - 1, (SHORT)_y - 1 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
