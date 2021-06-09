#pragma once
#include "main.h"

void PaintWall();                                            // Vẽ tường
void InforDisplay();										 // Hiện thông số Level, Point
bool IInforDisGameOver(bool bCheck, int SIndex);
void InitSnake(Snake &snake);								 // Khởi tạo rắn
void InitFruit(Fruit& fruit);								 // Khởi tạo mồi
void OnDisplay(Snake snake, Fruit fruit);					 
void ControlSnake(Snake& snake, Fruit& fruit);				 // Điều khiển rắn
void RunEvent(Snake& snake, Fruit& fruit, int iTime, int SIndex);
void CheckSnake_Fruit(Snake &snake,Fruit &fruit, int &time);
bool BCheckGameOver(Snake& snake, Fruit& fruit);
void paintMenuMain(short SIndex);
void paintLevelMenu(short SIndex);
void eventProcessing();
void TitleMenuMain();
void keyboardProcessing(KEY_EVENT_RECORD key);
void paintMenuGameOver(int SIndex);