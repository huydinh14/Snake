#include "main.hpp"
#include "function.hpp"
#include "console.hpp"

//Trang, Vi Tri, Tong muc
short sPages, sSelectLocation, sTotalCatalog;

int main()
{
	try
	{
		ConsoleResize(123, 40);
		DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_MAXIMIZE, MF_BYCOMMAND);
		SetConsoleTitle(TEXT("Snake Game - Huy Dinh SE"));
		ShowCur(false);
		sPages = 1;
		EventProcessing();
	}
	catch (const std::exception&)
	{
		std::cout << "Error.\n";
	}
	return 0;
}