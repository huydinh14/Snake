#include <string>
#include <iostream>

#include "console.hpp"

HANDLE hConsoleOutput;
HANDLE hConsoleInput;

void ConsoleResize(short sWidth, short sHeight)
{
	/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);*/

	COORD crd = { sWidth, sHeight };
	SMALL_RECT rec = { 0, 0, sWidth - 1, sHeight - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rec);
	SetConsoleScreenBufferSize(hConsoleOutput, crd);
}

void Clrscr()
{
	CONSOLE_SCREEN_BUFFER_INFO screen_Buffer_Info;
	COORD home = { 0, 0 };
	DWORD dummy;

	hConsoleOutput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_Buffer_Info);

	FillConsoleOutputCharacter(hConsoleOutput, ' ', screen_Buffer_Info.dwSize.X * screen_Buffer_Info.dwSize.Y, home, &dummy);
	screen_Buffer_Info.dwCursorPosition.X = 0;
	screen_Buffer_Info.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOutput, screen_Buffer_Info.dwCursorPosition);
}

void GotoXY(short sRow, short sColumn)
{
	COORD cursor_An_Pos = { sRow, sColumn };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, cursor_An_Pos);
}

int WhereX()
{
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &conInfo);
	return conInfo.dwCursorPosition.X;
}

int WhereY()
{
	CONSOLE_SCREEN_BUFFER_INFO conInfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &conInfo);
	return conInfo.dwCursorPosition.Y;
}

void ShowCur(bool bCursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, bCursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetColor(WORD color)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_Buffer_Info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_Buffer_Info);

	WORD wAttributes = screen_Buffer_Info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

WORD TextAttr()
{
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(hConsoleOutput, &consoleInfo);
	return consoleInfo.wAttributes;
}

void ResetTextAttr()
{
	DWORD mau_Mac_Dinh = TextAttr();
	SetConsoleTextAttribute(hConsoleOutput, mau_Mac_Dinh);
}

void SetBackgroundColorTextXY(SHORT sX, SHORT sY, WORD color, WORD background, LPSTR str,std::string strIcon, WORD colors, WORD bgColor,...)
{
	GotoXY(sX - 3, sY);
	SetColor(colors);
	SetBackgroundColor(bgColor);
	std::cout << strIcon;

	GotoXY(sX, sY);
	SetBackgroundColor(background);
	SetColor(color);

	/*In duoc nhieu chu hon*/
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	/*In duoc nhieu chu hon*/

	ResetTextAttr();
	//setColor(7);
}

void SetBackgroundColorTextXY2(SHORT sX, SHORT sY, WORD color, WORD background, LPSTR str,...)
{
	GotoXY(sX, sY);
	SetBackgroundColor(background);
	SetColor(color);

	/*In duoc nhieu chu hon*/
	va_list args;
	va_start(args, str);
	vprintf(str, args);
	va_end(args);
	/*In duoc nhieu chu hon*/

	ResetTextAttr();
	//setColor(7);
}

void SetBackgroundColor(WORD color)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_Buffer_Info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_Buffer_Info);

	WORD wAttributes = screen_Buffer_Info.wAttributes;
	color &= 0x000f;
	color <<= 4; // Dich trai 3 bit de phu hop voi mau nen
	wAttributes &= 0xff0f; // Cai 0 cho 1 bit chu nhay va 3 bit mau nen
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}

void DeleteRow(SHORT sStartPos, SHORT sNumberRow)
{
	CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
	COORD pos = { 0, sStartPos };
	DWORD tmp;
	GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
	FillConsoleOutputCharacter(hConsoleOutput, ' ', ConsoleInfo.dwSize.X * sNumberRow,pos, &tmp);
	FillConsoleOutputAttribute(hConsoleOutput, 15, ConsoleInfo.dwSize.X * sNumberRow, pos, &tmp);
	SetConsoleCursorPosition(hConsoleOutput, pos);
}