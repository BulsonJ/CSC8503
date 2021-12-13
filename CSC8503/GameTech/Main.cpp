#include "../../Common/Window.h"

#include "../CSC8503Common/StateMachine.h"
#include "../CSC8503Common/StateTransition.h"
#include "../CSC8503Common/State.h"

#include "../CSC8503Common/PushdownState.h"
#include "../CSC8503Common/PushdownMachine.h"

#include "../CSC8503Common/NavigationGrid.h"


#include "TutorialGame.h"
#include "LevelOne.h"
#include "LevelTwo.h"
#include "MainMenu.h"

using namespace NCL;
using namespace CSC8503;

class PauseScreen : public PushdownState {
	PushdownResult OnUpdate(float dt, PushdownState * *newState) override {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::U)) {
			return PushdownResult::Pop;
		}
		return PushdownResult::NoChange;
	}
	void OnAwake() override {
		std::cout << "Press U to unpause game!\n";
	}
};


class GameScreen : public PushdownState {
public:
	GameScreen(TutorialGame** g, TutorialGame* level) {
		currentGame = g;
		gameLevel = level;
	}
	PushdownResult OnUpdate(float dt, PushdownState * *newState) override {
		/*pauseReminder -= dt;
		if (pauseReminder < 0) {
			std::cout << "Coins mined: " << coinsMined << "\n";
			std::cout << "Press P to pause game , or F1 to return to main menu!\n";
				pauseReminder += 1.0f;
		}
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::P)) {
			* newState = new PauseScreen();
			return PushdownResult::Push;
		}
		*/
		if (Window::GetKeyboard()->KeyDown(KeyboardKeys::F1)) {
			std::cout << "Returning to main menu!\n";
			return PushdownResult::Pop;
		}/**
		if (rand() % 7 == 0) {
			coinsMined++;
			
		}*/
		return PushdownResult::NoChange;
		
	};
	void OnAwake() override {
		*currentGame = gameLevel;
	}
protected:
	TutorialGame** currentGame;
	TutorialGame* gameLevel;
	
};

class MenuScreen : public PushdownState {
public:
	MenuScreen(TutorialGame** g) {
		currentGame = g;
	};

protected:
	PushdownResult OnUpdate(float dt, PushdownState * *newState) override {
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::U)) {
			* newState = new GameScreen(currentGame, new LevelOne());
			return PushdownResult::Push;
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::I)) {
			*newState = new GameScreen(currentGame, new LevelTwo());
			return PushdownResult::Push;
		}
		return PushdownResult::NoChange;
	};
	
	void OnAwake() override {
		*currentGame = new MainMenu();
	}


	TutorialGame** currentGame;
};
/*

The main function should look pretty familar to you!
We make a window, and then go into a while loop that repeatedly
runs our 'game' until we press escape. Instead of making a 'renderer'
and updating it, we instead make a whole game, and repeatedly update that,
instead. 

This time, we've added some extra functionality to the window class - we can
hide or show the 

*/
int main() {
	Window*w = Window::CreateGameWindow("CSC8503 Game technology!", 1280, 720);

	if (!w->HasInitialised()) {
		return -1;
	}	
	srand(time(0));
	w->ShowOSPointer(false);
	w->LockMouseToWindow(true);

	// Make menu screen
	TutorialGame* g = new MainMenu();

	PushdownMachine machine(new MenuScreen(&g));

	w->GetTimer()->GetTimeDeltaSeconds(); //Clear the timer so we don't get a larget first dt!
	while (w->UpdateWindow() && !Window::GetKeyboard()->KeyDown(KeyboardKeys::ESCAPE)) {
		float dt = w->GetTimer()->GetTimeDeltaSeconds();
		if (dt > 0.1f) {
			std::cout << "Skipping large time delta" << std::endl;
			continue; //must have hit a breakpoint or something to have a 1 second frame time!
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::PRIOR)) {
			w->ShowConsole(true);
		}
		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::NEXT)) {
			w->ShowConsole(false);
		}

		if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::T)) {
			w->SetWindowPosition(0, 0);
		}
		w->SetTitle("Gametech frame time:" + std::to_string(1000.0f * dt));

		// Custom
		if (!machine.Update(dt)) return 0;

		g->UpdateGame(dt);
	}
	Window::DestroyGameWindow();
}