#include "Wall.h"

Wall::Wall(int InX, int InY)
{
	ID = ActorType::Wall;
	Icon = "██";
	Pos = Vector2D(InX, InY);
}

Wall::~Wall()
{
	
}
