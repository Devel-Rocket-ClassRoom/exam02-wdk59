#pragma once
#include <unordered_map>
#include "InputAction.h"

class InputManager
{
public :
	InputManager();
	virtual ~InputManager();

private :
	static constexpr short TOGGLED = 0x0001;

	int InputKey = 0;
	std::unordered_map<int, InputAction> KeyMap;

public :
	InputAction GetInput();

};
