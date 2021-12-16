#include "CoinObject.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/State.h"

using namespace NCL;
using namespace CSC8503;

CoinObject::CoinObject() {
	counter = 0.0f;
	stateMachine = new StateMachine();

	
	State * stateA = new State([&](float dt)-> void
	{
		this->MoveLeft(dt);
	}
	);
	State * stateB = new State([&](float dt)-> void
	{
		this->MoveRight(dt);
	}
	);
	
	stateMachine->AddState(stateA);
	stateMachine->AddState(stateB);
	
	stateMachine->AddTransition(new StateTransition(stateA, stateB,
	[&]()-> bool
	{
		return this->counter > 2.0f;
	}
	));
	
	stateMachine->AddTransition(new StateTransition(stateB, stateA,
	[&]()-> bool
	{
		return this->counter < 0.0f;
	}
	));
}

CoinObject ::~CoinObject() {
	delete stateMachine;
}

void CoinObject::Update(float dt) {
	stateMachine->Update(dt);
}

void CoinObject::MoveLeft(float dt) {
	GetPhysicsObject()->AddForce({ 0, 0, -6 });
	counter += dt;
}

void CoinObject::MoveRight(float dt) {
	GetPhysicsObject()->AddForce({ 0, 0, 6 });
	counter -= dt;
}