#pragma once
#include "Actor.h"
#include "ActorType.h"

class Ground : public Actor
{
public:
	Ground(int InX = 0, int InY = 0);
	virtual ~Ground();
};

