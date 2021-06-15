#include "Function.h"
#include "Console.h"
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

#define WIDTH 100
#define HEIGHT 30
#define WALL 218

#define HEAD 226
#define BODY 111
#define FRUIT 226

#define PI 3.14159265359

//#define HEAD 220
//#define BODY 112
//#define FRUIT 231
Snake snake;
Fruit fruit;
PLAYER Player[10];
int iFruitColor = 1;
int   iTime = 120;
std::string StrIcon = ">>";
std::string StrLevel = "EASY";
int iPoint = 0;
void PaintWall(int iWALL,int iColor, std::string StrLevel, int& iPoint)
{
	InforDisplay(StrLevel,iPoint);
	setColor(iColor);
	//On-Under
	for (int i = 5; i <= WIDTH; i++)
	{
		gotoXY(i,5);
		putchar(iWALL);
		gotoXY(i,4);
		putchar(iWALL);
		gotoXY(i,HEIGHT);
		putchar(iWALL);
		gotoXY(i, HEIGHT + 1);
		putchar(iWALL);
	}

	//Left-Right
	for (int i = 5; i <= HEIGHT; i++)
	{
		gotoXY(4,i);
		putchar(iWALL);
		gotoXY(5,i);
		putchar(iWALL);
		gotoXY(WIDTH,i);
		putchar(iWALL);
		gotoXY(WIDTH + 1,i);
		putchar(iWALL);
	}

	gotoXY(WIDTH / 2 - 7, HEIGHT + 3);
	setColor(White);
	std::cout << "Snake v1.0 by HuyDinhSE";
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

void InforDisplay(std::string StrLevel, int& iPoint) {
	LPSTR StrTitle = (char*)"Level: ";
	setBackgroundColorTextXY(WIDTH + 4, 6, Green, 0, StrTitle, "", 0);
	setColor(White);
	std::cout << StrLevel;
	StrTitle = (char*)"Point: "; 
	setBackgroundColorTextXY(WIDTH + 4, 7, Green, 0, StrTitle, "", 0);
	setColor(White);
	std::cout << iPoint;
}

bool IInforDisGameOver(bool bCheck, int SIndex)
{
	if (bCheck)
	{
		paintMenuGameOver(SIndex);
		return true;
	}
	return false;
}

void paintMenuGameOver(int SIndex) {
	SSelectLocation = SIndex;
	STotalCatalog = 2;

	LPSTR StrTitle = (char*)"  GAME OVER  ";
	setBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2, White, Green, StrTitle, "", 0);
	StrTitle = (char*)"  New Game  ";
	setBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2 + 2, White, ((SIndex == 0) ? Red : 0), StrTitle, StrIcon, ((SIndex == 0) ? Pink : 0));
	StrTitle = (char*)"  Exit  ";
	setBackgroundColorTextXY(WIDTH / 2 - 2, HEIGHT / 2 + 3, White, ((SIndex == 1) ? Red : 0), StrTitle, StrIcon, ((SIndex == 1) ? Pink : 0));
}

void InitFruit(Fruit& fruit, int iFruitColor)
{
	while (1) {
			fruit.location.x = rand() % (WIDTH - 5 -3);
			fruit.location.y = rand() % (HEIGHT -5 -3);
			if ((fruit.location.x > 6 && fruit.location.x < WIDTH) && (fruit.location.y > 5 && fruit.location.y < HEIGHT - 1))
			{
				break;
			}
	}
}

void InitSnake(Snake& snake)
{
	snake.LN[0].x = 45;
	snake.LN[0].y = 25;
	snake.iN = 5;
	snake.est = eStatus::UP;
}

void OnDisplay(Snake snake, Fruit fruit)
{
	setColor(iFruitColor);
	gotoXY(fruit.location.x, fruit.location.y);
	putchar(FRUIT);
	setColor(White);
	gotoXY(snake.LN[0].x, snake.LN[0].y);
	putchar(HEAD);
	setColor(Red);
	for (int i = 1; i < snake.iN; i++)
	{
		gotoXY(snake.LN[i].x, snake.LN[i].y);
		putchar(BODY);
	}
	gotoXY(snake.LN[snake.iN - 1].x, snake.LN[snake.iN - 1].y);
	putchar(' ');
}

void ControlSnake(Snake& snake, Fruit& fruit)
{
	for (int i = snake.iN - 1; i > 0; i--)
	{
		snake.LN[i] = snake.LN[i - 1];
	}

	if (_kbhit())
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
		snake.LN[0].y--;
	}
	else if (snake.est == eStatus::DOWN)
	{
		snake.LN[0].y++;
	}
	else if (snake.est == eStatus::LEFT)
	{
		snake.LN[0].x--;
	}
	else if (snake.est == eStatus::RIGHT)
	{
		snake.LN[0].x++;
	}
}

void UpdatePoint(int Point)
{
	gotoXY(WIDTH + 11, 7);
	setColor(White);
	std::cout << Point;
}

void RunEvent(Snake &snake, Fruit &fruit, int iTime,int SIndex, std::string StrLevel, int &iPoint)
{
	bool bCheck = false;
	PaintWall(WALL, Grey, StrLevel,iPoint);
	InitSnake(snake);
	InitFruit(fruit,iFruitColor);
	while (1)
	{
		OnDisplay(snake, fruit);
		ControlSnake(snake, fruit); 
		CheckSnake_Fruit(snake, fruit, iTime,iPoint);
		bCheck = BCheckGameOver(snake, fruit);
		if (IInforDisGameOver(bCheck, SIndex))
		{
			//while (_getch() != 13);
			SPages = 4;
			break;
		}
		Sleep(iTime);
	}
}

void CheckSnake_Fruit(Snake& snake, Fruit& fruit, int& time, int& iPoint)
{
	if ((snake.LN[0].x == fruit.location.x) && (snake.LN[0].y == fruit.location.y)) {
		snake.iN++;
		ControlSnake(snake, fruit);
		iFruitColor = rand() % 15;
		InitFruit(fruit, iFruitColor);
		iPoint++;
		UpdatePoint(iPoint);
		time -= 3;
	}
}

bool BCheckGameOver(Snake& snake, Fruit& fruit)
{
	if ((snake.LN[0].x < 7 || snake.LN[0].x >= WIDTH) || (snake.LN[0].y < 6 || snake.LN[0].y >= HEIGHT))
	{
		return true;
	}
	for (int i = 1; i < snake.iN; i++) {
		if ((snake.LN[0].x == snake.LN[i].x) && (snake.LN[0].y == snake.LN[i].y))
		{
			return true;
		}
	}
	return false;
}

void keyboardProcessing(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)
	{
		switch (key.wVirtualKeyCode)
		{
		case VK_UP:
			switch (SPages)
			{
			case 1://Menu Main
				if (SSelectLocation == 1)
				{
					SSelectLocation = STotalCatalog;
				}
				else
				{
					SSelectLocation -= 1;
				}
				paintMenuMain(SSelectLocation);
				break;
			case 2: //menu level
				if (STotalCatalog == 4)
				{
					if (SSelectLocation == 0)
					{
						SSelectLocation = STotalCatalog - 1;
					}
					else
					{
						SSelectLocation -= 1;
					}
					paintLevelMenu(SSelectLocation);
				}
				break;
			case 4://Display Game Over
				if (STotalCatalog == 2)
				{
					if (SSelectLocation == 0)
					{
						SSelectLocation = STotalCatalog - 1;
					}
					else
					{
						SSelectLocation -= 1;
					}
					paintMenuGameOver(SSelectLocation);
				}
				break;
			}
			break;
		case VK_DOWN:
			switch (SPages)
			{
			case 1://Menu Main
				if (SSelectLocation == STotalCatalog)
				{
					(STotalCatalog == 4) ? SSelectLocation = 1 : SSelectLocation = 0;
				}
				else
				{
					SSelectLocation += 1;
				}
				paintMenuMain(SSelectLocation);
				break;
			case 2: //menu level
				if (STotalCatalog == 4)
				{
					if (SSelectLocation == STotalCatalog - 1)
					{
						SSelectLocation = 0;
					}
					else
					{
						SSelectLocation += 1;
					}
					paintLevelMenu(SSelectLocation);
				}
				break;
			case 4://Display Game Over
				if (STotalCatalog == 2)
				{
					if (SSelectLocation == STotalCatalog - 1)
					{
						SSelectLocation = 0;
					}
					else
					{
						SSelectLocation += 1;
					}
					paintMenuGameOver(SSelectLocation);
				}
				break;
			}
			break;
		case VK_RETURN:
			switch (SPages)
			{
			case 1:
				if (SSelectLocation == 1)
				{
					iTime = 120;
					SPages = 3;
					deleteRow(7, HEIGHT + 1);
					RunEvent(snake, fruit, iTime, SSelectLocation, StrLevel,iPoint);
					AUDIO(104);
				}
				else if (SSelectLocation == 2)
				{
					SPages = 2;
					deleteRow(11, 6);
					paintLevelMenu(0);
				}
				else if (SSelectLocation == 3)
				{
					SPages = 2;
					deleteRow(1,HEIGHT);
					Point();
					SPages = 1;
					deleteRow(4, HEIGHT);
					paintMenuMain(0);
				}
				else if (SSelectLocation == 4)
				{
					exit(0);
				}
				break;
			case 2:
				if (SSelectLocation == 0)
				{
					iTime = 120;
					StrLevel = "EASY";
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation, StrLevel,iPoint);
				}
				else if (SSelectLocation == 1)
				{
					iTime = 95;
					StrLevel = "NORMAL";
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation, StrLevel,iPoint);
				}
				else if (SSelectLocation == 2)
				{
					iTime = 75;
					StrLevel = "HARD";
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation, StrLevel, iPoint);
				}
				else if (SSelectLocation == 3)
				{
					SPages = 1;
					deleteRow(11, HEIGHT);
					paintMenuMain(0);
				}
				break;
			case 4://Trang thua
				if (SSelectLocation == 1)
				{
					SaveName(iPoint);
					SPages = 1;
					deleteRow(4,HEIGHT);
					paintMenuMain(0);
				}
				else if (SSelectLocation == 0)
				{
					SPages = 4;
					deleteRow(4, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation,StrLevel,iPoint = 0);
				}
				break;
			}
			break;
		}
	}
}

void SaveName(int iPoint)
{
	LPSTR StrTitle = (char*)"      Name     ";
	setBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2 + 2, Black, White, StrTitle, "", 0);
	StrTitle = (char*)"               ";
	setBackgroundColorTextXY(WIDTH / 2 - 4, HEIGHT / 2 + 3, Black, White, StrTitle, "", 0);
	setColor(Black);
	char* Name = new char[10];
	gotoXY(WIDTH / 2 + 2, HEIGHT / 2 + 3);
	cin >> Name;

	//Write File
	FILE* _FileOut;
	errno_t _ErrOut = fopen_s(&_FileOut, "rank.txt", "a");
	/*if (_ErrOut)
	{
		cout << "Mo file out khong thanh cong!" << endl;
	}*/

	string Str = "\t\t";
	Str += to_string(iPoint);
	Str += "\n";
	char const* cPoint = Str.c_str();
	char const* cInfor = Name;
	fputs(cInfor, _FileOut);
	fputs(cPoint, _FileOut);
	delete[] Name;
	fclose(_FileOut);

	//Player->Name[(iNumPlayer++)] = (char)Name;
	//Player->iPoint = iPoint;
}

void Point()
{
	LPSTR StrTitle1 = (char*)"     TOP SERVER     ";
	setBackgroundColorTextXY(WIDTH / 2,6, Yellow,Red, StrTitle1, "", 0);
	LPSTR StrTitle2 = (char*)"                    ";
	for (int i = 7; i <= 22; i++)
	{
		for (int j = WIDTH / 2 - 5; j < WIDTH / 2 + 5; j++)
		{
			setBackgroundColorTextXY(j,i, Black, White, StrTitle2, "", 0);
		}
	}
	//gotoXY(WIDTH / 2 + 2, HEIGHT / 2 - 5);
	setColor(Black);
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
	char _Str[20];
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
	while(fscanf_s(_FileIn,"%[^\n]",_Str, __crt_countof(_Str)) != EOF)
	{
		gotoXY(WIDTH / 2 + 2, (HEIGHT / 2 - 5) + i);
		printf_s("%s", _Str);
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

void paintBorder()
{
	int iColor = rand() % 15;
	PaintWall(95, iColor,"", iPoint);
	Sleep(90);
	if (iColor == 15)
	{
		iColor = 1;
	}
}

void eventProcessing()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0; // Luu lai su kien hien tai.
		DWORD DWNumberOfEventsRead = 0; // Luu lai so luong su kien da duoc loc.

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // Thiet bi dau vao.
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents); // Dat su kien dau vao cua giao dien cho bien DWNumberOfEvents.
		PaintWall(95, 15, "", iPoint);
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
						keyboardProcessing(IREventBuffer[i].Event.KeyEvent);			
					}
					paintBorder();
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
	LPSTR StrTitle = (char*)"WELLCOME TO SNAKE";
	setBackgroundColorTextXY((WIDTH - 5) / 2 - 2, (HEIGHT - 5) / 2 - 2, Pink,0, StrTitle,"",0);
	StrTitle = (char*)"What Do You Want To Choose?";
	setBackgroundColorTextXY((WIDTH - 5) / 2 - 7, (HEIGHT - 5) / 2 - 1, Green, 0, StrTitle, "", 0);
}

void paintMenuMain(short SIndex)
{ 
	 SSelectLocation = SIndex;
	 STotalCatalog = 4;
	 TitleMenuMain();

	//Ve Menu
	 short SW = ((WIDTH - 5) / 2) + 2;
	 short SH = ((HEIGHT - 5) / 2 + 3);
	LPSTR StrTitle = (char*)"  NEW GAME  ";
	setBackgroundColorTextXY(SW - 1, SH, White, ((SIndex == 1) ? Red : 0), StrTitle, StrIcon, ((SIndex == 1) ? Pink : 0));
	StrTitle = (char*)"  LEVEL  ";
	setBackgroundColorTextXY(SW,SH + 1, White, ((SIndex == 2) ? Red : 0), StrTitle, StrIcon, ((SIndex == 2) ? Pink : 0));
	StrTitle = (char*)"  POINT  ";
	setBackgroundColorTextXY(SW,SH + 2, White, ((SIndex == 3) ? Red : 0), StrTitle, StrIcon, ((SIndex == 3) ? Pink : 0));
	StrTitle = (char*)"  EXIT   ";
	setBackgroundColorTextXY(SW,SH + 3, White, ((SIndex == 4) ? Red : 0), StrTitle, StrIcon, ((SIndex == 4) ? Pink : 0));
}
void paintLevelMenu(short SIndex)
{
	SSelectLocation = SIndex;
	STotalCatalog = 4;
	setColor(Green);
	LPSTR StrTitleLevel = (char*)"  CHOOSE LEVEL  ";
	setBackgroundColorTextXY(((WIDTH - 5) / 2) - 2, ((HEIGHT - 5) / 2) + 2, Blue,0, StrTitleLevel,"",0);

	short SW = ((WIDTH - 5) / 2) + 1;
	short SH = ((HEIGHT - 5) / 2) + 4;
	LPSTR StrTitle = (char*)"  EASY  ";
	setBackgroundColorTextXY(SW + 1, SH, White, ((SIndex == 0) ? Red : 0), StrTitle, StrIcon, ((SIndex == 0) ? Pink : 0));
	StrTitle = (char*)"  NORMAL  ";
	setBackgroundColorTextXY(SW, SH + 1, White, ((SIndex == 1) ? Red : 0), StrTitle, StrIcon, ((SIndex == 1) ? Pink : 0));
	StrTitle = (char*)"  HARD ";
	setBackgroundColorTextXY(SW+1, SH + 2, White, ((SIndex == 2) ? Red : 0), StrTitle, StrIcon, ((SIndex == 2) ? Pink : 0));
	StrTitle = (char*)"  EXIT  ";
	setBackgroundColorTextXY(SW + 1, SH + 3, White, ((SIndex == 3) ? Red : 0), StrTitle, StrIcon, ((SIndex == 3) ? Pink : 0));
}


