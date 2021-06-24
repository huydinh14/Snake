#pragma once
#include "main.hpp"
                
void InforDisplay(std::string strLevel, int& iPoint);		 // Hiện thông số Level, Point
bool InforDisGameOver(bool bCheck);
void InitSnake(Snake& snake);								 // Khởi tạo rắn
void InitFruit(Fruit& fruit, bool bCheck);						 // Khởi tạo mồi
void PaintSnake(Snake snake);	
void PaintFruit(Fruit fruit);
void ControlSnake(Snake& snake);			                    // Điều khiển rắn
void RunEvent(Snake& snake, Fruit& fruit, int iTime, int iIndex, std::string strLevel, int& iPoint);
void CheckSnake_Fruit(Snake& snake, Fruit& fruit, int& iTime, int& iPoint,bool bCheck);
void UpdatePoint(int iPoint);
bool BCheckGameOver(Snake& snake, Fruit& fruit);
void PaintMenuMain(short sIndex);
void PaintLevelMenu(short sIndex);
void PaintMenuPause(short sIndex);
void EventProcessing();
void TitleMenuMain();
void KeyboardProcessing(KEY_EVENT_RECORD kKey);
void PaintMenuGameOver(int iIndex);
void SaveName(int iPoint);
void Point();
void ReadFile();
void PaintTable();
void PaintBox(short SX, short SY);
short XCoord(short SX);
short YCoord(short SY);
void ControlHeadSnake(Snake& snake);
int VKControl();
//void TableCoordSave();
//void EventProcessingControl();
//void KeyboardProcessingControl(KEY_EVENT_RECORD Key);
