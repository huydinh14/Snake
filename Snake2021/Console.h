#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>

void clrscr();
void gotoXY(short iRow, short iColumn);
int  whereX();
int  whereY();
void ShowCur(bool CursorVisibility);
void setColor(WORD color);
WORD textAttr();
void resetTextAttr();
void setBackgroundColorTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, std::string StrIcon, WORD colors...);
void setBackgroundColor(WORD color);
void deleteRow(SHORT SStartPos, SHORT SNumberRow);