#include "Actor.h"

Actor::Actor(int InX, int InY)
{
	Pos = Vector2D(0, 0);
	Icon = "  ";
	Pos = Vector2D(InX, InY);
}

Actor::~Actor()
{

}
