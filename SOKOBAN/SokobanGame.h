#pragma once
#include "Player.h"
#include "LevelManager.h"

class SokobanGame
{
public:
	SokobanGame();
	virtual ~SokobanGame();

private :
	bool bIsRunning = false;
	Player* PlayerCharacter = nullptr;

	int LeftHouse = 0;
	int Moving = 0;

	LevelManager LM;

public :
	void GameRun();
	void GameReady();
	void GamePlay();
	void PrintScreen();

	bool CheckForwardBox(Box* InBox, Vector2D InDir);

	void FinishStage();
	
	void PrintSuccess();

	void Restart();
	void QuitGame();
};
