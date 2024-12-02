#pragma once
#include <windows.h>

enum 
{  
	Red = 4, Orange = 6, LightGray , Gray, 
	Cyan, LightGreen, Vanil = 14, White = 15 
};

inline void SetColor(int ForgC)
{
	WORD wColor;

	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
	return;
}

inline void SetColor(int textColor, int backgroundColor)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (WORD)((backgroundColor << 4) | textColor));
}

