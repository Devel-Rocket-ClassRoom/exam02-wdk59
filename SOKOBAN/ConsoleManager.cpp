#include "ConsoleManager.h"
#include <Windows.h>

void ConsoleManager::SetConsole()
{
	SetConsoleTitle(TEXT("SOKOBAN"));
	std::string Command = "mode con:cols=" + std::to_string(ScreenWidth) + " lines=" + std::to_string(ScreenHeight);
	system(Command.c_str());
	SetFontColor(ColorType::WHITE);
}

void ConsoleManager::SetFontColor(ColorType InColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)InColor);
}
