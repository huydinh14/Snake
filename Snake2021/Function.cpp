#include "console.hpp"
#include "define.hpp"
#include "function.hpp"
#include "main.hpp"

int iUP = YELLOW;
int iDOWN = YELLOW;
int iLEFT = YELLOW;
int iRIGHT = YELLOW;

Snake snake;
Fruit fruit;
std::vector<Player> player;
int* iArrLocX;
int* iArrLocY;

std::string strIcon = ">>";
std::string strLevel = "DE";

bool bStatusGame = false;
bool bContinueGame = false;

int iScore = 0;

// Luu choi lai
// iContinueDirectionSnake (1 - 2 - 3 - 4) ~ (UP - DOWN - LEFT - RIGHT)
int iContinueLengthSnake = 3;
int iContinueLocationSnakeX = 0;
int iContinueLocationSnakeY = 0;
int iContinueDirectionSnake = 4;
int iContinueLocationFruitX = 0;
int iContinueLocationFruitY = 0;
int iContinueGameScore = 0;
int iContinueGameSpeed = 120;
std::string strContinueGameLevel = "DE";

// Toc do ran
int iTime = 150;

void InitFruit(Fruit& fruit, bool bCheck)
{
	srand(time(NULL));
	while (!bCheck)
	{
		fruit.Location.sX = rand() % 50;
		fruit.Location.sY = rand() % 25;
		for (int i = 0; i < snake.iLength - 1; i++)
		{
			if ((snake.LN[i].sX == fruit.Location.sX) && (snake.LN[i].sY == fruit.Location.sY))
			{
				fruit.Location.sX = 0;
				fruit.Location.sY = 0;
			}
		}
		if ((fruit.Location.sX != 0) && (fruit.Location.sY != 0))
		{
			break;
		}
	}
	if (bContinueGame)
	{
		fruit.Location.sX = iContinueLocationFruitX;
		fruit.Location.sY = iContinueLocationFruitY;
	}
}

void InitSnake(Snake& snake)
{
	if (!bContinueGame)
	{
		snake.LN[0].sX = 15;
		snake.LN[0].sY = 15;
		snake.iLength = 3;
		snake.eDirecs = eDirections::RIGHT;
	}
	else
	{
		snake.LN[0].sX = iContinueLocationSnakeX;
		snake.LN[0].sY = iContinueLocationSnakeY;
		snake.iLength = iContinueLengthSnake;
		snake.eDirecs = (iContinueDirectionSnake == 1) ? eDirections::UP : ((iContinueDirectionSnake == 2) ? eDirections::DOWN : ((iContinueDirectionSnake == 3) ? eDirections::LEFT : eDirections::RIGHT));
		for (int i = 1; i < iContinueLengthSnake; i++)
		{
			snake.LN[i].sX = iArrLocX[i - 1];
			snake.LN[i].sY = iArrLocY[i - 1];
		}
		delete iArrLocX;
		delete iArrLocY;
	}
}

// Ve bang, thong tin, menu,...
void TitleMenuMain()
{
	LPSTR strTitle = (char*)"XIN CHAO - SNAKE DAY";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 2, (HEIGHT - 5) / 2 - 2, PINK, 0, strTitle);
	strTitle = (char*)"HAY DUA RA SU LUA CHON CUA BAN";
	SetBackgroundColorTextXY2((WIDTH - 5) / 2 - 7, (HEIGHT - 5) / 2 - 1, GREEN, 0, strTitle);
}

void InforDisplay(std::string strLevel, int& iScore)
{
	LPSTR StrTitle = (char*)"CAP DO: ";
	SetBackgroundColorTextXY2(WIDTH + 4, 6, GREEN, 0, StrTitle);
	SetColor(WHITE);
	std::cout << strLevel;
	StrTitle = (char*)"DIEM  : ";
	SetBackgroundColorTextXY2(WIDTH + 4, 7, GREEN, 0, StrTitle);
	SetColor(WHITE);
	std::cout << iScore;
	GotoXY(WIDTH / 2 - 7, HEIGHT + 3);
	SetColor(WHITE);
	std::cout << "Snake v1.0 by HuyDinhSE";
}

bool InforDisGameOver(bool bCheck)
{
	if (bCheck)
	{
		bStatusGame = false;
		PaintMenuGameOver(0);
		AUDIO(IDR_WAVE1);
		return true;
	}
	return false;
}

short XCoord(short sX) // Toa do x ve bang.
{
	return ((sX * 2) + 6);
}

short YCoord(short sY) // Toa do y ve bang.
{
	return (sY + 6);
}

void PaintTable()
{
	for (int i = 5; i <= WIDTH; i++)
	{
		SetBackgroundColorTextXY2(i, 5, YELLOW, 0, (char*)"%c", 4);
		SetBackgroundColorTextXY2(i, HEIGHT + 1, YELLOW, 0, (char*)"%c", 4);
	}

	for (int i = 5; i <= HEIGHT; i++)
	{
		SetBackgroundColorTextXY2(5, i, YELLOW, 0, (char*)"%c", 4);
		SetBackgroundColorTextXY2(WIDTH, i, YELLOW, 0, (char*)"%c", 4);
	}

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
	for (int i = 6; i < WIDTH; i++)
	{
		SetBackgroundColorTextXY2(i, 6, YELLOW, 0, (char*)"%c", 3);
		SetBackgroundColorTextXY2(i, 30, YELLOW, 0, (char*)"%c", 3);
	}

	for (int i = 6; i <= HEIGHT; i++)
	{
		SetBackgroundColorTextXY2(6, i, YELLOW, 0, (char*)"%c", 5);
		SetBackgroundColorTextXY2(105, i, YELLOW, 0, (char*)"%c", 5);
	}
}

void PaintFruit(Fruit fruit)
{
	srand(time(NULL));
	char cRandom = rand() % 6 + 1;
	SetColor(13);
	GotoXY(116, 9);
	std::cout << fruit.Location.sX;
	GotoXY(116, 10);
	std::cout << fruit.Location.sY;
	SetBackgroundColorTextXY2(XCoord(fruit.Location.sX), YCoord(fruit.Location.sY), 14, 0, (char*)"%c ", cRandom);
}

void PaintSnake(Snake snake)
{
	SetBackgroundColorTextXY2(XCoord(snake.LN[0].sX), YCoord(snake.LN[0].sY), 11, 11, (char*)"  "); // Ve dau con ran
	for (int i = 1; i < snake.iLength; i++)
	{
		SetBackgroundColorTextXY2(XCoord(snake.LN[i].sX), YCoord(snake.LN[i].sY), 15, 15, (char*)"  "); // Ve than con ran
	}
	SetBackgroundColorTextXY2(XCoord(snake.LN[snake.iLength - 1].sX), YCoord(snake.LN[snake.iLength - 1].sY), 8, 0, (char*)"  "); // Xoa duoi con ran
}

void PaintBox(short sX, short sY)
{
	SetBackgroundColorTextXY2(XCoord(sX), YCoord(sY), 0, 0, (char*)"  ");
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

void PaintPine()
{
	SetBackgroundColorTextXY2(115, 6, YELLOW,BLACK, (char*)"HUY");
	SetBackgroundColorTextXY2(112, 12, YELLOW,BLACK, (char*)"D I");
	SetBackgroundColorTextXY2(116, 12, GREEN,BLACK, (char*)"*");
	SetBackgroundColorTextXY2(118, 12, YELLOW,BLACK, (char*)"N H");

	SetColor(GREEN);
	int n = 5;
	for ( int i = 1; i <= n; i++)
	{
		GotoXY(112, 6 + i);
		for (int j = 1; j <= (n - i); j++)
		{
			printf(" ");
		}

		for (int j = 1; j <= i; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

	for (int i = 2; i <= n; i++)
	{
		GotoXY(112, 11 + i);
		for (int j = 1; j <= (n - i); j++)
		{
			printf(" ");
		}

		for (int j = 1; j <= i; j++)
		{
			printf("* ");
		}
		printf("\n");
	}

	SetBackgroundColorTextXY2(112, 17, YELLOW,BLACK, (char*)"2 0");
	SetBackgroundColorTextXY2(116, 17, YELLOW, GREEN, (char*)" ");
	SetBackgroundColorTextXY2(118, 17, YELLOW,BLACK, (char*)"2 1");
	SetBackgroundColorTextXY2(116, 18, YELLOW, GREEN, (char*)"S");
	SetBackgroundColorTextXY2(116, 19, YELLOW, GREEN, (char*)"E");
	SetBackgroundColorTextXY2(116, 20, YELLOW, GREEN, (char*)" ");
}

void PaintMenuMain(short sIndex)
{ 
	TitleMenuMain();
	PaintBoder();
	PaintPine();
	sSelectLocation = sIndex;
	sTotalCatalog = 4;

	//Ve Menu
	short sW = ((WIDTH - 5) / 2) + 2;
	short sH = ((HEIGHT - 5) / 2 + 3);

	LPSTR strTitle = (char*)"  CHOI NGAY  ";
	SetBackgroundColorTextXY(sW, sH, WHITE, ((sIndex == 1) ? RED : 0), strTitle, strIcon, ((sIndex == 1) ? PINK : 0), 0);
	strTitle = (char*)"  CAP DO  ";
	SetBackgroundColorTextXY(sW, sH + 1, WHITE, ((sIndex == 2) ? RED : 0), strTitle, strIcon, ((sIndex == 2) ? PINK : 0), 0);
	strTitle = (char*)"  DIEM SO  ";
	SetBackgroundColorTextXY(sW, sH + 2, WHITE, ((sIndex == 3) ? RED : 0), strTitle, strIcon, ((sIndex == 3) ? PINK : 0), 0);
	strTitle = (char*)"  THOAT   ";
	SetBackgroundColorTextXY(sW, sH + 3, WHITE, ((sIndex == 4) ? RED : 0), strTitle, strIcon, ((sIndex == 4) ? PINK : 0), 0);
	if (bContinueGame)
	{
		strTitle = (char*)"  TIEP TUC  ";
		SetBackgroundColorTextXY(sW, sH - 1, WHITE, ((sIndex == 0) ? RED : 0), strTitle, strIcon, ((sIndex == 0) ? PINK : 0), 0);
	}

	AUDIO(IDR_WAVE3);
}

void PaintLevelMenu(short sIndex)
{
	PaintBoder();
	sSelectLocation = sIndex;
	sTotalCatalog = 4;
	SetColor(GREEN);
	LPSTR strTitleLevel = (char*)"  CHON CAP DO  ";
	SetBackgroundColorTextXY2(((WIDTH - 5) / 2), ((HEIGHT - 5) / 2), BLUE, 0, strTitleLevel);

	short sW = ((WIDTH - 5) / 2) + 5;
	short sH = ((HEIGHT - 5) / 2) + 2;
	LPSTR strTitle = (char*)"  DE  ";
	SetBackgroundColorTextXY(sW, sH, WHITE, ((sIndex == 0) ? RED : 0), strTitle, strIcon, ((sIndex == 0) ? PINK : 0), 0);
	strTitle = (char*)"  TRUNG BINH  ";
	SetBackgroundColorTextXY(sW - 4, sH + 1, WHITE, ((sIndex == 1) ? RED : 0), strTitle, strIcon, ((sIndex == 1) ? PINK : 0), 0);
	strTitle = (char*)"  KHO ";
	SetBackgroundColorTextXY(sW, sH + 2, WHITE, ((sIndex == 2) ? RED : 0), strTitle, strIcon, ((sIndex == 2) ? PINK : 0), 0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(sW - 1, sH + 3, WHITE, ((sIndex == 3) ? RED : 0), strTitle, strIcon, ((sIndex == 3) ? PINK : 0), 0);

	AUDIO(IDR_WAVE3);
}

void PaintMenuPause(short sIndex)
{
	sSelectLocation = sIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"  TAM DUNG  ";
	SetBackgroundColorTextXY2(WIDTH + 5, HEIGHT / 2 + 7, WHITE, GREEN, strTitle);
	strTitle = (char*)"  TIEP TUC  ";
	SetBackgroundColorTextXY(WIDTH + 5, HEIGHT / 2 + 9, WHITE, ((sIndex == 0) ? RED : 0), strTitle, strIcon, ((sIndex == 0) ? PINK : 0), 0);
	strTitle = (char*)"LUU CHOI SAU ";
	SetBackgroundColorTextXY(WIDTH + 4, HEIGHT / 2 + 10, WHITE, ((sIndex == 1) ? RED : 0), strTitle, strIcon, ((sIndex == 1) ? PINK : 0), 0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH + 6, HEIGHT / 2 + 11, WHITE, ((sIndex == 2) ? RED : 0), strTitle, strIcon, ((sIndex == 2) ? PINK : 0), 0);

	AUDIO(IDR_WAVE3);
}

void PaintMenuGameOver(int iIndex)
{
	sSelectLocation = iIndex;
	sTotalCatalog = 3;

	LPSTR strTitle = (char*)"     THUA     ";
	SetBackgroundColorTextXY2(WIDTH + 4, HEIGHT / 2 + 7, WHITE, GREEN, strTitle);
	strTitle = (char*)"  CHOI LAI  ";
	SetBackgroundColorTextXY(WIDTH + 5, HEIGHT / 2 + 9, WHITE, ((iIndex == 0) ? RED : 0), strTitle, strIcon, ((iIndex == 0) ? PINK : 0), 0);
	strTitle = (char*)"  LUU  ";
	SetBackgroundColorTextXY(WIDTH + 7, HEIGHT / 2 + 10, WHITE, ((iIndex == 1) ? RED : 0), strTitle, strIcon, ((iIndex == 1) ? PINK : 0), 0);
	strTitle = (char*)"  THOAT  ";
	SetBackgroundColorTextXY(WIDTH + 6, HEIGHT / 2 + 11, WHITE, ((iIndex == 2) ? RED : 0), strTitle, strIcon, ((iIndex == 2) ? PINK : 0), 0);
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
		iContinueDirectionSnake = 1;
	}
	if (snake.eDirecs == eDirections::DOWN)
	{
		snake.LN[0].sY++;
		iContinueDirectionSnake = 2;
	}
	if (snake.eDirecs == eDirections::LEFT)
	{
		snake.LN[0].sX--;
		iContinueDirectionSnake = 3;
	}
	if (snake.eDirecs == eDirections::RIGHT)
	{
		snake.LN[0].sX++;
		iContinueDirectionSnake = 4;
	}
}

void Control(Snake& snake)
{
		PaintSnake(snake);
		for (int i = snake.iLength - 1; i > 0; i--)
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
void CheckSnake(Snake& snake, Fruit& fruit, int& iScore)
{
	bool bCheck = false;
	SnakeEatFruit(snake, fruit, iScore, bCheck);
	bCheck = BCheckGameOver(snake, fruit);
	if (InforDisGameOver(bCheck))
	{
		sPages = 4;
		bContinueGame = false;
		return;
	}
	Sleep(iTime);
	AUDIO(102);
}

// Su kien khi ran an moi
void UpdatePoint(int iScore)
{
	GotoXY(WIDTH + 12, 7);
	SetColor(WHITE);
	SetBackgroundColor(0);
	std::cout << iScore;
}

void RunEvent(Snake& snake, Fruit& fruit, int iIndex, std::string strLevel, int& iScore)
{
	sPages = 3;
	iScore = 0;
	bool bCheckFruit = false;
	bStatusGame = true;
	PaintTable();
	InforDisplay(strLevel, iScore);
	if (bContinueGame)
	{
		ContinueGameReadFile();
		InforDisplay(strContinueGameLevel, iScore);
		UpdatePoint(iScore);
		InitSnake(snake);
		InitFruit(fruit, bCheckFruit);
		PaintSnake(snake);
		PaintFruit(fruit);
		iTime = iContinueGameSpeed;
	}
	else
	{
		InitSnake(snake);
		InitFruit(fruit, bCheckFruit);
		PaintSnake(snake);
		PaintFruit(fruit);
	}
	bContinueGame = false;
	AUDIO(IDR_WAVE5);
	/*while (1)
	{
		PaintSnake(snake);
		ControlSnake(snake);
		SnakeEatFruit(snake, fruit, iTime, iScore, bCheck);
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
	if (((snake.LN[0].sX < 0) || (snake.LN[0].sX > 49)) || ((snake.LN[0].sY < 0) || (snake.LN[0].sY > 24)))
	{
		return true;
	}
	for (int i = 1; i < snake.iLength; i++)
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
	bContinueGame = (SizeOfFileContinue()) ? true : false;
	if (bContinueGame)
	{
		PaintMenuMain(0);
	}
	else
	{
		PaintMenuMain(1);
	}
	AUDIO(IDR_WAVE4);
	while (1)
	{
		if (bStatusGame)
		{
			Control(snake);
			Directional(snake);
			PaintMenuControlConsole();
			CheckSnake(snake, fruit, iScore);
			iUP = iDOWN = iLEFT = iRIGHT = YELLOW;
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
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) // Neu la su kien phim.
				{
					KeyboardProcessing(IREventBuffer[i].Event.KeyEvent);
					//else if (IREventBuffer[i].EventType == MOUSE_EVENT)// Su kien chuot.
					//{
					//	std::cout << " X:" << IREventBuffer[i].Event.MouseEvent.dwMousePosition.X
					//			  << " Y:" << IREventBuffer[i].Event.MouseEvent.dwMousePosition.Y
					//		      << std::endl;
					//}
				}
			}
		}
	}
}

void SnakeEatFruit(Snake& snake, Fruit& fruit, int& iScore, bool bCheck)
{
	if ((snake.LN[0].sX == fruit.Location.sX) && (snake.LN[0].sY == fruit.Location.sY))
	{
		snake.iLength++;
		iScore++;
		UpdatePoint(iScore);
		InitFruit(fruit, bCheck);
		PaintFruit(fruit);
		iTime -= 2;
		iContinueGameSpeed = iTime;
		AUDIO(IDR_WAVE2);
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
				if (!bStatusGame)
				{
					if ((sSelectLocation == 0) && bContinueGame)
					{
						sSelectLocation = sTotalCatalog;
					}
					else if ((sSelectLocation == 1) && !bContinueGame)
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
				if (!bStatusGame)
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
				if (bStatusGame)
				{
					iUP = RED;
					if (snake.eDirecs == eDirections::DOWN) {} // khong cap nhat
					else
					{
						snake.eDirecs = eDirections::UP;
					}
					
					/*if (snake.eDirecs == eDirections::DOWN); 
					snake.eDirecs = eDirections::UP;*/ /*Error Vi khi ran di xuong (Down), 
					bam di len(UP) thi chay vao IF dung(true - dang trang thai di xuong), khong duoc cap nhat bien snake.eDirecs di len (UP). Nhu vay sai logic game, tuc la ran bi quay dau*/

					/*while (1)
					{
					PaintSnake(snake);
					Control(snake, 1);
					snake.LN[0].sY--;
					Sleep(100);
					if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
					{
						break;
					}*/
				}
				break;
			case 4: // Game Over
				if (!bStatusGame)
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
				if (!bStatusGame)
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
				if (!bStatusGame)
				{
					if (sSelectLocation == sTotalCatalog)
					{
						if (!bContinueGame)
						{
							(sTotalCatalog == 4) ? sSelectLocation = 1 : sSelectLocation = -1;
						}
						else
						{
							(sTotalCatalog == 4) ? sSelectLocation = 0 : sSelectLocation = -1;
						}
					}
					else
					{
						sSelectLocation += 1;
					}
					PaintMenuMain(sSelectLocation);
				}
				break;
			case 2: // Menu level
				if (!bStatusGame)
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
				if (bStatusGame)
				{
					iDOWN = RED;
					if (snake.eDirecs == eDirections::UP) {}// khong cap nhat
					else
					{
						snake.eDirecs = eDirections::DOWN;
					}
					
					/*Control(snake, 2);
					if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState(VK_RIGHT))
					{
						break;
					}*/
				}
				break;
			case 4: // Display Game Over
				if (!bStatusGame)
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
				if (!bStatusGame)
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
			if (bStatusGame)
			{
				iLEFT = RED;
				if (snake.eDirecs == eDirections::RIGHT) {} // Khong cap nhat
				else
				{
					snake.eDirecs = eDirections::LEFT;
				}
				
				/*while (1)
				{
				PaintSnake(snake);
				Control(snake, 3);
				snake.LN[0].sX--;
				Sleep(100);
				if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState(VK_UP))
				{
					break;
				}*/
			}
			break;
		case VK_RIGHT:
			if (bStatusGame)
			{
				iRIGHT = RED;
				if (snake.eDirecs == eDirections::LEFT) {} // Khong cap nhat
				else
				{
					snake.eDirecs = eDirections::RIGHT;
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
				}
				Control(snake, 4);*/
			}
			break;
		case VK_RETURN: // Enter
			switch (sPages)
			{
			case 1:
				if (sSelectLocation == 0) // Tiep tuc
				{
					sPages = 3;
					//strLevel = iContinueGameLevel;
					DeleteRow(7, HEIGHT + 1);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iScore);
					Sleep(1500);
				}
				else if (sSelectLocation == 1) // Choi ngay
				{
					bContinueGame = false;
					iTime = 120;
					sPages = 3;
					DeleteRow(7, HEIGHT + 1);
					RunEvent(snake, fruit, sSelectLocation, strLevel = "DE", iScore);
				}
				else if (sSelectLocation == 2) // Cap do
				{
					sPages = 2;
					DeleteRow(5, 20);
					PaintLevelMenu(0);
				}
				else if (sSelectLocation == 3) // Diem so
				{
					sPages = 2;
					DeleteRow(1, HEIGHT);
					TopScore();
					sPages = 1;
					DeleteRow(4, HEIGHT);
					PaintMenuMain(1);
				}
				else if (sSelectLocation == 4) // Thoat
				{
					exit(0);
				}
				break;
			case 2:
				if (sSelectLocation == 0)
				{
					sPages = 3;
					iTime = 120;
					strLevel = "DE";
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iScore);
				}
				else if (sSelectLocation == 1)
				{
					sPages = 3;
					iTime = 100;
					strLevel = "TB";
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iScore);
				}
				else if (sSelectLocation == 2)
				{
					sPages = 3;
					iTime = 80;
					strLevel = "KHO";
					DeleteRow(5, HEIGHT);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iScore);
				}
				else if (sSelectLocation == 3) // Thoat
				{
					sPages = 1;
					DeleteRow(11, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 4: // Game Over
				if (sSelectLocation == 0) // Choi lai
				{
					sPages = 4;
					DeleteRow(4, HEIGHT);
					iTime = (strLevel == "DE") ? 120 : ((strLevel == "TB") ? 100 : 80);
					RunEvent(snake, fruit, sSelectLocation, strLevel, iScore = 0);
				}
				else if (sSelectLocation == 1) // Luu
				{
					SaveName(iScore);
					sPages = 1;
					DeleteRow(4, HEIGHT);
					PaintMenuMain(1);
				}
				else if (sSelectLocation == 2) // Thoat
				{
					sPages = 1;
					DeleteRow(5, HEIGHT);
					PaintMenuMain(1);
				}
				break;
			case 5: // Pause
				if (!bStatusGame)
				{
					if (sSelectLocation == 0) // Choi tiep
					{
						sPages = 3;
						bStatusGame = true;
						DeleteRow(15, 20);
						PaintTable();
						PaintSnake(snake);
						PaintFruit(fruit);
						Sleep(1500);
					}
					else if (sSelectLocation == 1) // Luu choi sau
					{
						bContinueGame = true;
						strContinueGameLevel = strLevel;
						ContinueGameWriteFile();
						DeleteRow(5, HEIGHT);
						sPages = 1;
						PaintMenuMain(0);
					}
					else if (sSelectLocation == 2) // Thoat
					{
						sPages = 1;
						bStatusGame = false;
						bContinueGame = false;
						DeleteRow(5, HEIGHT);
						PaintMenuMain(1);
					}
				}
				break;
			}
			break;
		case VK_ESCAPE: // ESC
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
				PaintMenuPause(0);
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

// Luu ten
void InputArrayScorePlayer()
{
	Player pTemp;
	gets_s(pTemp.cName);
	pTemp.iScore = iScore;
	player.push_back(pTemp);
}

void Swap(Player* pl1, Player* pl2)
{
	Player pTemp = *pl1;
	*pl1 = *pl2;
	*pl2 = pTemp;
}

void SaveName(int iScore)
{
	LPSTR strTitle = (char*)"   TEN (KHONG DAU)   ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 8, HEIGHT / 2 + 2, BLACK, RED, strTitle);
	strTitle = (char*)"               ";
	SetBackgroundColorTextXY2(WIDTH / 2 - 5, HEIGHT / 2 + 3, BLACK, WHITE, strTitle);
	ReadFileForSort();
	SetColor(BLACK);
	GotoXY(WIDTH / 2 + 1, HEIGHT / 2 + 3);
	InputArrayScorePlayer();

	// Sap Xep
	int iCountPlayer = player.size();
	if (iCountPlayer > 1)
	{
		for (int i = 0; i < iCountPlayer; i++)
		{
			for (int j = i + 1; j < iCountPlayer; j++)
			{
				if (player[i].iScore < player[j].iScore)
				{
					Swap(&player[i], &player[j]);
				}
			}
		}
	}

	WriteFileUpdate(iCountPlayer);
	player.clear();
}

void ReadFileForSort()
{
	std::ifstream fileIn;
	fileIn.open("rank.txt", std::ios_base::in);
	int iCount = 0;
	int iLine = SizeOfFileRank();
	Player pTemp;
	while (!fileIn.eof())
	{		
		if ((iCount > iLine) || !iLine)
		{
			break;
		}
		fileIn >> pTemp.cName;
		fileIn >> pTemp.iScore;
		player.push_back(pTemp);
		iCount++;
	}
	fileIn.close();
}

void WriteFileUpdate(int iLength)
{
	std::ofstream fileOut;
	fileOut.open("rank.txt", std::ios_base::out);
	for (int i = 0; i < iLength; i++)
	{
		fileOut << player[i].cName << "\t";
		fileOut << player[i].iScore << "\n";
	}
	fileOut.close();
}

int SizeOfFileContinue()
{
	std::ifstream fileIn;
	fileIn.open("continuegame.txt", std::ios_base::in);
	int iLine = 0;
	std::string strLine;
	if(getline(fileIn, strLine))
	{
		++iLine;
	}
	fileIn.close();
	return iLine;
}

int SizeOfFileRank()
{
	std::ifstream fileIn;
	fileIn.open("rank.txt", std::ios_base::in);
	int iLine = 0;
	std::string strLine;
	while (std::getline(fileIn,strLine))
	{
		iLine++;
	}
	fileIn.close();
	return (iLine - 1);
}

void TopScore()
{
	LPSTR strTitle1 = (char*)"     TOP     ";
	SetBackgroundColorTextXY2(WIDTH / 2 + 1, 6, YELLOW, RED, strTitle1);
	LPSTR strTitle2 = (char*)"                    ";
	for (int i = 7; i <= 22; i++)
	{
		for (int j = WIDTH / 2 - 7; j < WIDTH / 2 + 3; j++)
		{
			SetBackgroundColorTextXY2(j , i, BLACK, WHITE, strTitle2);
		}
	}
	SetColor(BLACK);
	ReadFile();
	while (_getch() != 13) {};
}

void ReadFile()
{	
	std::ifstream fileIn;
	fileIn.open("rank.txt", std::ios_base::in);
	char cTopPlayer[20];
	int iCount = 1;
	while (!fileIn.eof() && (iCount < 10))
	{
		GotoXY(WIDTH / 2 + 2, (HEIGHT / 2 - 6) + iCount);
		fileIn.getline(cTopPlayer, '\n');
		iCount++;
		std::cout << cTopPlayer;
	}
	fileIn.close();
}

void ContinueGameWriteFile()
{
	std::ofstream fileOut;
	fileOut.open("continuegame.txt", std::ios_base::out);
	iContinueLengthSnake = snake.iLength;
	iContinueLocationSnakeX = snake.LN->sX;
	iContinueLocationSnakeY = snake.LN->sY;
	iContinueLocationFruitX = fruit.Location.sX;
	iContinueLocationFruitY = fruit.Location.sY;
	iContinueGameScore = iScore;

	fileOut << iContinueLengthSnake << "\n";
	fileOut << iContinueLocationSnakeX << "\n";
	fileOut << iContinueLocationSnakeY << "\n";
	for (int i = 1; i < snake.iLength; i++)
	{
		fileOut << snake.LN[i].sX << "\n";
		fileOut << snake.LN[i].sY << "\n";
	}
	fileOut << iContinueLocationFruitX << "\n";
	fileOut << iContinueLocationFruitY << "\n";
	fileOut << iContinueGameScore << "\n";
	fileOut << iContinueDirectionSnake << "\n";
	fileOut << iContinueGameSpeed << "\n";
	fileOut << strContinueGameLevel;
	fileOut.close();
}

void ContinueGameReadFile()
{
	std::ifstream fileIn;
	fileIn.open("continuegame.txt", std::ios_base::in);
	fileIn >> iContinueLengthSnake;
	fileIn >> iContinueLocationSnakeX;
	fileIn >> iContinueLocationSnakeY;
	iArrLocX = new int[iContinueLengthSnake];
	iArrLocY = new int[iContinueLengthSnake];
	for (int i = 0; i < iContinueLengthSnake - 1; i++)
	{
		fileIn >> iArrLocX[i];
		fileIn >> iArrLocY[i];
	}
	fileIn >> iContinueLocationFruitX;
	fileIn >> iContinueLocationFruitY;
	fileIn >> iScore;
	fileIn >> iContinueDirectionSnake;
	fileIn >> iContinueGameSpeed;
	fileIn >> strContinueGameLevel;
	fileIn.close();
	remove("continuegame.txt");
}