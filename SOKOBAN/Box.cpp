#include "Box.h"
#include "Ground.h"

Box::Box(int InX, int InY)
{
	ID = ActorType::Box;
	Icon = "██";
	Pos = Vector2D(InX, InY);
	OriginalActor = new Ground(InX, InY);
}

Box::~Box()
{
	if (OriginalActor)
	{
		delete OriginalActor;
		OriginalActor = nullptr;
	}
}
