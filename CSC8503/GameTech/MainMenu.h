#pragma once
#include "TutorialGame.h"
class MainMenu : public TutorialGame
{
public:
	MainMenu();

protected:
	virtual void InitWorld();
	virtual void UpdateGame(float dt) override;
	virtual void ResetGame() {};
	virtual void FinishGame() {};
};

