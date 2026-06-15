#pragma once
#include "Actor.h"
#include "IHaveColor.h"

class Wall : public Actor, public IHaveColor
{
public :
	Wall(int InX = 0, int InY = 0);
	virtual ~Wall();

private :
	const ConsoleManager::ColorType IconColor = ConsoleManager::ColorType::GRAY;

public :
	inline std::string GetIcon() const { return Icon; };
	virtual inline ConsoleManager::ColorType GetColor() const override { return IconColor; };

};
