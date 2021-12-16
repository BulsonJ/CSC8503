#include "LevelTwo.h"
#include "../CSC8503Common/NavigationGrid.h"
#include "../CSC8503Common/FinishObject.h"
#include "../CSC8503Common/ResetObject.h"
using namespace NCL;
using namespace CSC8503;

LevelTwo::LevelTwo() : TutorialGame() {
	InitCamera();
	InitWorld();
}

void LevelTwo::InitWorld() {
	world->ClearAndErase();
	physics->Clear();

	if (grid == nullptr) {
		grid = new NavigationGrid("TestGrid1.txt");
	}

	int** gridSquare = grid->GetGrid();
	int size = grid->GetSize();
	for (int y = 0; y < grid->GetHeight(); y++) {
		for (int x = 0; x < grid->GetWidth(); x++) {
			if (gridSquare[y][x] == 120) {
				AddCubeToWorld(Vector3(x * size, 5, y * size), Vector3(size / 2, size / 2, size / 2), 0.0f);
			}
		}
	}

	AddPlayerToWorld(Vector3(80, 5, 10));
	AddEnemyToWorld(Vector3(80, 5, 80));

	InitDefaultFloor();
}

void LevelTwo::WinScreen() {
	Debug::Print("You Won!", Vector2(40, 40));
	Debug::Print("Time:" + std::to_string(elapsedTime), Vector2(40, 45));
	Debug::Print("Score:" + std::to_string(score), Vector2(40, 50));

	if (transitionTimer > transitionTimerMax) {
		FinishGame();
		finishObject->SetFinish(false);
		startTransition = false;
		finishTransition = false;
		transitionTimer = 0;
	}
}

void LevelTwo::LoseScreen() {
	Debug::Print("You Lost!", Vector2(40, 40));
	Debug::Print("Time:" + std::to_string(elapsedTime), Vector2(40, 45));
	Debug::Print("Score:" + std::to_string(score), Vector2(40, 50));

	if (transitionTimer > transitionTimerMax) {
		ResetGame();
		resetObject->SetResetGame(false);
		startTransition = false;
		resetTransition = false;
		transitionTimer = 0;
	}
}

void LevelTwo::ResetGame() {
	transitionTimer = true;

	InitWorld();
	InitCamera();
	elapsedTime = 0;
	score = 0;
}


void LevelTwo::FinishGame() {
	gameEnded = true;
}