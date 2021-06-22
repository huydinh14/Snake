#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "resource.hpp"


#pragma comment(lib, "winmm.lib")
#define AUDIO(FileName) (PlaySound(MAKEINTRESOURCE(FileName),GetModuleHandle(NULL),SND_RESOURCE | SND_ASYNC));

extern short sPages, sSelectLocation, sTotalCatalog;

enum class eStatus{
	UP,
	DOWN,
	LEFT,
	RIGHT
};
enum class eLevel
{
	EASY = 25, NORMAL = 30, HARD = 35
}; 

struct Location {
	short sX;
	short sY;
};

struct Snake
{
	Location LN[100];
	int iN;
	eStatus est;
};

struct Fruit
{
	Location Location;
};

struct PLAYER
{
	char cName[20];
	int iPoint;
};
