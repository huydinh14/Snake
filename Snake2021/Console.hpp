#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>

#define consoleWidth 120
#define consoleHeight 110

void ConsoleResize(SHORT width, SHORT height);
void Clrscr();
void GotoXY(short iRow, short iColumn);
int  WhereX();
int  WhereY();
void ShowCur(bool CursorVisibility);
void SetColor(WORD color);
WORD TextAttr();
void ResetTextAttr();
void SetBackgroundColorTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, std::string StrIcon, WORD colors, WORD bgcolor, ...);
void SetBackgroundColorTextXY2(SHORT x, SHORT y, WORD color, WORD background, LPSTR str,...);
void SetBackgroundColor(WORD color);
void DeleteRow(SHORT SStartPos, SHORT SNumberRow);
//void WINAPI SetConsoleTitle();