#pragma once
#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string>

// Ham thay doi kich co man hinh console.
void ConsoleResize(short sWidth, short sHeight);

// Ham xoa man hinh khong bi dut(lag).
void Clrscr();

// Ham dich chuyen con tro den toa do x, y.
void GotoXY(short sRow, short sColumn);

// Tra ve vi tri x hien tai.
int  WhereX();

// Tra ve vi tri y hien tai.
int  WhereY();

// Ham an hien con tro.
void ShowCur(bool bCursorVisibility);

// Ham to mau.
void SetColor(WORD color);

void ResetTextAttr();

// Ham in mau chu va thay doi mai nen hien thi theo vi tri x, y, co ki tu dac biet.
void SetBackgroundColorTextXY(SHORT sX, SHORT sY, WORD color, WORD background, LPSTR str, std::string strIcon, WORD colors, WORD bgColor, ...);

// Ham in mau chu va thay doi mai nen hien thi theo vi tri x, y.
void SetBackgroundColorTextXY2(SHORT sX, SHORT sY, WORD color, WORD background, LPSTR str,...);

// Ham to mau nen
void SetBackgroundColor(WORD color);

// Xoa so luong dong, SStartPos - Vi tri bat dau xoa, SNumberRow so luong dong can xoa.
void DeleteRow(SHORT sStartPos, SHORT sNumberRow);