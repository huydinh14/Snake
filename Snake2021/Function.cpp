#include "Function.h"
#include "Console.h"
#include "main.h"

#define Green			2
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
#define WALL 219

#define HEAD 233
#define BODY 111
#define FRUIT 232

Snake snake;
Fruit fruit;
int   iTime = 120;
std::string StrIcon = ">>";

void PaintWall()
{
	InforDisplay();
	setColor(Grey);
	//On-Under
	for (int i = 5; i <= WIDTH; i++)
	{
		gotoXY(i,5);
		putchar(WALL);
		gotoXY(i,HEIGHT);
		putchar(WALL);
	}

	//Left-Right
	for (int i = 5; i <= HEIGHT; i++)
	{
		gotoXY(4,i);
		putchar(WALL);
		gotoXY(5,i);
		putchar(WALL);
		gotoXY(WIDTH,i);
		putchar(WALL);
		gotoXY(WIDTH + 1,i);
		putchar(WALL);
	}
}

void InforDisplay() {
	setColor(Green);
	gotoXY(WIDTH + 4, 5);
	std::cout << "Level: ";

	setColor(Green);
	gotoXY(WIDTH + 4, 6);
	std::cout << "Point: ";
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
	setBackgroundColorTextXY(WIDTH / 2 - 5, HEIGHT / 2, White, Green, StrTitle, "", 0);
	StrTitle = (char*)"  New Game  ";
	setBackgroundColorTextXY(WIDTH / 2 - 5, HEIGHT / 2 + 2, White, ((SIndex == 0) ? Red : 0), StrTitle, StrIcon, ((SIndex == 0) ? Pink : 0));
	StrTitle = (char*)"  Exit  ";
	setBackgroundColorTextXY(WIDTH / 2 - 3, HEIGHT / 2 + 3, White, ((SIndex == 1) ? Red : 0), StrTitle, StrIcon, ((SIndex == 1) ? Pink : 0));
}

void InitFruit(Fruit& fruit)
{
	while (1) {
			fruit.location.x = rand() % (WIDTH - 5 -3);
			fruit.location.y = rand() % (HEIGHT -5 -3);
			if ((fruit.location.x > 5 && fruit.location.x < WIDTH) && (fruit.location.y > 5 && fruit.location.y < HEIGHT))
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
	snake.est = eStatus::RIGHT;
}

void OnDisplay(Snake snake, Fruit fruit)
{
	setColor(Yellow);
	gotoXY(fruit.location.x, fruit.location.y);
	putchar(FRUIT);

	setColor(Red);
	gotoXY(snake.LN[0].x, snake.LN[0].y);
	putchar(HEAD);
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

void RunEvent(Snake &snake, Fruit &fruit, int iTime,int SIndex)
{
	bool bCheck = false;
	PaintWall();
	InitSnake(snake);
	InitFruit(fruit);
	while (1)
	{
		OnDisplay(snake, fruit);
		ControlSnake(snake, fruit);
		CheckSnake_Fruit(snake, fruit, iTime);
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

void CheckSnake_Fruit(Snake& snake, Fruit& fruit, int& time)
{
	if ((snake.LN[0].x == fruit.location.x) && (snake.LN[0].y == fruit.location.y)) {
		snake.iN++;
		ControlSnake(snake, fruit);
		InitFruit(fruit);
		time -= 3;
	}
}

bool BCheckGameOver(Snake& snake, Fruit& fruit)
{
	if ((snake.LN[0].x < 6 || snake.LN[0].x >= WIDTH) || (snake.LN[0].y < 6 || snake.LN[0].y >= HEIGHT))
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
					deleteRow(7, 10);
					RunEvent(snake, fruit, iTime, SSelectLocation);
				}
				else if (SSelectLocation == 2)
				{
					SPages = 2;
					deleteRow(11, 6);
					paintLevelMenu(0);
				}
				else if (SSelectLocation == 3)
				{

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
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation);
				}
				else if (SSelectLocation == 1)
				{
					iTime = 95;
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation);
				}
				else if (SSelectLocation == 2)
				{
					iTime = 75;
					SPages = 3;
					deleteRow(5, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation);
				}
				else if (SSelectLocation == 3)
				{
					SPages = 1;
					deleteRow(11, 6);
					paintMenuMain(0);
				}
				break;
			case 4://Trang thua
				if (SSelectLocation == 1)
				{
					SPages = 1;
					deleteRow(4,HEIGHT);
					paintMenuMain(0);
				}
				else if (SSelectLocation == 0)
				{
					SPages = 4;
					deleteRow(4, HEIGHT);
					RunEvent(snake, fruit, iTime, SSelectLocation);
				}
				break;
			}
			break;
		}
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

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD[DWNumberOfEvents]; // Con tro EventBuffer.
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); // Dat cac su kien duoc luu tru vao con EventBuffer.

			// Chay vong lap de doc su kien.
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREventBuffer[i].EventType == KEY_EVENT) // Neu la su kien phim.
				{
					keyboardProcessing(IREventBuffer[i].Event.KeyEvent);
				}
				//else if (IREventBuffer[i].EventType == MOUSE_EVENT) // Su kien chuot.
			}
		}
	}
}

void TitleMenuMain() {
	LPSTR StrTitle = (char*)"WELLCOME TO SNAKE";
	setBackgroundColorTextXY((WIDTH - 5) / 2 - 2, (HEIGHT - 5) / 2 - 5, Pink,0, StrTitle,"",0);
	StrTitle = (char*)"What Do You Want To Choose?";
	setBackgroundColorTextXY((WIDTH - 5) / 2 - 7, (HEIGHT - 5) / 2 - 4, Green, 0, StrTitle, "", 0);
}

void paintMenuMain(short SIndex)
{ 
	 SSelectLocation = SIndex;
	 STotalCatalog = 4;
	 TitleMenuMain();

	//Ve Menu
	 short SW = ((WIDTH - 5) / 2) + 2;
	 short SH = ((HEIGHT - 5) / 2);
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
	setBackgroundColorTextXY(((WIDTH - 5) / 2) - 2, ((HEIGHT - 5) / 2) - 1, Blue,0, StrTitleLevel,"",0);

	short SW = ((WIDTH - 5) / 2) + 1;
	short SH = ((HEIGHT - 5) / 2) + 1;
	LPSTR StrTitle = (char*)"  EASY  ";
	setBackgroundColorTextXY(SW + 1, SH, White, ((SIndex == 0) ? Red : 0), StrTitle, StrIcon, ((SIndex == 0) ? Pink : 0));
	StrTitle = (char*)"  MEDIUM  ";
	setBackgroundColorTextXY(SW, SH + 1, White, ((SIndex == 1) ? Red : 0), StrTitle, StrIcon, ((SIndex == 1) ? Pink : 0));
	StrTitle = (char*)" DIFICULT  ";
	setBackgroundColorTextXY(SW, SH + 2, White, ((SIndex == 2) ? Red : 0), StrTitle, StrIcon, ((SIndex == 2) ? Pink : 0));
	StrTitle = (char*)"  EXIT  ";
	setBackgroundColorTextXY(SW + 1, SH + 3, White, ((SIndex == 3) ? Red : 0), StrTitle, StrIcon, ((SIndex == 3) ? Pink : 0));
}


