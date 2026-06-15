#include "Ground.h"

Ground::Ground(int InX, int InY)
{
	ID = ActorType::Ground;
	Icon = "  ";
	Pos = Vector2D(InX, InY);
}

Ground::~Ground()
{

}
