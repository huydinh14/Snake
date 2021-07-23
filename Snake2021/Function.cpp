#include "Function.hpp"
#include "Console.hpp"
#include "main.hpp"

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

#define WIDTH 106
#define HEIGHT 30
#define WALL 45

int iUP = Yellow;
int iDOWN = Yellow;
int iLEFT = Yellow;
int iRIGHT = Yellow;

Snake snake;
Fruit fruit;
PLAYER Player[10];
std::string strIcon = ">>";
std::string strLevel = "DE";
bool bStatusGame = false;

// Diem
int iPoint = 0;

// toc do ran
int   iTime = 150;

// Toa do x, y ve bang.
short SXCoord;
short SYCoord;

//auto input = std::getchar();
//bool bUseKeyControl = false;

// 
void InitFruit(Fruit& fruit, bool bCheck)
{
	srand(time(NULL));
	while (!bCheck) 
	{
		fruit.Location.sX = rand() % 50;
		fruit.Location.sY = rand() % 15,5;
		for (int i = 0; i < snake.iN - 1; i++) {
			if (snake.LN[i].sX == fruit.Location.sX && snake.LN[i].sY == fruit.Location.sY)
			{
				fruit.Location.sX = 0;
				fruit.Location.sY = 0;
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
	snake.LN[0].sX = 15;
	snake.LN[0].sY = 15;
	snake.iN = 3;
	snake.eDirecs = eDirections::RIGHT;
}

// Ve bang, thong tin, menu,...
void TitleMenuMain() {
	LPSTR strTitle = (char*)"XIN CHAO - SNAKE DAY";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 2, (HEIGHT - 5) / 2 - 2, Pink, 0, strTitle);
	strTitle = (char*)"HAY DUA RA SU LUA CHON CUA BAN";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 7, (HEIGHT - 5) / 2 - 1, Green, 0, strTitle);
}

void InforDisplay(std::string strLevel, int& iPoint)
{
	LPSTR StrTitle = (char*)"CAP DO: ";
	SetBackgroundColorTextXY2(WIDTH + 4, 6, Green, 0, StrTitle);
	SetColor(White);
	std::cout << strLevel;
	StrTitle = (char*)"DIEM  : ";
	SetBackgroundColorTextXY2(WIDTH + 4, 7, Green, 0, StrTitle);
	SetColor(White);
	std::cout << iPoint;
	GotoXY(WIDTH / 2 - 7, HEIGHT + 3);
	SetColor(White);
	std::cout << "Snake v1.0 by HuyDinhSE";
}

bool InforDisGameOver(bool bCheck)
{
	if (bCheck)
	{
		AUDIO(IDR_WAVE1);
		bStatusGame = false;
		PaintMenuGameOver(1);
		return true;
	}
	return false;
}

short XCoord(short SX) // Toa do x ve bang.
{
	return ((SX * 2) + 6);
}

short YCoord(short SY) // Toa do y ve bang.
{
	return (SY + 6);
}

void PaintTable()
{
	//SetBackgroundColorTextXY2(5, 5, Yellow, 0, (char*)"%c", 4);
	//SetBackgroundColorTextXY2(106, 5, Yellow, 0, (char*)"%c", 4);
	//SetBackgroundColorTextXY2(5, 31, Yellow, 0, (char*)"%c", 4);
	//SetBackgroundColorTextXY2(106, 31, Yellow, 0, (char*)"%c", 4);
	for (int i = 5; i <= 106; i++)
	{
		SetBackgroundColorTextXY2(i, 5, Yellow, 0, (char*)"%c", 4);
		SetBackgroundColorTextXY2(i, 31, Yellow, 0, (char*)"%c", 4);
	}
	for (int i = 5; i <= 30; i++)
	{
		SetBackgroundColorTextXY2(5, i, Yellow, 0, (char*)"%c", 4);
		SetBackgroundColorTextXY2(106, i, Yellow, 0, (char*)"%c", 4);
	}
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

void PaintBoder()
{
	for (int i = 6; i <= 105; i++)
	{
		//GotoXY(i, 6);
		//SetColor(14);
		//putchar(3);
		SetBackgroundColorTextXY2(i, 6, Yellow, 0, (char*)"%c", 3);
		SetBackgroundColorTextXY2(i, 30, Yellow, 0, (char*)"%c", 3);
		//GotoXY(i, 30);
		//SetColor(14);
		//putchar(3);
	}
	for (int i = 6; i <= 30; i++)
	{
		GotoXY(6, i);
		SetColor(14);
		putchar(5);
		GotoXY(105, i);
		SetColor(14);
		putchar(5);
	}
}

void PaintFruit(Fruit fruit)
{
	srand(time(NULL));
	char iRandom = rand() % 6 + 1;
	SetColor(13);
	GotoXY(116,9);
	std::cout << fruit.Location.sX;
	GotoXY(116, 10);
	std::cout << fruit.Location.sY;
	SetBackgroundColorTextXY2(XCoord(fruit.Location.sX), YCoord(fruit.Location.sY), 14, 0, (char*)"%c ", iRandom);
}

void PaintSnake(Snake snake)
{
	SetBackgroundColorTextXY2(XCoord(snake.LN[0].sX), YCoord(snake.LN[0].sY),11,11, (char*)"  "); // Ve dau con ran
	for (int i = 1; i < snake.iN; i++)
	{
		SetBackgroundColorTextXY2(XCoord(snake.LN[i].sX), YCoord(snake.LN[i].sY), 15, 15, (char*)"  "); // Ve than con ran
	}
	SetBackgroundColorTextXY2(XCoord(snake.LN[snake.iN - 1].sX), YCoord(snake.LN[snake.iN - 1].sY), 8, 0, (char*)"  "); // Xoa duoi con ran
}

void PaintBox(short SX, short SY)
{
	SetBackgroundColorTextXY2(XCoord(SX), YCoord(SY), 0, 0, (char*)"  ");
}

void PaintMenuControlConsole_UP()
{
	SetBackgroundColorTextXY2(116, 13, iUP, 0, (char*)"%c", 30);
	SetBackgroundColorTextXY2(115, 14, iUP, 0, (char*)"%c", 30);
	SetBackgroundColorTextXY2(116, 14, iUP, 0, (char*)"%c", 30);
	SetBackgroundColorTextXY2(117, 14, iUP, 0, (char*)"%c", 30);
}

void PaintMenuControlConsole_LEFT()
{
	SetBackgroundColorTextXY2(112, 15, iLEFT, 0, (char*)"%c", 17);
	SetBackgroundColorTextXY2(111, 16, iLEFT, 0, (char*)"%c", 17);
	SetBackgroundColorTextXY2(112, 16, iLEFT, 0, (char*)"%c", 17);
	SetBackgroundColorTextXY2(112, 17, iLEFT, 0, (char*)"%c", 17);
}

void PaintMenuControlConsole_DOWN()
{
	SetBackgroundColorTextXY2(116, 19, iDOWN, 0, (char*)"%c", 31);
	SetBackgroundColorTextXY2(115, 18, iDOWN, 0, (char*)"%c", 31);
	SetBackgroundColorTextXY2(116, 18, iDOWN, 0, (char*)"%c", 31);
	SetBackgroundColorTextXY2(117, 18, iDOWN, 0, (char*)"%c", 31);

}

void PaintMenuControlConsole_RIGHT()
{
	SetBackgroundColorTextXY2(120, 15, iRIGHT, 0, (char*)"%c", 16);
	SetBackgroundColorTextXY2(120, 16, iRIGHT, 0, (char*)"%c", 16);
	SetBackgroundColorTextXY2(121, 16, iRIGHT, 0, (char*)"%c", 16);
	SetBackgroundColorTextXY2(120, 17, iRIGHT, 0, (char*)"%c", 16);
}

void PaintMenuControlConsole()
{
	PaintMenuControlConsole_UP();
	PaintMenuControlConsole_DOWN();
	PaintMenuControlConsole_LEFT();
	PaintMenuControlConsole_RIGHT();
}

void UpdateKeyControlOnConsole(int iControl)
{
	switch (iControl)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	}
}

void PaintPine()
{
	SetBackgroundColorTextXY2(115, 6, Yellow, Black, (char*)"HUY");
	SetBackgroundColorTextXY2(112, 12, Yellow, Black, (char*)"D I");
	SetBackgroundColorTextXY2(116, 12, Green, Black, (char*)"*");
	SetBackgroundColorTextXY2(118, 12, Yellow, Black, (char*)"N H");
	SetColor(Green);
	int n = 5;
	for ( int i = 1; i <= n; i++) 
	{
		GotoXY(112, 6 + i);
		for (int j = 1; j <= n - i; j++)
			printf(" ");

		for (int j = 1; j <= i; j++)
			printf("* ");

		printf("\n");
	}
	for (int i = 2; i <= n; i++)
	{
		GotoXY(112,11 + i);
		for (int j = 1; j <= n - i; j++)
			printf(" ");

		for (int j = 1; j <= i; j++)
			printf("* ");

		printf("\n");
	}

	SetBackgroundColorTextXY2(112, 17, Yellow, Black, (char*)"2 0");
	SetBackgroundColorTextXY2(116, 17, Yellow, Green, (char*)" ");
	SetBackgroundColorTextXY2(118, 17, Yellow, Black, (char*)"2 1");
	SetBackgroundColorTextXY2(116, 18, Yellow, Green, (char*)"S");
	SetBackgroundColorTextXY2(116, 19, Yellow, Green, (char*)"E");
	SetBackgroundColorTextXY2(116, 20, Yellow, Green, (char*)" ");
}

void PaintMenuMain(short sIndex)
{ 
	 PaintPine();
	 PaintBoder();
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
	AUDIO(IDR_WAVE3);
}

void PaintLevelMenu(short sIndex)
{
	PaintBoder();
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
	AUDIO(IDR_WAVE3);
}

void PaintMenuPause(short sIndex)
{
	sSelectLocation = sIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"  TAM DUNG  ";
	SetBackgroundColorTextXY2(WIDTH + 5, HEIGHT / 2 + 7, White, Green, strTitle);
	strTitle = (char*)"  TIEP TUC  ";
	SetBackgroundColorTextXY(WIDTH + 5, HEIGHT / 2 + 9, White, ((sIndex == 0) ? Red : 0), strTitle, strIcon, ((sIndex == 0) ? Pink : 0), 0);
	strTitle = (char*)"  LUU  ";
	SetBackgroundColorTextXY(WIDTH + 7, HEIGHT / 2 + 10, White, ((sIndex == 1) ? Red : 0), strTitle, strIcon, ((sIndex == 1) ? Pink : 0), 0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH + 6, HEIGHT / 2 + 11, White, ((sIndex == 2) ? Red : 0), strTitle, strIcon, ((sIndex == 2) ? Pink : 0), 0);
	AUDIO(IDR_WAVE3);
}

void PaintMenuGameOver(int iIndex) 
{
	sSelectLocation = iIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"     THUA     ";
	SetBackgroundColorTextXY2(WIDTH + 4, HEIGHT / 2 + 7, White, Green, strTitle);
	strTitle = (char*)"  CHOI LAI  ";
	SetBackgroundColorTextXY(WIDTH + 5, HEIGHT / 2 + 9, White, ((iIndex == 0) ? Red : 0), strTitle, strIcon, ((iIndex == 0) ? Pink : 0), 0);
	strTitle = (char*)"  LUU  ";
	SetBackgroundColorTextXY(WIDTH + 7, HEIGHT / 2 + 10, White, ((iIndex == 1) ? Red : 0), strTitle, strIcon, ((iIndex == 1) ? Pink : 0), 0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH + 6, HEIGHT / 2 + 11, White, ((iIndex == 2) ? Red : 0), strTitle, strIcon, ((iIndex == 2) ? Pink : 0), 0);
}

//void TableCoordSave()
//{
//	SXCoord = ((WIDTH / 2) + 20);
//	SYCoord = (((HEIGHT - 6) - 40) / 2) + 7;
//}

// Dieu khien ran
//void ControlSnake(Snake& snake)
//{
//	while (1)
//	{
//		PaintSnake(snake);
//		for (int i = snake.iN - 1; i > 0; i--)
//		{
//			snake.LN[i] = snake.LN[i - 1];
//		}
//		//PaintSnake(snake);
//		snake.LN[0].sY--;
//		Sleep(200);
//		//ControlHeadSnake(snake);
//	}
//
//	/*if (_kbhit())
//	{
//		int iKey = _getch();
//		iKey = tolower(iKey);
//		if (iKey == 'w' && snake.est != eStatus::DOWN)
//		{
//			snake.est = eStatus::UP;
//		}
//		else if (iKey == 's' && snake.est != eStatus::UP)
//		{
//			snake.est = eStatus::DOWN;
//		}
//		else if(iKey == 'a' && snake.est != eStatus::RIGHT)
//		{
//			snake.est = eStatus::LEFT;
//		}
//		else if(iKey == 'd' && snake.est != eStatus::LEFT)
//		{
//			snake.est = eStatus::RIGHT;
//		}
//	}*/
//	//Nhan va cap nhat trang thai ran di chuyen
//	/*switch (VKControl())
//	{
//	case 1:
//		if (snake.est != eStatus::DOWN)
//		{
//			snake.est = eStatus::UP;
//		}
//		break;
//	case 2:
//		if (snake.est != eStatus::UP)
//		{
//			snake.est = eStatus::DOWN;
//		}
//		break;
//	case 3:
//		if (snake.est != eStatus::RIGHT)
//		{
//			snake.est = eStatus::LEFT;
//		}
//		break;
//	case 4:
//		if (snake.est != eStatus::LEFT)
//		{
//			snake.est = eStatus::RIGHT;
//		}
//		break;
//	}*/
//	//Dieu huong ran
//	//ControlHeadSnake(snake);
//
//	/*if (GetAsyncKeyState(VK_UP) && snake.est != eStatus::DOWN)
//	{
//		snake.est = eStatus::UP;
//	}
//	if (GetAsyncKeyState(VK_DOWN) && snake.est != eStatus::UP)
//	{
//		snake.est = eStatus::DOWN;
//	}
//	if (GetAsyncKeyState(VK_LEFT) && snake.est != eStatus::RIGHT)
//	{
//		snake.est = eStatus::LEFT;
//	}
//	if (GetAsyncKeyState(VK_RIGHT) && snake.est != eStatus::LEFT)
//	{
//		snake.est = eStatus::RIGHT;
//	}*/
//
//}

// Dieu huong
void Directional(Snake& snake)
{
	if (snake.eDirecs == eDirections::UP)
	{
		snake.LN[0].sY--;
	}
	if (snake.eDirecs == eDirections::DOWN)
	{
		snake.LN[0].sY++;
	}
	if (snake.eDirecs == eDirections::LEFT)
	{
		snake.LN[0].sX--;
	}
	if (snake.eDirecs == eDirections::RIGHT)
	{
		snake.LN[0].sX++;
	}
}

void Control(Snake& snake)
{
		PaintSnake(snake);
		for (int i = snake.iN - 1; i > 0; i--)
		{
			snake.LN[i] = snake.LN[i - 1];
		}
}

//int VKControl()
//{
//	if (GetAsyncKeyState(VK_UP))
//	{
//		return 1;
//	}
//	if (GetAsyncKeyState(VK_DOWN))
//	{
//		return 2;
//	}
//	if (GetAsyncKeyState(VK_LEFT))
//	{
//		return 3;
//	}
//	if (GetAsyncKeyState(VK_RIGHT))
//	{
//		return 4;
//	}
//}

//void ControlHeadSnake(Snake& snake)
//{
//	switch (snake.est)
//	{
//	case eStatus::UP:
//		snake.LN[0].sY--;
//		break;
//	case eStatus::DOWN:
//		snake.LN[0].sY++;
//		break;
//	case eStatus::LEFT:
//		snake.LN[0].sX--;
//		break;
//	case eStatus::RIGHT:
//		snake.LN[0].sX++;
//		break;
//	}
//}

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

// Xu ly su kien khi ran di chuyen
void UpdatePoint(int iPoint)
{
	GotoXY(WIDTH + 12, 7);
	SetColor(White);
	SetBackgroundColor(0);
	std::cout << iPoint;
}

void CheckSnake(Snake& snake, Fruit& fruit, int& iPoint)
{
	bool bCheck = false;
	SnakeEatFruit(snake, fruit, iPoint, bCheck);
	bCheck = BCheckGameOver(snake, fruit);
	if (InforDisGameOver(bCheck))
	{
		sPages = 4;
		return;
	}
	Sleep(iTime);
}

void RunEvent(Snake& snake, Fruit& fruit, int iIndex, std::string strLevel, int& iPoint)
{
	sPages = 3;
	bool bCheck = false;
	InforDisplay(strLevel, iPoint);
	PaintTable();
	InitSnake(snake);
	InitFruit(fruit, bCheck);
	PaintSnake(snake);
	PaintFruit(fruit);
	bStatusGame = true;
	AUDIO(IDR_WAVE5);
	/*while (1)
	{
		PaintSnake(snake);
		ControlSnake(snake);
		SnakeEatFruit(snake, fruit, iTime, iPoint, bCheck);
		bCheck = BCheckGameOver(snake, fruit);
		if (InforDisGameOver(bCheck))
		{
			sPages = 4;
				break;
		}
		Sleep(iTime);
	}*/
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

void EventProcessing()
{
	while (1)
	{
		do
		{
			if (bStatusGame == true)
			{
				Control(snake);
				Directional(snake);
				PaintMenuControlConsole();
				CheckSnake(snake, fruit, iPoint);
				iUP = iDOWN = iLEFT = iRIGHT = Yellow;
			}
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
						//UnregisterHotKey(NULL,VK_DOWN);
						KeyboardProcessing(IREventBuffer[i].Event.KeyEvent);
						//else if (IREventBuffer[i].EventType == MOUSE_EVENT)// Su kien chuot.
						//{
						//	std::cout << " X:" << IREventBuffer												[i].Event.MouseEvent.dwMousePosition.X
						//		<< " Y:" << IREventBuffer[i].Event.MouseEvent.dwMousePosition.Y
						//		<< std::endl;
						//}
					}
				}
			}
		} while (!bStatusGame);
	}
}

void SnakeEatFruit(Snake& snake, Fruit& fruit, int& iPoint,bool bCheck)
{
	if ((snake.LN[0].sX == fruit.Location.sX) && (snake.LN[0].sY == fruit.Location.sY)) {
		snake.iN++;
		AUDIO(IDR_WAVE2);
		InitFruit(fruit, bCheck);
		PaintFruit(fruit);
		iPoint++;
		UpdatePoint(iPoint);
		iTime -= 2;
	}
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
			case 1: // Menu Main
				if (bStatusGame == false)
				{
					if (sSelectLocation == 1)
					{
						sSelectLocation = sTotalCatalog;
					}
					else
					{
						sSelectLocation -= 1;
					}
					PaintMenuMain(sSelectLocation);
				}
				break;
			case 2: // Menu level
				if (bStatusGame == false)
				{
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
				}
				break;
			case 3: // Control Snake Up
				if (bStatusGame == true)
				{
					iUP = Red;
					if (snake.eDirecs == eDirections::DOWN)
					{

					}
					else
					{
						snake.eDirecs = eDirections::UP;
					}
					
													
					//SetBackgroundColor(2);
					//std::cout << iDirect;  Check thu nhung khong chay vao
					//while (1)
					//{
					//PaintSnake(snake);
					//Control(snake, 1);
					//snake.LN[0].sY--;
					//Sleep(100);
					/*if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
					{
						break;
					}*/
					//}
				}
				break;
			case 4: // Game Over
				if (bStatusGame == false)
				{
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
						AUDIO(IDR_WAVE3);
					}
				}
				break;
			
			case 5: // Pause
				if (bStatusGame == false)
				{
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
				}
				break;
			}
			break;
		case VK_DOWN:
			switch (sPages)
			{
			case 1: // Menu Main
				if (bStatusGame == false)
				{
					if (sSelectLocation == sTotalCatalog)
					{
						(sTotalCatalog == 4) ? sSelectLocation = 1 : sSelectLocation = 0;
					}
					else
					{
						sSelectLocation += 1;
					}
					PaintMenuMain(sSelectLocation);
				}
				break;
			case 2: // Menu level
				if (bStatusGame == false)
				{
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
				}
				break;
			case 3: // Control Snake DOWN
				if (bStatusGame == true)
				{
					iDOWN = Red;
					if (snake.eDirecs == eDirections::UP)
					{

					}
					else
					{
						snake.eDirecs = eDirections::DOWN;
					}
					
					//Control(snake, 2);
					/*if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
					{
						break;
					}*/
				}
				break;
			case 4: // Display Game Over
				if (bStatusGame == false)
				{
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
						AUDIO(IDR_WAVE3);
					}
				}
				break;
			case 5: // Pause
				if (bStatusGame == false)
				{
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
				}
				break;
			}
			break;
		case VK_LEFT:
			if (bStatusGame == true)
			{
				if (snake.eDirecs == eDirections::RIGHT)
				{
					iLEFT = Red;
				}
				else
				{
					snake.eDirecs = eDirections::LEFT;
					iLEFT = Red;
				}
				
				//while (1)
				//{
				//PaintSnake(snake);
				//Control(snake, 3);
				//snake.LN[0].sX--;
				//Sleep(100);
				/*if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
				{
					break;
				}*/
				//}
			}
			break;
		case VK_RIGHT:
			if (bStatusGame == true)
			{
				if (snake.eDirecs == eDirections::LEFT)
				{
					iRIGHT = Red;
				}
				else
				{
					snake.eDirecs = eDirections::RIGHT;
					iRIGHT = Red;
				}

				/*while (1)
				{
					PaintSnake(snake);
					Control(snake);
					snake.LN[0].sX++;
					Sleep(100);
					if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
					{
						break;
					}
				}*/
				//Control(snake, 4);
			}
			break;
		case VK_RETURN: // Enter
			switch (sPages)
			{
			case 1:
				if (sSelectLocation == 1)
				{
					iTime = 120;
					sPages = 3;
					DeleteRow(7, HEIGHT + 1);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iPoint);
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
					RunEvent(snake, fruit, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 1)
				{
					iTime = 95;
					strLevel = "TB";
					sPages = 3;
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 2)
				{
					iTime = 75;
					strLevel = "KHO";
					sPages = 3;
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iPoint);
				}
				else if (sSelectLocation == 3)
				{
					sPages = 1;
					DeleteRow(11, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 4: // Game Over
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
					iTime = 120;
					RunEvent(snake, fruit, sSelectLocation, strLevel, iPoint = 0);
				}
				else if (sSelectLocation == 2)
				{
					sPages = 1;
					DeleteRow(5, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 5: // Pause
				if (bStatusGame == false)
				{
					if (sSelectLocation == 0)
					{
						sPages = 3;
						bStatusGame = true;
						DeleteRow(15, 20);
						PaintTable();
						PaintSnake(snake);
						PaintFruit(fruit);
					}
					else if (sSelectLocation == 1)
					{

					}
					else if (sSelectLocation == 2)
					{
						sPages = 1;
						DeleteRow(5, HEIGHT);
						PaintMenuMain(1);
					}
				}
				break;
			}
			break;
		case VK_ESCAPE: // ESC
		{
			switch (sPages)
			{
			case 1:
				exit(0);
				break;
			case 2:
				sPages = 1;
				DeleteRow(5, HEIGHT);
				PaintMenuMain(1);
				break;
			case 3:
				sPages = 5;
				bStatusGame = false;
				PaintMenuPause(sSelectLocation);
				break;
			case 4:
				sPages = 1;
				DeleteRow(5, HEIGHT);
				PaintMenuMain(1);
				break;
			}
		}
		}
	}
}

// Luu ten
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

