#include "Map.h"
#include <fstream>
#include <iterator>

Map::Map(const std::string InPath)
{
	std::string MapDataString = ReadFile(InPath);
	ParseMap(MapDataString);
}

Map::~Map()
{
	Clean();
}

std::string Map::ReadFile(const std::string InPath)
{
	std::string MapDataString = "";

	std::ifstream MapFile(InPath);
	if (MapFile.is_open())
	{
		std::string FileTexts {
			std::istreambuf_iterator<char>(MapFile),
			std::istreambuf_iterator<char>()
		};

		MapFile.close();
		MapDataString = FileTexts;
		
	}
	else
	{
		printf("맵 파일 열기 실패\n");
		printf("파일 경로: %s\n", InPath.c_str());
	}

	return MapDataString;
}

bool Map::ParseMap(const std::string MapDataString)
{
	/* 맵 크기 알아내기 */
	
	// 맨 처음 한 줄 찾기: 첫번째 개행 문자 위치 찾기
	size_t MapSizeLinePosition = MapDataString.find('\n');
	if (MapSizeLinePosition == std::string::npos)
	{
		printf("Error: 맵 크기 읽기 오류\n잘못된 파일 형식입니다. 개행 문자를 찾을 수 없습니다.\n");
		return false;
	}
	// 첫 줄(맵 크기) 읽기
	std::string MapSizeLine = MapDataString.substr(0, MapSizeLinePosition);
	
	// 가로, 세로 크기 찾기
	size_t MapSizeCommaPosition = MapSizeLine.find(',');
	if (MapSizeCommaPosition == std::string::npos)
	{
		printf("Error: 맵 크기 읽기 오류\n잘못된 파일 형식입니다. 콤마(,)를 찾을 수 없습니다.\n");
		return false;
	}
	// 가로, 세로 크기 저장
	Width = std::stoi(MapSizeLine.substr(0, MapSizeCommaPosition));
	Height = std::stoi(MapSizeLine.substr(MapSizeCommaPosition + 1));

	/* 맵 정보 가공: 파일에서 읽어와서 int형으로 저장하기 */

	// 맵 정보 저장할 배열 동적 할당
	MapInfo = new int[Width * Height];

	// 맵 데이터 파싱 시작 지점 설정
	size_t CurrentPosition = MapSizeLinePosition + 1;	// 맵 크기 다음 줄 위치
	unsigned int X = 0;
	unsigned int Y = 0;

	// 맵 데이터 파싱: CurrentPosition부터 탐색 시작
	size_t MapCommaPosition = 0;
	size_t MapLinePosition = 0;
	size_t TokenEndPosition = std::string::npos;
	bool bIsLineEnd = false;
	int MapIndex = 0;
	while (CurrentPosition < MapDataString.length() && Y < Height)
	{
		MapCommaPosition = MapDataString.find(',', CurrentPosition);
		MapLinePosition = MapDataString.find('\n', CurrentPosition);
		TokenEndPosition = std::string::npos;
		bIsLineEnd = false;

		// 한 줄의 마지막 숫자인지 확인
		if (MapCommaPosition < MapLinePosition)
		{
			TokenEndPosition = MapCommaPosition;
		}
		else
		{
			TokenEndPosition = MapLinePosition;
			bIsLineEnd = true;
		}

		// 파일의 마지막 문자 읽고 있을 때
		if (TokenEndPosition == std::string::npos)
		{
			TokenEndPosition = MapDataString.length();
			bIsLineEnd = true;
		}

		// 값 추출: 현재 커서 위치부터 콤마가 나오는 위치까지 하나의 값으로 처리
		std::string ValueString = MapDataString.substr(CurrentPosition, TokenEndPosition - CurrentPosition);
		if (!ValueString.empty())
		{
			MapIndex = X + Y * Width;
			*(MapInfo + MapIndex) = std::stoi(ValueString);
			X++;
		}
		else
		{
			printf("Error: 맵 정보 읽기 오류\n잘못된 파일 형식입니다. 유효한 맵 정보 값이 아닙니다.\n");
		}

		CurrentPosition = TokenEndPosition + 1;	// 커서 이동

		// 한 줄 끝나면 다음 행으로 인덱스 이동
		if (bIsLineEnd)
		{
			Y++;
			X = 0;
		}
	}

	return MapInfo != nullptr;
}

void Map::Clean()
{
	if (MapInfo)
	{
		delete[] MapInfo;
		MapInfo = nullptr;
	}
}
