#include "SokobanGame.h"
#include <iostream>
#include "InputManager.h"
#include "InputAction.h"
#include "House.h"


SokobanGame::SokobanGame()
{
	bIsRunning = false;
	PlayerCharacter = nullptr;
	LeftHouse = 0;
}

SokobanGame::~SokobanGame()
{

}

void SokobanGame::GameRun()
{
	GameReady();
	GamePlay();
	
}

void SokobanGame::GameReady()
{
	bIsRunning = true;
	Moving = 0;
	PlayerCharacter = nullptr;
}

void SokobanGame::GamePlay()
{
	PlayerCharacter = LM.CreateLevel();
	LeftHouse = LM.GetHouseCount();

	InputManager IM;
	InputAction CurrentAction = InputAction::None;
	bool bCanMove = false;
	Vector2D ForwardVector = Vector2D::Default;
	while (bIsRunning)
	{
		PrintScreen();

		PlayerCharacter->SetCurrentBox(nullptr);

		CurrentAction = InputAction::None;
		bCanMove = false;
		ForwardVector = Vector2D::Default;
		// 유효한 입력 들어올 때까지 입력 받기
		while (CurrentAction == InputAction::None || CurrentAction == InputAction::Next)
		{
			CurrentAction = IM.GetInput();
		}
		switch (CurrentAction)
		{
		case InputAction::Up :
			ForwardVector = Vector2D::Up;
			break;

		case InputAction::Down :
			ForwardVector = Vector2D::Down;
			break;

		case InputAction::Left :
			ForwardVector = Vector2D::Left;
			PlayerCharacter->Flip(false);	// facing Left
			break;

		case InputAction::Right :
			ForwardVector = Vector2D::Right;
			PlayerCharacter->Flip(true);	// facing Right
			break;

		case InputAction::Quit:
			printf("Quit Game\n");	// debug
			QuitGame();
			break;

		case InputAction::Restart:
			printf("Restart\n");	// debug
			Restart();
			break;

		default :
			printf("Error: 입력 오류\n알 수 없는 입력입니다.\n");
			break;
		}
		
		// 앞에 뭔지 체크
		Actor* ForwardActor = LM.GetCell(PlayerCharacter->GetForwardCoordinate(ForwardVector));
		if (ForwardVector != Vector2D::Default)
		{
			if (!ForwardActor)
			{
				printf("Error: 게임 진행 불가\n진행 방향에 유효한 액터가 없습니다.\n");
				printf("게임을 강제로 종료합니다.\n");
				QuitGame();	// test
				break;
			}
			
			// 앞에 벽인 경우 입력 무시
			if (ForwardActor->GetID() == ActorType::Wall)
			{
				continue;
			}

			switch (ForwardActor->GetID())
			{
			case ActorType::Ground :
				bCanMove = true;
				break;

			case ActorType::Box:
				if (auto* ForwardBox = dynamic_cast<Box*>(ForwardActor))
				{
					bCanMove = CheckForwardBox(ForwardBox, ForwardVector);
				}
				else
				{
					printf("Error: 잘못된 액터 ID\n");
				}
				break;

			case ActorType::House:
				if (auto* ForwardHouse = dynamic_cast<House*>(ForwardActor))
				{
					if (Box* ForwardBox = ForwardHouse->GetCurrentBox())
					{
						bCanMove = CheckForwardBox(ForwardBox, ForwardVector);
					}
					else
					{
						bCanMove = true;
					}
				}
				break;

			default :
				printf("Error: 게임 진행 불가\n진행 방향의 액터를 알 수 없습니다.\n");
				printf("게임을 강제로 종료합니다.\n");
				QuitGame();
				break;
			}
		}

		// 이동 가능: 이동
		if (bCanMove)
		{
			printf("Move %d %d\n", ForwardVector.X, ForwardVector.Y);

			// 앞 칸이 집일 때: 채워진 집인지 확인 -> 채워진 집이면 상자 챙기기
			if (House* NowHouse = dynamic_cast<House*>(LM.GetCell(ForwardActor->GetPos())))
			{
				if (NowHouse->GetID() == ActorType::House)
				{
					PlayerCharacter->SetCurrentBox(NowHouse->GetCurrentBox());
				}
			}

			// 플레이어가 상자 들고 있을 때: 상자도 움직이기
			Box* CurrentBox = PlayerCharacter->GetCurrentBox();
			if (CurrentBox)
			{
				// 집에서 나갈 때
				if (CurrentBox->GetOriginalActor()->GetID() == ActorType::House)
				{
					if (auto* NowHouse = dynamic_cast<House*>(CurrentBox->GetOriginalActor()))
					{
						NowHouse->UpdateState();
						LeftHouse++;
					}
				}
				// 집 들어갈 때
				if (LM.GetCell(CurrentBox->GetForwardCoordinate(ForwardVector))->GetID() == ActorType::House)
				{
					if (auto* ForwardHouse = dynamic_cast<House*>(LM.GetCell(CurrentBox->GetForwardCoordinate(ForwardVector))))
					{
						ForwardHouse->UpdateState(CurrentBox);
						LeftHouse--;
					}
				}

				// 상자 옮기기
				LM.SetCell(CurrentBox->GetPos(), CurrentBox->GetOriginalActor());
				CurrentBox->SetOriginalActor(LM.GetCell(CurrentBox->GetForwardCoordinate(ForwardVector)));
				CurrentBox->Move(ForwardVector);
				// 상자 옮긴 곳이 집이면 상자가 아니라 집이 보이게
				if (LM.GetCell(CurrentBox->GetPos())->GetID() != ActorType::House)
				{
					LM.SetCell(CurrentBox->GetPos(), CurrentBox);
				}
			}
			// 플레이어 이동
			PlayerCharacter->Move(ForwardVector);
			Moving++;
		}

		if (LeftHouse <= 0)
		{
			PrintScreen();
			PrintSuccess();
			FinishStage();
		}
	}
}

void SokobanGame::PrintScreen()
{
	system("cls");

	printf("┌──────────────────────────────────────────┐\n");
	printf("│              ＳＯＫＯＢＡＮ              │\n");
	printf("├──────────────────────────────────────────┤\n");
	printf("│Stage: %2d  │  Moving: %3d  │  Box: %2d / %2d│\n", LM.GetStageNumber(), Moving, LM.GetHouseCount() - LeftHouse, LM.GetHouseCount());
	printf("├──────────────────────────────────────────┤\n");
	printf("│                                          │\n");

	const int SCREEN_WIDTH = 19;
	const int SCREEN_HEIGHT = 16;

	const int MAP_WIDTH = LM.GetLevelSize().X;
	const int MAP_HEIGHT = LM.GetLevelSize().Y;

	const int START_X = (SCREEN_WIDTH - MAP_WIDTH) / 2;
	const int START_Y = (SCREEN_HEIGHT - MAP_HEIGHT) / 2;

	const int END_X = START_X + MAP_WIDTH;
	const int END_Y = START_Y + MAP_HEIGHT;

	for (int y = 0; y < SCREEN_HEIGHT; ++y)
	{
		printf("|  ");

		for (int x = 0; x < SCREEN_WIDTH; ++x)
		{
			// 레벨 경계 검사
			bool bInsideMap = (x >= START_X && x < END_X) && (y >= START_Y && y < END_Y);

			if (!bInsideMap)
			{
				printf("  ");
				continue;
			}

			// 레벨 출력
			int MapX = x - START_X;
			int MapY = y - START_Y;

			if (MapX == PlayerCharacter->GetPos().X && MapY == PlayerCharacter->GetPos().Y)
			{
				printf("%s", PlayerCharacter->GetIcon().c_str());
				continue;
			}

			Actor* Cell = LM.GetCell(Vector2D(MapX, MapY));

			if (!Cell)
			{
				printf("  ");
				continue;
			}

			ConsoleManager CM;
			if (auto* ColorActor = dynamic_cast<IHaveColor*>(Cell))
			{
				CM.SetFontColor(ColorActor->GetColor());
			}
			printf("%s", Cell->GetIcon().c_str());
			if (auto* ColorActor = dynamic_cast<IHaveColor*>(Cell))
			{
				CM.SetFontColor(LM.GetDefaultColor());
			}
		}

		printf("  │\n");
	}

	printf("│                                          │\n");
	printf("├──────────────────────────────────────────┤\n");
	printf("│Move\t │ ↑ ↓ ← →                         │\n");
	printf("│Restart │ R                               │\n");
	printf("│Exit\t │ Esc                             │\n");
	printf("└──────────────────────────────────────────┘\n");
}

bool SokobanGame::CheckForwardBox(Box* InBox, Vector2D InDir)
{
	bool bCanMove = false;

	Actor* ForwardActor = LM.GetCell(InBox->GetForwardCoordinate(InDir));
	switch (ForwardActor->GetID())
	{
	case ActorType::Ground :
		bCanMove = true;
		break;

	case ActorType::House :
		if (auto* ForwardHouse = dynamic_cast<House*>(ForwardActor))
		{
			if (!ForwardHouse->GetCurrentBox())
			{
				bCanMove = true;
			}
		}
		break;

	default :
		break;
	}

	if (bCanMove)
	{
		PlayerCharacter->SetCurrentBox(InBox);
	}

	return bCanMove;
}

void SokobanGame::FinishStage()
{
	printf(".\n.\n.\n.\n.\n");

	if (LM.GetStageNumber() >= LM.GetFinalStageNumber())
	{
		printf("Congratulation!! You did it!!!!!\n");
		printf("It was the Final Stage.\n");
		printf("You have only two selection.\n");
		printf(".\n.\n.\n.\n.\n");
	}

	printf("Select the Next Action\n");
	printf("- Quit Game: Input Esc\n");
	printf("- Restart Stage: Input R\n");

	InputManager IM;
	InputAction CurrentAction = InputAction::None;
	// 유효한 입력 들어올 때까지 입력 받기
	bool bIsInSelection = false;
	if (LM.GetStageNumber() < LM.GetFinalStageNumber())
	{
		printf("- Next Stage: Input N\n");
		while (CurrentAction != InputAction::Restart && CurrentAction != InputAction::Next && CurrentAction != InputAction::Quit)
		{
			CurrentAction = IM.GetInput();
		}
	}
	else
	{
		while (CurrentAction != InputAction::Restart && CurrentAction != InputAction::Quit)
		{
			CurrentAction = IM.GetInput();
		}
	}
	
	switch (CurrentAction)
	{
	case InputAction::Restart:
		Restart();
		break;

	case InputAction::Next:
		Moving = 0;
		PlayerCharacter = LM.NextLevel();
		LeftHouse = LM.GetHouseCount();
		break;

	case InputAction::Quit:
		QuitGame();
		break;

	default:
		printf("Error: 입력 오류\n알 수 없는 입력입니다.\n");
		break;
	}
}

void SokobanGame::PrintSuccess()
{
	printf("Stage Clear!\n");
}

void SokobanGame::Restart()
{
	Moving = 0;
	PlayerCharacter = LM.CreateLevel();
	LeftHouse = LM.GetHouseCount();
}

void SokobanGame::QuitGame()
{
	bIsRunning = false;
}
