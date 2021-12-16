#pragma once
#include "TutorialGame.h"
class LevelTwo : public TutorialGame
{
public:
	LevelTwo();

protected:
	virtual void InitWorld();

	virtual void WinScreen();
	virtual void LoseScreen();

	virtual void ResetGame();
	virtual void FinishGame();
};

