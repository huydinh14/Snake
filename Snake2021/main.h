#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

extern short SPages, SSelectLocation, STotalCatalog;

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
	short x;
	short y;
};

struct Snake
{
	Location LN[100];
	int iN;
	eStatus est;
};

struct Fruit
{
	Location location;
};

