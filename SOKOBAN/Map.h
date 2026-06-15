#pragma once
// 맵: .txt로 저장
// - 파싱해와서 저장
// - 첫째 줄: 맵의 가로, 세로 크기
// - 둘째줄~끝줄: 맵 정보
//	 ㄴ 배치 정보는 액터의 ID로 표현
//		ActorType
//		  0: DefaultActor,
//		  1: Player,
//		  2: Ground,
//		  3: Box,
//		  4: House,
//		  5: Wall,
//		  6: NUM_OF_ACTOR_TYPE

#include <string>
#include "Vector2D.h"

class Map
{
public :
	Map(std::string InPath);
	virtual ~Map();

private :
	std::string Path = "";
	unsigned int Width = 0;
	unsigned int Height = 0;
	int* MapInfo = nullptr;
	
	// 맵 정보가 저장된 파일 읽기
	std::string ReadFile(const std::string InPath);
	// 파싱 성공 여부 반환
	bool ParseMap(const std::string MapDataString);

public :
	inline int* GetMapInfo() const { return MapInfo; };
	inline Vector2D GetMapSize() const { return Vector2D(Width, Height); };

	void Clean();
};
