#include "main.h"
#include "Function.h"
#include "Console.h"

//Trang,Vị Trí, Tổng mục
short SPages, SSelectLocation, STotalCatalog;

int main(){
	try
	{
		SetConsoleTitle(TEXT("Snake Game - Huy Dinh SE"));
		ShowCur(false);
		paintMenuMain(1);
		SPages = 1;
		eventProcessing();
	}
	catch (const std::exception&)
	{

	}
	return 0;
}