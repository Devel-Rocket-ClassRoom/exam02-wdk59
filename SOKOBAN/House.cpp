#include "House.h"

House::House(int InX, int InY)
{
	ID = ActorType::House;
	Icon = TileIcons[0];	// 2가지 타입 중 현재 사용 중인 아이콘 저장
	Pos = Vector2D(InX, InY);

	IconColor = IconColors[0];

	CurrentBox = nullptr;
}

House::~House()
{

}

void House::UpdateState(Box* InBox)
{
	CurrentBox = InBox;
	Icon = TileIcons[InBox != nullptr];	// 빈 집: 0(false), 상자 들어간 집: 1(true)
	IconColor = IconColors[InBox != nullptr];		// 빈 집(빨강): 0(false), 상자 들어간 집(초록): 1(true)
}
