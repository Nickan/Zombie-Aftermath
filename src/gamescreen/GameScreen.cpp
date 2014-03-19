#include "GameScreen.h"

GameScreen::GameScreen(ZombieAftermath* gamePtr) {
    this->gamePtr = gamePtr;

    updatePtr = new GameScreenUpdate();
    rendererPtr = new GameScreenRenderer(updatePtr);
    updatePtr->initializeMapInfo(rendererPtr->getTileMapInfo());

    setInput(new GameScreenController(this));
}

void GameScreen::render(RenderWindow& win, const float& delta) {
    // Don't update if the delta is way too big
    if (delta > 0.1f) {
        return;
    }

    updatePtr->update(delta);
    rendererPtr->render(win, delta);
}

GameScreen::~GameScreen() {
    delete updatePtr;
    delete rendererPtr;
}
