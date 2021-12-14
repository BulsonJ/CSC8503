#pragma once
#include "TutorialGame.h"
class LevelOne : public TutorialGame
{
public:
	LevelOne();
	
protected:
	virtual void InitWorld();
	virtual void ResetGame();

	GameObject* AddSeesawToWorld(const Vector3& position, Vector3 dimensions, float inverseMass);
};

