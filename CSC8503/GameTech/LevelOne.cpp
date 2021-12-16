#include "LevelOne.h"
#include "../CSC8503Common/PositionConstraint.h"
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

	GameObject* hammer = AddHammerToWorld(Vector3(-7.5, 19.5, 0), Vector3(5, 1, 1), 1.0f);

	AddCubeToWorld(Vector3(0, 10, 0), Vector3(5, 10, 5), 0.0f);
	// See saw
	//GameObject* seesaw = AddSeesawToWorld(Vector3(12.5, 17.5, 0), Vector3(7.5, 2.5, 2.5), 5.0f);
	AddCubeToWorld(Vector3(25, 10, 0), Vector3(5, 10, 5), 0.0f);
	//GameObject* seesaw2 = AddSeesawToWorld(Vector3(25 + 12.5, 17.5, 0), Vector3(7.5, 2.5, 2.5), 5.0f);
	AddCubeToWorld(Vector3(50, 10, 0), Vector3(5, 10, 5), 0.0f);

	GameObject* ramp = AddOBBCubeToWorld(Vector3(50, 10, -10), Vector3(5, 10, 5), 0.0f);
	ramp->GetTransform().SetOrientation(
		ramp->GetTransform().GetOrientation() * Quaternion(Vector3(0,-1,-0.5), 0));

	AddCubeToWorld(Vector3(50, 5, -22.5), Vector3(5, 5, 5), 0.0f);

	AddBridge();
	AddCubeToWorld(Vector3(0, 5, -22.5), Vector3(5, 5, 5), 0.0f);
	AddCubeToWorld(Vector3(0, 5, -32.5), Vector3(5, 5, 5), 0.0f);
	AddCubeToWorld(Vector3(0, 5, -42.5), Vector3(5, 5, 5), 0.0f);

	// Ice

	GameObject* ice = AddCubeToWorld(Vector3(25, 9, -42.5), Vector3(20, 1, 10), 0.0f);
	ice->GetPhysicsObject()->SetElasticity(0.8f);
	ice->GetPhysicsObject()->SetFriction(200.0f);

	// Finish
	AddCubeToWorld(Vector3(50, 5, -42.5), Vector3(5, 5, 10), 0.0f);
	GameObject* finish = AddCubeToWorld(Vector3(55, 11, -42.5), Vector3(1, 1, 10), 0.0f);
	finish->SetCollisionLayer(CollisionLayer::Finish);

	//AddBonusToWorld(Vector3(10, 5, 0));

	InitDefaultFloor();
}

void LevelOne::ResetGame() {
	physics->SetResetGame(false);
	player->GetTransform()
		.SetPosition(Vector3(0, 25, 0));
	player->GetPhysicsObject()->SetLinearVelocity(Vector3(0, 0, 0));
}


void LevelOne::FinishGame() {
	physics->SetResetGame(false);
	physics->SetEndGame(false);
	//gameEnded = true;
}

GameObject* LevelOne::AddSeesawToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject();

	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);
	cube->SetCollisionLayer(CollisionLayer::Wall);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	GameObject* hinge = AddCubeToWorld(position, Vector3(1, 2, 1), 0.0f);
	hinge->SetCollisionLayer(CollisionLayer::Wall);
	PositionConstraint* posConstraint = new PositionConstraint(cube, hinge, 0);
	world->AddConstraint(posConstraint);
	HingeConstraint* constraint = new HingeConstraint(cube, hinge);
	world->AddConstraint(constraint);

	return cube;
}

GameObject* LevelOne::AddHammerToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject();

	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);
	cube->SetCollisionLayer(CollisionLayer::Wall);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();

	world->AddGameObject(cube);

	GameObject* hinge = AddCubeToWorld(position + Vector3(0,10,0), Vector3(1, 1, 1), 0.0f);
	hinge->SetCollisionLayer(CollisionLayer::Wall);
	PositionConstraint* posConstraint = new PositionConstraint(cube, hinge, 5);
	world->AddConstraint(posConstraint);
	HingeConstraint* constraint = new HingeConstraint(cube, hinge);
	world->AddConstraint(constraint);

	return cube;
}

void LevelOne::AddBridge() {
	Vector3 cubeSize = Vector3(1, 1, 4);

	float invCubeMass = 5; //how heavy the middle pieces are
	int numLinks = 8;
	float maxDistance = 4; // constraint distance
	float cubeDistance = 2; // distance between links

	Vector3 startPos = Vector3(43, 9, -22.5);

	GameObject* start = AddCapsuleToWorld(startPos + Vector3(0, 0, 0)
		, cubeSize.z, 1, 0);
	start->GetTransform().SetOrientation(
		start->GetTransform().GetOrientation() * Quaternion(Vector3(-1, 0, 0), 1));
	GameObject* end = AddCapsuleToWorld(startPos - Vector3((numLinks + 10)
		* cubeDistance, 0, 0), cubeSize.z, 1, 0);
	end->GetTransform().SetOrientation(
		end->GetTransform().GetOrientation() * Quaternion(Vector3(-1, 0, 0), 1));

	GameObject* previous = start;

	for (int i = 0; i < numLinks; ++i) {
		GameObject* block = AddCapsuleToWorld(startPos - Vector3((i + 1) *
			cubeDistance, 0, 0), cubeSize.z, 1 ,invCubeMass);
		block->GetTransform().SetOrientation(
			block->GetTransform().GetOrientation() * Quaternion(Vector3(-1, 0, 0), 1));
		PositionConstraint* constraint = new PositionConstraint(previous,
			block, maxDistance);
		world->AddConstraint(constraint);
		previous = block;
	}
	PositionConstraint* constraint = new PositionConstraint(previous,
		end, maxDistance);
	world->AddConstraint(constraint);
}