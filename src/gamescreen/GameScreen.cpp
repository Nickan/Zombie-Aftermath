#include "GameScreen.h"

GameScreen::GameScreen(ZombieAftermath* gamePtr) {
    this->gamePtr = gamePtr;
    setInput(new GameScreenController(this));

    updatePtr = new GameScreenUpdate();
    rendererPtr = new GameScreenRenderer(updatePtr);
    updatePtr->initializeMapInfo(rendererPtr->getTileMapInfo());
}

void GameScreen::render(RenderWindow& win, const float& delta) {
    updatePtr->update(delta);
    rendererPtr->render(win, delta);
}

GameScreen::~GameScreen() {
    delete updatePtr;
    delete rendererPtr;
}
