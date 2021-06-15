#pragma once
#include "main.h"

void PaintWall(int iWALL, int iColor, std::string StrLevel, int& iPoint);                     // Vẽ tường
void paintBorder();
void InforDisplay(std::string StrLevel, int& iPoint);									 // Hiện thông số Level, Point
bool IInforDisGameOver(bool bCheck, int SIndex);
void InitSnake(Snake &snake);								 // Khởi tạo rắn
void InitFruit(Fruit& fruit, int iFruitColor);						 // Khởi tạo mồi
void OnDisplay(Snake snake, Fruit fruit);					 
void ControlSnake(Snake& snake, Fruit& fruit);				 // Điều khiển rắn
void RunEvent(Snake& snake, Fruit& fruit, int iTime, int SIndex, std::string StrLevel, int& iPoint);
void CheckSnake_Fruit(Snake& snake, Fruit& fruit, int& time, int& iPoint);
void UpdatePoint(int Point);
bool BCheckGameOver(Snake& snake, Fruit& fruit);
void paintMenuMain(short SIndex);
void paintLevelMenu(short SIndex);
void eventProcessing();
void TitleMenuMain();
void keyboardProcessing(KEY_EVENT_RECORD key);
void paintMenuGameOver(int SIndex);
void SaveName(int iPoint);
void Point();
void ReadFile();