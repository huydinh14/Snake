#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>
#include "resource.hpp"
#include <windows.h>
#include <stdio.h>
#include <vector>


#pragma comment(lib, "winmm.lib")
#define AUDIO(FileName) (PlaySound(MAKEINTRESOURCE(FileName),GetModuleHandle(NULL),SND_RESOURCE | SND_ASYNC));

extern short sPages, sSelectLocation, sTotalCatalog;

enum class eDirections {
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
	int iLength;
	eDirections eDirecs;
};

struct Fruit
{
	Location Location;
};

struct PLAYER
{
	char strName[10];
	int iScore;
};
