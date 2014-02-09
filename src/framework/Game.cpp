#include "Game.h"

Game::Game() {
    closed = false;
    screenPtr = 0;
    cumulativeTime = 0;
    float updateRate = 30.0f;
    updateTime = (1000.0f / updateRate) / 1000.0f;
}

void Game::update(const float& delta) {
    screenPtr->update(delta);
}

void Game::render(RenderWindow& win, const float& delta) {

    Event event;
    while (win.pollEvent(event)) {
        ///< Close window
        if (event.type == Event::Closed) {
            win.close();
        }
        screenPtr->updateInputEvent(win, event);
    }

    cumulativeTime += delta;
    if (cumulativeTime >= updateTime) {
        cumulativeTime -= updateTime;
        screenPtr->updateMouseMotion(win);
    }

    screenPtr->render(win, delta);

    if (closed) {
        win.close();
    }

}


void Game::setScreen(Screen* scrPtr) {
    delete screenPtr;
    screenPtr = scrPtr;
}


void Game::close() {
    closed = true;
}

void Game::setScreenSize(const Vector2i& sSize) {
    screenSize = sSize;
}

const Vector2i& Game::getScreenSize() {
    return screenSize;
}

Game::~Game() {
}
