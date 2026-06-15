#pragma once
#include "Vector2D.h"

class IMovable
{
public :
	virtual void Move(Vector2D InDir) = 0;
	virtual Vector2D GetForwardCoordinate(Vector2D InDir) const = 0;
};
