#pragma once
#include "Actor.h"
#include "IHaveColor.h"
#include "Box.h"

class House : public Actor, public IHaveColor
{
public :
	House(int InX = 0, int InY = 0);
	virtual ~House();

private :
	Box* CurrentBox = nullptr;
	const std::string TileIcons[2] = {"░░", "▓▓"};

	// 빈 집: 빨강, 상자 들어간 집: 초록
	const ConsoleManager::ColorType IconColors[2] = { ConsoleManager::ColorType::RED, ConsoleManager::ColorType::GREEN };
	ConsoleManager::ColorType IconColor = ConsoleManager::ColorType::DARK_YELLOW;

public :
	void UpdateState(Box* InBox = nullptr);
	
	virtual inline ConsoleManager::ColorType GetColor() const override { return IconColor; };
	inline Box* GetCurrentBox() const { return CurrentBox; };
};
