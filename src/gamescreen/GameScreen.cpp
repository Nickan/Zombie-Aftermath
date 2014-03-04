#include "GameScreen.h"

GameScreen::GameScreen(ZombieAftermath* gamePtr) {
    this->gamePtr = gamePtr;
    setInput(new GameScreenController());

    updatePtr = new GameScreenUpdate();
    rendererPtr = new GameScreenRenderer(updatePtr);
}

void GameScreen::render(RenderWindow& win, const float& delta) {
    updatePtr->update(delta);
    rendererPtr->render(win, delta);
}

GameScreen::~GameScreen() {
    delete updatePtr;
    delete rendererPtr;
}
