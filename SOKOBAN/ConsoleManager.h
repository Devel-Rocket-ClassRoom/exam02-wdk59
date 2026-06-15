#pragma once
#include <string>

class ConsoleManager
{
/* Manager라서 함수랑 변수 전부 static으로 관리 */
public :
	enum class ColorType : int
	{
		BLACK,
		DARK_BLUE,
		DARK_GREEN,
		DARK_SKYBLUE,
		DARK_RED,
		DARK_PURPLE,
		DARK_YELLOW,
		GRAY,
		DARK_GRAY,
		BLUE,
		GREEN,
		SKYBLUE,
		RED,
		PURPLE,
		YELLOW,
		WHITE,
		NUM_OF_COLORS
	};

private :
	static constexpr int ScreenWidth = 50;
	static constexpr int ScreenHeight = 75;

public :

	void SetConsole();
	void SetFontColor(ColorType InColor);
};
