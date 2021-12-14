#include "LevelOne.h"
#include "../CSC8503Common/PositionConstraint.h"

LevelOne::LevelOne() : TutorialGame() {
	InitCamera();
	InitWorld();
}

void LevelOne::InitWorld() {
	world->ClearAndErase();
	physics->Clear();

	AddPlayerToWorld(Vector3(0, 25, 0));

	AddCubeToWorld(Vector3(0, 10, 0), Vector3(5, 10, 5), 0.0f);
	// See saw
	GameObject* seesaw = AddCubeToWorld(Vector3(10, 10, 0), Vector3(10, 5, 2.5), 0.0f);
	//PositionConstraint* constraint = new PositionConstraint(seesaw, block, maxDistance);
	//world->AddConstraint(constraint);

	AddCubeToWorld(Vector3(25, 10, 0), Vector3(5, 5, 5), 0.0f);


	AddBonusToWorld(Vector3(10, 5, 0));

	InitDefaultFloor();
}
