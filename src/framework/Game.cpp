#include "Game.h"

Game::Game(const float width, const float height) {
    this->width = width;
    this->height = height;
    scrPtr = NULL;
    cumulativeTime = 0;
    float updateRate = 30.0f;
    updateTime = (1000.0f / updateRate) / 1000.0f;

    timerPtr = new Timer();
}

void Game::startLooping() {
    RenderWindow win(VideoMode(width, height), "Game Created!");
    while (win.isOpen()) {
        win.clear();

        float delta = timerPtr->getDeltaTime();
        scrPtr->update(delta);
        scrPtr->render(win, delta);

        Event event;
        while (win.pollEvent(event)) {
            if (event.type == Event::Closed) {
                win.close();
            }
            scrPtr->updateInputEvent(win, event);
        }

        // For mouse update
        cumulativeTime += delta;
        if (cumulativeTime >= updateTime) {
            cumulativeTime -= updateTime;
            scrPtr->updateMouseMotion(win);
        }

        win.display();
    }
}

/*
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
*/

void Game::setScreen(Screen* scrPtr) {
    delete this->scrPtr;
    this->scrPtr = scrPtr;
}


void Game::setScreenSize(const Vector2i& scrSize) {
    screenSize = scrSize;
}

const Vector2i& Game::getScreenSize() {
    return screenSize;
}

Game::~Game() {
}
