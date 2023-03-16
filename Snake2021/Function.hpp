#pragma once
#include "main.hpp"

// Init
void InitSnake(Snake& snake);
void InitFruit(Fruit& fruit, bool bCheck);

short XCoord(short sX);
short YCoord(short sY);

// Paint
void TitleMenuMain();
void InforDisplay(std::string strLevel, int& iScore);
bool InforDisGameOver(bool bCheck);
void PaintMenuControlConsole();
void PaintBoder();
//void PaintPine();
//void PaintTable();
void PaintBox(short sX, short sY);
void PaintSnake(Snake snake);
void PaintFruit(Fruit fruit);
void PaintMenuMain(short sIndex);
void PaintLevelMenu(short sIndex);
void PaintMenuPause(short sIndex);
void PaintMenuGameOver(int iIndex);

// Control
void Control(Snake& snake);
void Directional(Snake& snake);

// Even processing
void RunEvent(Snake& snake, Fruit& fruit, int iIndex, std::string strLevel, int& iScore);
void SnakeEatFruit(Snake& snake, Fruit& fruit, int& iScore, bool bCheck);
void UpdatePoint(int iScore);
bool BCheckGameOver(Snake& snake, Fruit& fruit);
void EventProcessing();

// Keyboard
void KeyboardProcessing(KEY_EVENT_RECORD kKey);

// Save File
void SaveName(int iScore);
void TopScore();
void ReadFile();
void ReadFileForSort();
void WriteFileUpdate(int iLength);
void ContinueGameWriteFile();
void ContinueGameReadFile();
int SizeOfFileRank();
int SizeOfFileContinue();