#pragma once
#include "Actor.h"
#include "IMovable.h"

class MovableActor : public Actor, public IMovable
{
protected :


public :
	MovableActor(int InX = 0, int InY = 0);
	virtual ~MovableActor();

	// Player.h의 Move 없애면 virtual 빼는 게 좋을지도??
	virtual inline void Move(Vector2D InDir) override { Pos += InDir; };
	virtual inline Vector2D GetForwardCoordinate(Vector2D InDir) const override { return Pos + InDir; };
};
