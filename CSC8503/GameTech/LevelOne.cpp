#include "LevelOne.h"

LevelOne::LevelOne() : TutorialGame() {
	InitialiseAssets();
}

void LevelOne::InitWorld() {
	world->ClearAndErase();
	physics->Clear();

	BridgeConstraintTest();
	InitMixedGridWorld(5, 5, 3.5f, 3.5f);

	AddBonusToWorld(Vector3(10, 5, 0));

	InitDefaultFloor();
}
