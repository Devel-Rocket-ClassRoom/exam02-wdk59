#pragma once
#include "MovableActor.h"
#include "IHaveColor.h"

class Box : public MovableActor, public IHaveColor
{
public :
	Box(int InX = 0, int InY = 0);
	virtual ~Box();

private :
	Actor* OriginalActor = nullptr;

	const ConsoleManager::ColorType ICON_COLOR = ConsoleManager::ColorType::DARK_YELLOW;
	
public :
	virtual inline ConsoleManager::ColorType GetColor() const override { return ICON_COLOR; };
	
	virtual inline void SetOriginalActor(Actor* InActor) { OriginalActor = InActor; };
	virtual inline Actor* GetOriginalActor() const { return OriginalActor; };

};
