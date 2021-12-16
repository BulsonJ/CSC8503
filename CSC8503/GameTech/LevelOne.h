#pragma once
#include "TutorialGame.h"
class LevelOne : public TutorialGame
{
public:
	LevelOne();
	
protected:
	virtual void InitWorld();

	virtual void WinScreen();
	virtual void LoseScreen();

	virtual void ResetGame();
	virtual void FinishGame();

	GameObject* AddHammerToWorld(const Vector3& position, Vector3 dimensions, float inverseMass);
	void AddBridge();
};

