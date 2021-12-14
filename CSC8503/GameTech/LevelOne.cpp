#include "LevelOne.h"
#include "../CSC8503Common/HingeConstraint.h"
#include "../CSC8503Common/OBBVolume.h"
using namespace NCL;
using namespace CSC8503;

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
	GameObject* seesaw = AddSeesawToWorld(Vector3(10, 10, 0), Vector3(10, 2.5, 2.5), 0.0f);
	//GameObject* hinge = AddCubeToWorld(Vector3(10, 10, 1), Vector3(1, 1, 1), 0.0f);
	//HingeConstraint* constraint = new HingeConstraint(seesaw, hinge, 0);
	//world->AddConstraint(constraint);

	AddCubeToWorld(Vector3(25, 10, 0), Vector3(5, 5, 5), 0.0f);


	AddBonusToWorld(Vector3(10, 5, 0));

	InitDefaultFloor();
}

void LevelOne::ResetGame() {
	player->GetTransform()
		.SetPosition(Vector3(0, 25, 0));
}

GameObject* LevelOne::AddSeesawToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject();

	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	return cube;
}
