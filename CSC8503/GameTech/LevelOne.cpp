#include "LevelOne.h"

LevelOne::LevelOne() : TutorialGame() {
	InitCamera();
	InitWorld();
}

void LevelOne::InitWorld() {
	world->ClearAndErase();
	physics->Clear();

	BridgeConstraintTest();
	InitMixedGridWorld(5, 5, 3.5f, 3.5f);

	AddPlayerToWorld(Vector3(5, 5, 0));
	AddBonusToWorld(Vector3(10, 5, 0));

	InitDefaultFloor();
}
