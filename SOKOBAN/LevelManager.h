#pragma once
#include <vector>
#include <string>
#include "ConsoleManager.h"
#include "Map.h"
#include "Actor.h"
#include "Player.h"

class LevelManager
{
public:
	LevelManager();
	virtual ~LevelManager();

private :
	const std::string MapDataFolderPath = "./MapData";
	const ConsoleManager::ColorType DefaultColor = ConsoleManager::ColorType::WHITE;

	const int NUM_OF_PRESET_MAPS = 5;
	std::vector<Map*> PresetMaps;	// 미리 만들어둔 맵들

	unsigned int Stage = 0;			// 현재 스테이지
	int HouseCount = 0;

	Actor** Level = nullptr;			// 맵 정보대로 액터를 배치할 공간
	Vector2D LevelSize = { 0, 0 };

	Player* PlayerCharacter = nullptr;

public :
	Player* CreateLevel();

	Player* NextLevel();

	void Clean();

	inline int GetStageNumber() const { return Stage + 1; };
	inline int GetFinalStageNumber() const { return NUM_OF_PRESET_MAPS; };
	inline Vector2D GetLevelSize() const { return LevelSize; };
	inline ConsoleManager::ColorType GetDefaultColor() const { return DefaultColor; };
	inline int GetHouseCount() const { return HouseCount; };
	inline void SetCell(Vector2D InPos, Actor* InActor) { Level[InPos.Y * LevelSize.X + InPos.X] = InActor; };
	inline Actor* GetCell(Vector2D InPos) const { return Level[InPos.Y * LevelSize.X + InPos.X]; };
};
