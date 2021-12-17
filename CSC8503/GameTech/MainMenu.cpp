#include "MainMenu.h"

using namespace NCL;
using namespace CSC8503;

MainMenu::MainMenu() : TutorialGame() {
	InitCamera();
	InitWorld();
}

void MainMenu::InitWorld() {
	world->ClearAndErase();
	physics->Clear();
}

void MainMenu::UpdateGame(float dt) {

	Debug::Print("CSC 8503 Coursework", Vector2(30, 30));
	Debug::Print("Level 1 - Press 1", Vector2(30, 40));
	Debug::Print("Level 2 - Press 2", Vector2(30, 50));
	Debug::Print("Exit - Press ESC", Vector2(30, 60));


	world->UpdateWorld(dt);
	renderer->Update(dt);

	Debug::FlushRenderables(dt);
	renderer->Render();

}
