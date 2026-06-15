#include "Player.h"
#include "Ground.h"

Player::Player(int InX, int InY)
{
	ID = ActorType::Player;
	Icon = DirectionIcons[0];   // 오른쪽, 왼쪽 따라 2가지 아이콘 중 현재 아이콘
	Pos = Vector2D(InX, InY);

	CurrentBox = nullptr;
}

Player::~Player()
{

}

// 필요 없을수도??
void Player::Move(Vector2D InDir)
{
	Pos += InDir;
}

// 필요 없을수도??
void Player::PushBox(Vector2D InDir)
{
	if (CurrentBox != nullptr)
	{
		CurrentBox->Move(InDir);
	}
}
