#include "EnemyGameObject.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/State.h"
#include "../CSC8503Common/NavigationGrid.h"

using namespace NCL;
using namespace CSC8503;

EnemyGameObject::EnemyGameObject(NavigationGrid* grid, GameObject* target) {
	this->stateMachine = new StateMachine();
	this->grid = grid;
	this->target = target;
	counter = 20.0f;

	State* idle = new State([&](float dt)-> void
		{
			this->GetPhysicsObject()->ClearForces();
			this->GetPhysicsObject()->SetLinearVelocity(Vector3(0, 0, 0));
		}
	, "Idle");
	State* chase = new State([&](float dt)-> void
		{
			this->MoveToTarget(dt);
		}
	, "Chase Path");
	State* chaseClose = new State([&](float dt)-> void
		{
			Vector3 dir = (this->target->GetTransform().GetPosition() - this->GetTransform().GetPosition());
			dir = Vector3(dir.x, 0, dir.z);
			GetPhysicsObject()->SetLinearVelocity(dir.Normalised() * 1000.0f * dt);
		}
	, "Chase Close");

	stateMachine->AddState(idle);
	stateMachine->AddState(chase);
	stateMachine->AddState(chaseClose);

	stateMachine->AddTransition(new StateTransition(idle, chase,
		[&]()-> bool
		{
			if (this->GetTarget()) {
				return (this->GetTarget()->GetTransform().GetPosition() - this->GetTransform().GetPosition()).Length() >= 10.0f;
			}
		}
	));

	stateMachine->AddTransition(new StateTransition(chase, chaseClose,
		[&]()-> bool
		{
			if (this->GetTarget()) {
				return (this->target->GetTransform().GetPosition() - this->GetTransform().GetPosition()).Length() < 10.0f;
			}
		}
	));

	stateMachine->AddTransition(new StateTransition(chaseClose, chase,
		[&]()-> bool
		{
			if (this->GetTarget()) {
				return (this->target->GetTransform().GetPosition() - this->GetTransform().GetPosition()).Length() > 10.0f;
			}
		}
	));

	stateMachine->AddTransition(new StateTransition(chaseClose, idle,
		[&]()-> bool
		{
			if (this->GetTarget()) {
				return (this->target->GetTransform().GetPosition() - this->GetTransform().GetPosition()).Length() < 1.0f;
			}
		}
	));
}

EnemyGameObject::~EnemyGameObject() {
	delete stateMachine;
}

void EnemyGameObject::Update(float dt) {
	if (counter > 2.0f) {
		CalculatePath();
		counter = 0.0f;
	}
	stateMachine->Update(dt);
	counter += dt;
}

void EnemyGameObject::MoveToTarget(float dt) {
	if (pathToTarget.size() > 0) {
		auto it = pathToTarget.begin();
		Vector3 target = *it;
		Vector3 dir = (target - this->GetTransform().GetPosition());
		dir = Vector3(dir.x, 0, dir.z);
		GetPhysicsObject()->SetLinearVelocity(dir.Normalised() * 1000.0f * dt);

		if (dir.Length() <= 2.0f) {
			pathToTarget.erase(it);
			GetPhysicsObject()->SetLinearVelocity(Vector3(0, 0, 0));
		}
	}
}

void EnemyGameObject::CalculatePath() {
	pathToTarget.clear();
	NavigationPath outPath;

	if (target == nullptr) { 
		return; 
	}
	bool found = grid->FindPath(GetTransform().GetPosition(), target->GetTransform().GetPosition(), outPath);

	Vector3 pos;
	while (outPath.PopWaypoint(pos)) {
		pathToTarget.push_back(pos);
	}
}

string EnemyGameObject::GetState() {
	return stateMachine->GetStateName();
}