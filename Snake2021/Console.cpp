#include "Console.hpp"
#include <string>
#include <iostream>

HANDLE hConsoleOutput;
HANDLE hConsoleInput;

void ConsoleResize(SHORT width, SHORT height)
{
	/*HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);*/

	COORD crd = { width, height };
	SMALL_RECT rec = { 0, 0, width - 1, height - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rec);
	SetConsoleScreenBufferSize(hConsoleOutput, crd);
}


void Clrscr()
{

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	COORD Home = { 0, 0 };
	DWORD dummy;

	hConsoleOutput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	FillConsoleOutputCharacter(hConsoleOutput, ' ', screen_buffer_info.dwSize.X * screen_buffer_info.dwSize.Y, Home, &dummy);
	screen_buffer_info.dwCursorPosition.X = 0;
	screen_buffer_info.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOutput, screen_buffer_info.dwCursorPosition);
}

void GotoXY(short iRow, short iColumn)
{
	COORD Cursor_an_Pos = { iRow, iColumn };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

int WhereX()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &coninfo);
	return coninfo.dwCursorPosition.X;
}

int WhereY()
{
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOutput, &coninfo);
	return coninfo.dwCursorPosition.Y;
}

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursor = { 1, CursorVisibility };
	SetConsoleCursorInfo(handle, &cursor);
}

void SetColor(WORD color)
{
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	wAttributes &= 0xfff0;
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
WORD TextAttr()
{
	CONSOLE_SCREEN_BUFFER_INFO ConsoleInfo;
	GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
	return ConsoleInfo.wAttributes;
}

void ResetTextAttr()
{
	DWORD Mau_Mac_Dinh = TextAttr();
	SetConsoleTextAttribute(hConsoleOutput, Mau_Mac_Dinh);
}
void SetBackgroundColorTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str,std::string StrIcon, WORD colors, WORD bgcolor,...)
{
	GotoXY(x - 3, y);
	SetColor(colors);
	SetBackgroundColor(bgcolor);
	std::cout << StrIcon;

	GotoXY(x, y);
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
void SetBackgroundColorTextXY2(SHORT x, SHORT y, WORD color, WORD background, LPSTR str,...)
{
	GotoXY(x, y);
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

	CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
	GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

	WORD wAttributes = screen_buffer_info.wAttributes;
	color &= 0x000f;
	color <<= 4; // Dich trai 3 bit de phu hop voi mau nen
	wAttributes &= 0xff0f; // Cai 0 cho 1 bit chu nhay va 3 bit mau nen
	wAttributes |= color;

	SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void DeleteRow(SHORT SStartPos, SHORT SNumberRow)
{
	CONSOLE_SCREEN_BUFFER_INFO  ConsoleInfo;
	COORD Pos = { 0, SStartPos };
	DWORD Tmp;
	GetConsoleScreenBufferInfo(hConsoleOutput, &ConsoleInfo);
	FillConsoleOutputCharacter(hConsoleOutput, ' ', ConsoleInfo.dwSize.X * SNumberRow, Pos, &Tmp);
	FillConsoleOutputAttribute(hConsoleOutput, 15, ConsoleInfo.dwSize.X * SNumberRow, Pos, &Tmp);
	SetConsoleCursorPosition(hConsoleOutput, Pos);
}