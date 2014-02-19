#include "GameScreen.h"

GameScreen::GameScreen(ZombieAftermath* gamePtr) {
    this->gamePtr = gamePtr;
    circle = CircleShape(100.0f);
    setInput(new GameScreenController());
}

void GameScreen::render(RenderWindow& win, const float& delta) {
//    cout << "" << delta << endl;
    win.draw(circle);
}

GameScreen::~GameScreen() {
    //dtor
}
