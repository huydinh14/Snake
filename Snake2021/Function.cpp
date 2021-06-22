#include "Function.hpp"
#include "Console.hpp"
#include "main.h"

#define Green			2
#define Black			0
#define Grey			8
#define Blue			9
#define LightGreen		10
#define Cyan			11
#define Red				12
#define Pink			13
#define Yellow			14
#define White			15

#define WIDTH 105
#define HEIGHT 30
#define WALL 45

Snake snake;
Fruit fruit;
PLAYER Player[10];
int iFruitColor = 1;
int   iTime = 120;
std::string strIcon = ">>";
std::string strLevel = "DE";
int iPoint = 0;
short SXCoord;
short SYCoord;

void PaintTable()
{
	//TableCoordSave();
	for (int i = 0; i < 25; ++i)
	{
		for (int j = 0; j < 50; ++j)
		{
			/*if (((i % 2) && (j % 2)) || !((i % 2) || (j % 2)))
			{
				PaintBox(j, i);
			}*/
			PaintBox(j, i);
		}
	}
}

short XCoord(short SX) // Toa do x ve bang.
{
	return ((SX * 2) + 6);
}

short YCoord(short SY) // Toa do y ve bang.
{
	return (SY + 6);
}

//void TableCoordSave()
//{
//	SXCoord = ((WIDTH / 2) + 20);
//	SYCoord = (((HEIGHT - 6) - 40) / 2) + 7;
//}

void PaintBox(short SX, short SY)
{
	SetBackgroundColorTextXY2(XCoord(SX), YCoord(SY), 0, 8, (char*)"  ");
}

//void paintStarCircle()
//{
//	gotoXY(WIDTH + 8, 9);
//	int iXc = 220, iYc = 140, r = 100;
//	int iD = 170;
//
//	HWND hwnd = 
//	HDC hdc = GetDC(HWND);
//	for (int i = 0; i <= 5; i++)
//	{
//		int iX = iXc + (int)(r * cos(iD / (180 / PI)));
//		int iY = iYc + (int)(r * sin(iD / (180 / PI)));
//		if (!i)
//		{
//			gotoXY(iX, iY);
//		}
//		else
//		{
//			LineTo(hdc,iX, iY);
//		}
//	}
//}

void InforDisplay(std::string strLevel, int& iPoint) 
{
	LPSTR StrTitle = (char*)"CAP DO: ";
	SetBackgroundColorTextXY2(WIDTH + 4, 6, Green, 0, StrTitle);
	SetColor(White);
	std::cout << strLevel;
	StrTitle = (char*)"DIEM:   "; 
	SetBackgroundColorTextXY2(WIDTH + 4, 7, Green, 0, StrTitle);
	SetColor(White);
	std::cout << iPoint;

	GotoXY(WIDTH / 2 - 7, HEIGHT + 3);
	SetColor(White);
	std::cout << "Snake v1.0 by HuyDinhSE";
}

bool IInforDisGameOver(bool bCheck, int iIndex)
{
	if (bCheck)
	{
		PaintMenuGameOver(1);
		return true;
	}
	return false;
}

void PaintMenuGameOver(int iIndex) 
{
	sSelectLocation = iIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"  THUA  ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 2, HEIGHT / 2, White, Green, strTitle);
	strTitle = (char*)"  CHOI LAI  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2 + 2, White, ((iIndex == 0) ? Red : 8), strTitle, strIcon, ((iIndex == 0) ? Pink : 8), 8);
	strTitle = (char*)"  LUU  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 2, HEIGHT / 2 + 3, White, ((iIndex == 1) ? Red : 8), strTitle, strIcon, ((iIndex == 1) ? Pink : 8), 8);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 3, HEIGHT / 2 + 4, White, ((iIndex == 2) ? Red : 8), strTitle, strIcon, ((iIndex == 2) ? Pink : 8), 8);
}

void InitFruit(Fruit& fruit, bool bCheck)
{
	srand(time(NULL));
	while (bCheck == false) 
	{
		fruit.Location.sX = rand() % ((100 - 7 + 1) / 2) + 3.5;
		fruit.Location.sY = rand() % ((31 - 7 + 1) / 2) + 3.5;
		for (int i = 0; i < snake.iN - 1; i++) {
			if (snake.LN[i].sX == fruit.Location.sX && snake.LN[i].sY == fruit.Location.sY)
			{
				continue;
			}
		}
		if (fruit.Location.sX != 0 && fruit.Location.sY != 0)
		{
			break;
		}
	}
}

void InitSnake(Snake& snake)
{
	snake.LN[0].sX = 25;
	snake.LN[0].sY = 15;
	snake.iN = 3;
	snake.est = eStatus::UP;
}

void OnDisplay(Snake snake, Fruit fruit)
{
	SetBackgroundColorTextXY2(XCoord(fruit.Location.sX), YCoord(fruit.Location.sY),9,9,(char*)"  ");
	/*SetColor(White);
	GotoXY(snake.LN[0].sX, snake.LN[0].sY);
	putchar(HEAD);*/
	SetBackgroundColorTextXY2(XCoord(snake.LN[0].sX), YCoord(snake.LN[0].sY),11,11, (char*)"  ");
	for (int i = 1; i < snake.iN; i++)
	{
		/*GotoXY(snake.LN[i].sX, snake.LN[i].sY);
		putchar(BODY);*/
		SetBackgroundColorTextXY2(XCoord(snake.LN[i].sX), YCoord(snake.LN[i].sY), 15, 15, (char*)"  ");
	}
	SetBackgroundColorTextXY2(XCoord(snake.LN[snake.iN - 1].sX), YCoord(snake.LN[snake.iN - 1].sY), 8, 8, (char*)"  ");
	/*GotoXY(snake.LN[snake.iN - 1].sX, snake.LN[snake.iN - 1].sY);
	putchar('  ');*/
}

void ControlSnake(Snake& snake, Fruit& fruit)
{
	for (int i = snake.iN - 1; i > 0; i--)
	{
		snake.LN[i] = snake.LN[i - 1];
	}

	/*if (_kbhit())
	{
		int iKey = _getch();
		iKey = tolower(iKey);
		if (iKey == 'w' && snake.est != eStatus::DOWN)
		{
			snake.est = eStatus::UP;
		}
		else if (iKey == 's' && snake.est != eStatus::UP)
		{
			snake.est = eStatus::DOWN;
		}
		else if(iKey == 'a' && snake.est != eStatus::RIGHT)
		{
			snake.est = eStatus::LEFT;
		}
		else if(iKey == 'd' && snake.est != eStatus::LEFT)
		{
			snake.est = eStatus::RIGHT;
		}
	}
	
	if (snake.est == eStatus::UP)
	{
		snake.LN[0].sY--;
	}
	else if (snake.est == eStatus::DOWN)
	{
		snake.LN[0].sY++;
	}
	else if (snake.est == eStatus::LEFT)
	{
		snake.LN[0].sX--;
	}
	else if (snake.est == eStatus::RIGHT)
	{
		snake.LN[0].sX++;
	}*/
}

void UpdatePoint(int iPoint)
{
	GotoXY(WIDTH + 12, 7);
	SetColor(White);
	SetBackgroundColor(0);
	std::cout << iPoint;
}

void RunEvent(Snake &snake, Fruit &fruit, int iTime, int iIndex, std::string strLevel, int &iPoint)
{
	bool bCheck = false;
	InforDisplay(strLevel, iPoint);
	PaintTable();
	InitSnake(snake);
	InitFruit(fruit, bCheck);
	while (1)
	{
		OnDisplay(snake, fruit);
		ControlSnake(snake, fruit); 
		/*CheckSnake_Fruit(snake, fruit, iTime, iPoint, bCheck);
		bCheck = BCheckGameOver(snake, fruit);
		if (IInforDisGameOver(bCheck, iIndex))
		{
			sPages = 4;
		}*/
		//Sleep(iTime);
		/*if (_getch() == 27)
		{
			sPages = 3;
			PaintMenuPause(1);
		}*/
	}
}

void CheckSnake_Fruit(Snake& snake, Fruit& fruit, int& iTime, int& iPoint,bool bCheck)
{
	if ((snake.LN[0].sX == fruit.Location.sX) && (snake.LN[0].sY == fruit.Location.sY)) {
		snake.iN++;
		ControlSnake(snake, fruit);
		InitFruit(fruit, bCheck);
		iPoint++;
		UpdatePoint(iPoint);
		iTime -= 3;
	}
}

bool BCheckGameOver(Snake& snake, Fruit& fruit)
{
	if ((snake.LN[0].sX < 0 || snake.LN[0].sX > 49) || (snake.LN[0].sY < 0 || snake.LN[0].sY > 24))
	{
		return true;
	}
	for (int i = 1; i < snake.iN; i++) 
	{
		if ((snake.LN[0].sX == snake.LN[i].sX) && (snake.LN[0].sY == snake.LN[i].sY))
		{
			return true;
		}
	}
	return false;
}

void KeyboardProcessing(KEY_EVENT_RECORD kKey)
{
	if (kKey.bKeyDown)
	{
		switch (kKey.wVirtualKeyCode)
		{
		case VK_UP:
			switch (sPages)
			{
			case 1://Menu Main
				if (sSelectLocation == 1)
				{
					sSelectLocation = sTotalCatalog;
				}
				else
				{
					sSelectLocation -= 1;
				}
				PaintMenuMain(sSelectLocation);
				break;
			case 2: //menu level
				if (sTotalCatalog == 4)
				{
					if (sSelectLocation == 0)
					{
						sSelectLocation = sTotalCatalog - 1;
					}
					else
					{
						sSelectLocation -= 1;
					}
					PaintLevelMenu(sSelectLocation);
				}
				break;
			case 3:
				if (sTotalCatalog == 3)
				{
					if (sSelectLocation == 0)
					{
						sSelectLocation = sTotalCatalog - 1;
					}
					else
					{
						sSelectLocation -= 1;
					}
					PaintMenuPause(sSelectLocation);
				}
				break;
			case 4://Display Game Over
				if (sTotalCatalog == 3)
				{
					if (sSelectLocation == 0)
					{
						sSelectLocation = sTotalCatalog - 1;
					}
					else
					{
						sSelectLocation -= 1;
					}
					PaintMenuGameOver(sSelectLocation);
				}
				break;
			}
			break;
		case VK_DOWN:
			switch (sPages)
			{
			case 1://Menu Main
				if (sSelectLocation == sTotalCatalog)
				{
					(sTotalCatalog == 4) ? sSelectLocation = 1 : sSelectLocation = 0;
				}
				else
				{
					sSelectLocation += 1;
				}
				PaintMenuMain(sSelectLocation);
				break;
			case 2: //menu level
				if (sTotalCatalog == 4)
				{
					if (sSelectLocation == sTotalCatalog - 1)
					{
						sSelectLocation = 0;
					}
					else
					{
						sSelectLocation += 1;
					}
					PaintLevelMenu(sSelectLocation);
				}
				break;
			case 3:
				if (sTotalCatalog == 3)
				{
					if (sSelectLocation == sTotalCatalog - 1)
					{
						sSelectLocation = 0;
					}
					else
					{
						sSelectLocation += 1;
					}
					PaintMenuPause(sSelectLocation);
				}
				break;
			case 4://Display Game Over
				if (sTotalCatalog == 3)
				{
					if (sSelectLocation == sTotalCatalog - 1)
					{
						sSelectLocation = 0;
					}
					else
					{
						sSelectLocation += 1;
					}
					PaintMenuGameOver(sSelectLocation);
				}
				break;
			}
			break;
		case VK_RETURN:
			switch (sPages)
			{
			case 1:
				if (sSelectLocation == 1)
				{
					iTime = 120;
					sPages = 3;
					DeleteRow(7, HEIGHT + 1);
					RunEvent(snake, fruit, iTime, sSelectLocation, strLevel, iPoint);
					//AUDIO(104);
				}
				else if (sSelectLocation == 2)
				{
					sPages = 2;
					DeleteRow(11, 11);
					PaintLevelMenu(0);
				}
				else if (sSelectLocation == 3)
				{
					sPages = 2;
					DeleteRow(1, HEIGHT);
					Point();
					sPages = 1;
					DeleteRow(4, HEIGHT);
					PaintMenuMain(0);
				}
				else if (sSelectLocation == 4)
				{
					exit(0);
				}
				break;
			case 2:
				if (sSelectLocation == 0)
				{
					iTime = 120;
					strLevel = "DE";
					sPages = 3;
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 1)
				{
					iTime = 95;
					strLevel = "TB";
					sPages = 3;
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 2)
				{
					iTime = 75;
					strLevel = "KHO";
					sPages = 3;
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 3)
				{
					sPages = 1;
					DeleteRow(11, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 3://Pause
				if (sSelectLocation == 1)
				{
					SaveName(iPoint);
					sPages = 1;
					DeleteRow(4, HEIGHT);
					PaintMenuMain(1);
				}
				else if (sSelectLocation == 0)
				{
					
				}
				else if (sSelectLocation == 2)
				{
					sPages = 1;
					DeleteRow(6, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 4://Trang thua
				if (sSelectLocation == 1)
				{
					SaveName(iPoint);
					sPages = 1;
					DeleteRow(4, HEIGHT);
					PaintMenuMain(1);
				}
				else if (sSelectLocation == 0)
				{
					sPages = 4;
					DeleteRow(4, HEIGHT);
					RunEvent(snake, fruit, iTime, sSelectLocation, strLevel, iPoint = 0);
				}
				else if (sSelectLocation == 2)
				{
					sPages = 1;
					DeleteRow(6, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			}
			break;
		case VK_ESCAPE:
		{
			switch (sPages)
			{
				case 1:
			{
				exit(0);
				break;
			}
			case 2:
			{
				sPages = 1;
				DeleteRow(6, HEIGHT);
				PaintMenuMain(1);
				break;
			}
			case 3:
			{
				PaintMenuPause(sSelectLocation);
			}
			break;
			case 4:
			{
				sPages = 1;
				DeleteRow(6, HEIGHT);
				PaintMenuMain(1);
				break;
			}
			}
		}
		}
	}
}

void SaveName(int iPoint)
{
	LPSTR strTitle = (char*)"     TEN     ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 4, HEIGHT / 2 + 2, Black, Red, strTitle);
	strTitle = (char*)"               ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 5, HEIGHT / 2 + 3, Black, White, strTitle);
	SetColor(Black);
	char* cName = new char[10];
	GotoXY(WIDTH / 2 + 2, HEIGHT / 2 + 3);
	std::cin >> cName;

	//Write File
	FILE* _FileOut;
	errno_t _ErrOut = fopen_s(&_FileOut, "rank.txt", "a");
	/*if (_ErrOut)
	{
		cout << "Mo file out khong thanh cong!" << endl;
	}*/

	std::string strTemp = "\t\t";
	strTemp += std::to_string(iPoint);
	strTemp += "\n";
	char const* cPoint = strTemp.c_str();
	char const* cInfor = cName;
	fputs(cInfor, _FileOut);
	fputs(cPoint, _FileOut);
	delete[] cName;
	fclose(_FileOut);

	//Player->Name[(iNumPlayer++)] = (char)Name;
	//Player->iPoint = iPoint;
}

void Point()
{
	LPSTR strTitle1 = (char*)"     TOP SERVER     ";
	SetBackgroundColorTextXY2(WIDTH / 2,6, Yellow,Red, strTitle1);
	LPSTR strTitle2 = (char*)"                    ";
	for (int i = 7; i <= 22; i++)
	{
		for (int j = WIDTH / 2 - 5; j < WIDTH / 2 + 5; j++)
		{
			SetBackgroundColorTextXY2(j,i, Black, White, strTitle2);
		}
	}
	//gotoXY(WIDTH / 2 + 2, HEIGHT / 2 - 5);
	SetColor(Black);
	ReadFile();
	while (_getch() != 13) {};
}

void ReadFile()
{
	FILE* _FileIn;
	errno_t _ErrOut = fopen_s(&_FileIn, "rank.txt", "r+");
	/*if (_ErrOut)
	{
		cout << "Mo file out khong thanh cong!" << endl;
	}*/
	char _cTemp[20];
	int i = 0;
	/*if (_ErrOut != NULL)
	{
		for (int i = 0; i <= 10; i++)
		{
			fscanf_s(_FileIn, "%s\t\t%d", &Player[i].Name,&Player[i].iPoint);
			fscanf_s(_FileIn, "%d", &Player[i].iPoint);
			fseek(_FileIn, 4, SEEK_CUR);
			fclose(_FileIn);
		}
		fclose(_FileIn);
	}*/
	while(fscanf_s(_FileIn,"%[^\n]", _cTemp, __crt_countof(_cTemp)) != EOF)
	{
		GotoXY(WIDTH / 2 + 2, (HEIGHT / 2 - 5) + i);
		printf_s("%s", _cTemp);
		i++;
		fseek(_FileIn,2, SEEK_CUR);
		if (i > 10)
		{
			break;
		}
	}
	fclose(_FileIn);

	////Sort
	//for (int i = 0; i < 9; i++)
	//{
	//	for (int j = i + 1; j < 9; j++)
	//	{
	//		if (Player[i].iPoint > Player[j].iPoint)
	//		{
	//			swap(Player[i],Player[j]);
	//		}
	//	}
	//}
	//while (i < 10)
	//{
	//	gotoXY(WIDTH / 2 + 4, (HEIGHT / 2 - 5) + i);
	//	printf_s("%s\t%d", Player[i].Name, Player[i].iPoint);
	//	i++;
	//	//fseek(_FileIn,2, SEEK_CUR);
	//}
}

void EventProcessing()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0; // Luu lai su kien hien tai.
		DWORD DWNumberOfEventsRead = 0; // Luu lai so luong su kien da duoc loc.

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // Thiet bi dau vao.
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // Dat su kien dau vao cua giao dien cho bien DWNumberOfEvents.
			if (DWNumberOfEvents)
			{
				INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents]; // Con tro EventBuffer.
				ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); // Dat cac su kien duoc luu tru vao con EventBuffer.

				// Chay vong lap de doc su kien.
				/*omp_set_num_threads(2);
				#pragma omp parallel for*/

				for (DWORD i = 0; i < DWNumberOfEvents; ++i)
				{
					if (IREventBuffer[i].EventType == KEY_EVENT) // Neu la su kien phim.
					{
						KeyboardProcessing(IREventBuffer[i].Event.KeyEvent);			
					}
					//else if (IREventBuffer[i].EventType == MOUSE_EVENT)// Su kien chuot.
					//{
					//	std::cout << " X:" << IREventBuffer[i].Event.MouseEvent.dwMousePosition.X
					//		<< " Y:" << IREventBuffer[i].Event.MouseEvent.dwMousePosition.Y
					//		<< std::endl;
					//}
				}
			}
	}
}

void TitleMenuMain() {
	LPSTR strTitle = (char*)"XIN CHAO - SNAKE DAY";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 2, (HEIGHT - 5) / 2 - 2, Pink,0, strTitle);
	strTitle = (char*)"HAY DUA RA SU LUA CHON CUA BAN";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 7, (HEIGHT - 5) / 2 - 1, Green, 0, strTitle);
}

void PaintMenuMain(short sIndex)
{ 
	 sSelectLocation = sIndex;
	 sTotalCatalog = 4;
	 TitleMenuMain();

	//Ve Menu
	 short SW = ((WIDTH - 5) / 2) + 2;
	 short SH = ((HEIGHT - 5) / 2 + 3);
	LPSTR strTitle = (char*)"  CHOI NGAY  ";
	SetBackgroundColorTextXY(SW, SH, White, ((sIndex == 1) ? Red : 0), strTitle, strIcon, ((sIndex == 1) ? Pink : 0),0);
	strTitle = (char*)"  CAP DO  ";
	SetBackgroundColorTextXY(SW,SH + 1, White, ((sIndex == 2) ? Red : 0), strTitle, strIcon, ((sIndex == 2) ? Pink : 0),0);
	strTitle = (char*)"  DIEM SO  ";
	SetBackgroundColorTextXY(SW,SH + 2, White, ((sIndex == 3) ? Red : 0), strTitle, strIcon, ((sIndex == 3) ? Pink : 0),0);
	strTitle = (char*)"  THOAT   ";
	SetBackgroundColorTextXY(SW,SH + 3, White, ((sIndex == 4) ? Red : 0), strTitle, strIcon, ((sIndex == 4) ? Pink : 0),0);
}
void PaintLevelMenu(short sIndex)
{
	sSelectLocation = sIndex;
	sTotalCatalog = 4;
	SetColor(Green);
	LPSTR strTitleLevel = (char*)"  CHON CAP DO  ";
	SetBackgroundColorTextXY2(((WIDTH - 5) / 2), ((HEIGHT - 5) / 2), Blue,0, strTitleLevel);

	short SW = ((WIDTH - 5) / 2) + 5;
	short SH = ((HEIGHT - 5) / 2) + 2;
	LPSTR strTitle = (char*)"  DE  ";
	SetBackgroundColorTextXY(SW, SH, White, ((sIndex == 0) ? Red : 0), strTitle, strIcon, ((sIndex == 0) ? Pink : 0),0);
	strTitle = (char*)"  TRUNG BINH  ";
	SetBackgroundColorTextXY(SW - 4, SH + 1, White, ((sIndex == 1) ? Red : 0), strTitle, strIcon, ((sIndex == 1) ? Pink : 0),0);
	strTitle = (char*)"  KHO ";
	SetBackgroundColorTextXY(SW, SH + 2, White, ((sIndex == 2) ? Red : 0), strTitle, strIcon, ((sIndex == 2) ? Pink : 0),0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(SW - 1, SH + 3, White, ((sIndex == 3) ? Red : 0), strTitle, strIcon, ((sIndex == 3) ? Pink : 0),0);
}
void PaintMenuPause(short sIndex)
{
	sSelectLocation = sIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"  TAM DUNG  ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 2, HEIGHT / 2, White, Green, strTitle);
	strTitle = (char*)"  TIEP TUC  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2 + 2, White, ((sIndex == 0) ? Red : 8), strTitle, strIcon, ((sIndex == 0) ? Pink : 8), 8);
	strTitle = (char*)"  LUU  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 2, HEIGHT / 2 + 3, White, ((sIndex == 1) ? Red : 8), strTitle, strIcon, ((sIndex == 1) ? Pink : 8), 8);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH / 2 - 3, HEIGHT / 2 + 4, White, ((sIndex == 2) ? Red : 8), strTitle, strIcon, ((sIndex == 2) ? Pink : 8), 8);
}


