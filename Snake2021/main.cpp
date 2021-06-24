#include "main.hpp"
#include "Function.hpp"
#include "Console.hpp"

//Trang,Vị Trí, Tổng mục
short sPages, sSelectLocation, sTotalCatalog;

int main(){
	try
	{
		ConsoleResize(123,35);
		SetConsoleTitle(TEXT("Snake Game - Huy Dinh SE"));
		ShowCur(false);
		PaintMenuMain(1);
		sPages = 1;
		EventProcessing();
	}
	catch (const std::exception&)
	{

	}
	return 0;
}