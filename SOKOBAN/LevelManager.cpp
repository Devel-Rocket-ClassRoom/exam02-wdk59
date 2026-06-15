#include "LevelManager.h"
#include <iostream>
#include "Ground.h"
#include "Box.h"
#include "House.h"
#include "Wall.h"

LevelManager::LevelManager()
{
	HouseCount = 0;

	Level = nullptr;
	LevelSize = { 0, 0 };

	for (int i = 0; i < NUM_OF_PRESET_MAPS; ++i)
	{
		PresetMaps.push_back(new Map(MapDataFolderPath + "/" + std::to_string(i) + ".txt"));
		printf("%d %d\n", PresetMaps[i]->GetMapSize().X, PresetMaps[i]->GetMapSize().Y);
	}

	PlayerCharacter = nullptr;
}

LevelManager::~LevelManager()
{
	Clean();
}

Player* LevelManager::CreateLevel()
{
	HouseCount = 0;
	Level = nullptr;
	LevelSize = { 0, 0 };
	PlayerCharacter = nullptr;

	LevelSize = PresetMaps[Stage]->GetMapSize();
	int* WorldInfo = PresetMaps[Stage]->GetMapInfo();
	Level = new Actor * [LevelSize.X * LevelSize.Y]();

	for (int y = 0; y < LevelSize.Y; ++y)
	{
		for (int x = 0; x < LevelSize.X; ++x)
		{
			switch (static_cast<ActorType>(WorldInfo[y * LevelSize.X + x]))
			{
			case ActorType::DefaultActor:
				Level[y * LevelSize.X + x] = new Actor(x, y);
				break;

			case ActorType::Ground:
				Level[y * LevelSize.X + x] = new Ground(x, y);
				break;

			case ActorType::Player:
				PlayerCharacter = new Player(x, y);
				Level[y * LevelSize.X + x] = new Ground(x, y);
				break;

			case ActorType::Box:
				Level[y * LevelSize.X + x] = new Box(x, y);
				break;

			case ActorType::House:
				Level[y * LevelSize.X + x] = new House(x, y);
				HouseCount++;
				break;

			case ActorType::Wall:
				Level[y * LevelSize.X + x] = new Wall(x, y);
				break;

			default:
				printf("Error: 레벨 생성 오류\n알 수 없는 액터입니다.\n");
				break;
			}
		}
	}

	if (!PlayerCharacter)
	{
		printf("Error: 맵에서 플레이어를 찾을 수 없습니다.\n");
	}
	
	return PlayerCharacter;
}

Player* LevelManager::NextLevel()
{
	++Stage;
	return CreateLevel();
}

void LevelManager::Clean()
{
	for (int i = 0; i < NUM_OF_PRESET_MAPS; ++i)
	{
		if (PresetMaps[i])
		{
			delete PresetMaps[i];
			PresetMaps[i] = nullptr;
		}
	}

	if (Level)
	{
		for (int i = 0; i < LevelSize.X * LevelSize.Y; ++i)
		{
			if (Level[i])
			{
				delete Level[i];
				Level[i] = nullptr;
			}
		}

		delete[] Level;
		Level = nullptr;
	}
}
