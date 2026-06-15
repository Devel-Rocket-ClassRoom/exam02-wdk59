#include "InputManager.h"
#include <Windows.h>
#include <conio.h>

InputManager::InputManager()
{
	InputKey = 0;
	
	KeyMap[VK_UP] = InputAction::Up;
	KeyMap[VK_DOWN] = InputAction::Down;
	KeyMap[VK_LEFT] = InputAction::Left;
	KeyMap[VK_RIGHT] = InputAction::Right;
	KeyMap['R'] = InputAction::Restart;
	KeyMap[VK_ESCAPE] = InputAction::Quit;
	KeyMap['N'] = InputAction::Next;
}

InputManager::~InputManager()
{

}

InputAction InputManager::GetInput()
{
	InputAction CurrentInput = InputAction::None;

	for (const std::pair<int, InputAction>& p : KeyMap)
	{
		if (GetAsyncKeyState(p.first) & TOGGLED)
		{
			CurrentInput = p.second;
		}
	}

	return CurrentInput;
}
