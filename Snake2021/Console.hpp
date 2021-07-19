#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>

#define consoleWidth 120
#define consoleHeight 110

// Ham thay doi kich co man hinh console.
void ConsoleResize(SHORT width, SHORT height);

// Ham xoa man hinh khong bi dut(lag).
void Clrscr();

// Ham dich chuyen con tro den toa do x, y.
void GotoXY(short iRow, short iColumn);

// Tra ve vi tri x hien tai.
int  WhereX();

// Tra ve vi tri y hien tai.
int  WhereY();

// Ham an hien con tro.
void ShowCur(bool CursorVisibility);

// Ham to mau.
void SetColor(WORD color);

void ResetTextAttr();

// Ham in mau chu va thay doi mai nen hien thi theo vi tri x, y, co ki tu dac biet.
void SetBackgroundColorTextXY(SHORT x, SHORT y, WORD color, WORD background, LPSTR str, std::string StrIcon, WORD colors, WORD bgcolor, ...);

// Ham in mau chu va thay doi mai nen hien thi theo vi tri x, y.
void SetBackgroundColorTextXY2(SHORT x, SHORT y, WORD color, WORD background, LPSTR str,...);

// Ham to mau nen
void SetBackgroundColor(WORD color);

// Xoa so luong dong, SStartPos - Vi tri bat dau xoa, SNumberRow so luong dong can xoa.
void DeleteRow(SHORT SStartPos, SHORT SNumberRow);
