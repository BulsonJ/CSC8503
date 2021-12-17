#include "LevelOne.h"
#include "../CSC8503Common/PositionConstraint.h"
#include "../CSC8503Common/HingeConstraint.h"
#include "../CSC8503Common/RotationConstraint.h"
#include "../CSC8503Common/OBBVolume.h"
#include "../CSC8503Common/FinishObject.h"
#include "../CSC8503Common/ResetObject.h"
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

	AddHammerToWorld(Vector3(-5.5, 22.5, -5), Vector3(1, 1, 7), 1.0f);

	// Bride section
	AddCubeToWorld(Vector3(0, 10, 0), Vector3(5, 10, 5), 0.0f);
	GameObject* bridge = AddCubeToWorld(Vector3(12.5, 17.5, 0), Vector3(7.5, 2.5, 2.5), 0.0f);
	AddCubeToWorld(Vector3(25, 10, 0), Vector3(5, 10, 5), 0.0f);
	GameObject* bridge2 = AddCubeToWorld(Vector3(25 + 12.5, 17.5, 0), Vector3(7.5, 2.5, 2.5), 0.0f);
	AddCubeToWorld(Vector3(50, 10, 0), Vector3(5, 10, 5), 0.0f);

	AddHammerToWorld(Vector3(-5.5+60, 22.5, 0), Vector3(1, 1, 7), 1.0f);
	AddHammerToWorld(Vector3(-5.5 , 12.5, -35), Vector3(1, 1, 7), 1.0f);

	GameObject* ramp = AddOBBCubeToWorld(Vector3(50, 10, -10), Vector3(5, 10, 5), 0.0f);
	ramp->GetTransform().SetOrientation(
		ramp->GetTransform().GetOrientation() * Quaternion(Vector3(0,-1,-0.5), 0));

	AddCubeToWorld(Vector3(50, 5, -22.5), Vector3(5, 5, 5), 0.0f);

	AddBridge();
	AddCubeToWorld(Vector3(0, 5, -22.5), Vector3(5, 5, 5), 0.0f);
	AddCubeToWorld(Vector3(0, 5, -32.5), Vector3(5, 5, 5), 0.0f);
	AddCubeToWorld(Vector3(0, 5, -42.5), Vector3(5, 5, 5), 0.0f);

	// Ice
	GameObject* ice = AddCubeToWorld(Vector3(25, 9, -42.5), Vector3(20, 1, 8), 0.0f);
	ice->GetPhysicsObject()->SetElasticity(0.8f);
	ice->GetPhysicsObject()->SetFriction(0.0f);
	ice->SetColour(Vector4(0, 0.8, 0.8, 1));
	GameObject* obstacle = AddSphereToWorld(Vector3(25, 9, -42.5), 3, 0.0f);
	obstacle->SetColour(Vector4(0, 0.8, 0.8, 1));
	obstacle = AddSphereToWorld(Vector3(35, 9, -48.5), 3, 0.0f);
	obstacle->SetColour(Vector4(0, 0.8, 0.8, 1));

	// Finish
	AddCubeToWorld(Vector3(50, 5, -42.5), Vector3(5, 5, 10), 0.0f);
	GameObject* finish = AddFinishToWorld(Vector3(55, 11, -42.5), Vector3(1, 1, 10), 0.0f);
	finish->SetCollisionLayer(CollisionLayer::Finish);

	InitMixedGridWorld(5, 5, 3, 3);

	AddCoinObjectToWorld(Vector3(25, 32, 5.5));
	AddCoinObjectToWorld(Vector3(35+12.5, 32, 5.5));

	InitResetFloor();
}

void LevelOne::WinScreen() {
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

void LevelOne::LoseScreen() {
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

void LevelOne::ResetGame() {
	transitionTimer = true;
	selectionObject = nullptr;
	lockedObject = nullptr;

	InitWorld();
	//InitCamera();
	elapsedTime = 0;
	score = 0;
}


void LevelOne::FinishGame() {
	gameEnded = true;
}

GameObject* LevelOne::AddHammerToWorld(const Vector3& position, Vector3 dimensions, float inverseMass) {
	GameObject* cube = new GameObject();

	OBBVolume* volume = new OBBVolume(dimensions);

	cube->SetBoundingVolume((CollisionVolume*)volume);
	cube->SetCollisionLayer(CollisionLayer::Default);

	cube->GetTransform()
		.SetPosition(position)
		.SetScale(dimensions * 2);

	cube->SetRenderObject(new RenderObject(&cube->GetTransform(), cubeMesh, basicTex, basicShader));
	cube->SetPhysicsObject(new PhysicsObject(&cube->GetTransform(), cube->GetBoundingVolume()));
	cube->SetColour(Vector4(0.0, 0, 0.7, 1));

	cube->GetPhysicsObject()->SetInverseMass(inverseMass);
	cube->GetPhysicsObject()->InitCubeInertia();
	cube->GetPhysicsObject()->SetElasticity(1.0f);

	cube->SetLockFlags(AxisLock::ANGULAR_X | AxisLock::ANGULAR_Z | AxisLock::LINEAR_X | AxisLock::LINEAR_Y | AxisLock::LINEAR_Z);
	cube->SetUsesGravity(false);

	world->AddGameObject(cube);

	//GameObject* hinge = AddCubeToWorld(position + Vector3(0,15,0), Vector3(1, 1, 1), 0.0f);
	//hinge->SetCollisionLayer(CollisionLayer::Wall);
	//PositionConstraint* posConstraint = new PositionConstraint(cube, hinge, 10);
	//world->AddConstraint(posConstraint);
	//HingeConstraint* constraint = new HingeConstraint(cube, hinge);
	//world->AddConstraint(constraint);;

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

	start->SetColour(Vector4(0.6, 0.3, 0, 1));
	end->SetColour(Vector4(0.6, 0.3, 0, 1));

	GameObject* previous = start;

	for (int i = 0; i < numLinks; ++i) {
		GameObject* block = AddCapsuleToWorld(startPos - Vector3((i + 1) *
			cubeDistance, 0, 0), cubeSize.z, 1 ,invCubeMass);
		block->GetTransform().SetOrientation(
			block->GetTransform().GetOrientation() * Quaternion(Vector3(-1, 0, 0), 1));
		block->SetColour(Vector4(0.6, 0.3, 0, 1));
		PositionConstraint* constraint = new PositionConstraint(previous,
			block, maxDistance);
		world->AddConstraint(constraint);
		previous = block;
	}
	PositionConstraint* constraint = new PositionConstraint(previous,
		end, maxDistance);
	world->AddConstraint(constraint);
}