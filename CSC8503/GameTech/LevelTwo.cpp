#include "LevelTwo.h"
#include "../CSC8503Common/NavigationGrid.h"

LevelTwo::LevelTwo() : TutorialGame() {
	InitialiseAssets();
}

void LevelTwo::InitWorld() {
	world->ClearAndErase();
	physics->Clear();

	if (grid == nullptr) {
		grid = new NavigationGrid("TestGrid2.txt");
	}

	BridgeConstraintTest();
	InitMixedGridWorld(5, 5, 3.5f, 3.5f);

	AddPlayerToWorld(Vector3(80, 0, 10));
	AddEnemyToWorld(Vector3(80, 0, 80));

	InitDefaultFloor();
}
