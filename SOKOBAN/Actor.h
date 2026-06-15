#pragma once
#include <string>
#include "ActorType.h"
#include "Vector2D.h"

class Actor
{
public:
	Actor(int InX = 0, int InY = 0);
	virtual ~Actor();

protected :
	ActorType ID = ActorType::DefaultActor;	// 액터 종류
	std::string Icon = "  ";	// default: 2byte
	Vector2D Pos;

public :
	inline ActorType GetID() const { return ID; };
	inline std::string GetIcon() const { return Icon; };
	inline Vector2D GetPos() const { return Pos; };
};
