#pragma once
#include "main.hpp"

// Init
void InitSnake(Snake& snake);								 
void InitFruit(Fruit& fruit, bool bCheck);

// 
short XCoord(short SX);
short YCoord(short SY);

// Paint
void TitleMenuMain();
void InforDisplay(std::string strLevel, int& iPoint);
bool InforDisGameOver(bool bCheck);
void PaintBoder();
void PaintSnake(Snake snake);	
void PaintFruit(Fruit fruit);
void PaintTable();
void PaintBox(short SX, short SY);
void PaintMenuMain(short sIndex);
void PaintLevelMenu(short sIndex);
void PaintMenuPause(short sIndex);
void PaintMenuGameOver(int iIndex);

// Control
//void ControlSnake(Snake& snake);			                  
void Control(Snake& snake);
void Directional(Snake& snake);

// Even processing
void RunEvent(Snake& snake, Fruit& fruit, int iIndex, std::string strLevel, int& iPoint);
void SnakeEatFruit(Snake& snake, Fruit& fruit, int& iPoint,bool bCheck);
void UpdatePoint(int iPoint);
bool BCheckGameOver(Snake& snake, Fruit& fruit);
void EventProcessing();

// Keyboard
void KeyboardProcessing(KEY_EVENT_RECORD kKey);

// Svae File
void SaveName(int iPoint);
void Point();
void ReadFile();

//void ControlHeadSnake(Snake& snake);
//int VKControl();
//void TableCoordSave();

