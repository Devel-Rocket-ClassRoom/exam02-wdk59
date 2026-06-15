#pragma once
#include "ConsoleManager.h"

class IHaveColor
{
public :
	virtual inline ConsoleManager::ColorType GetColor() const = 0;
};
