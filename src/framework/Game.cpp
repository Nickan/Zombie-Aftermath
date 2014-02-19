#include "Game.h"

Game::Game(const float width, const float height, const string gameName) {
    this->width = width;
    this->height = height;
    scrPtr = NULL;
    cumulativeTime = 0;
    float updateRate = 30.0f;
    updateTime = (1000.0f / updateRate) / 1000.0f;

    timerPtr = new Timer();
    this->gameName = gameName;
}

void Game::startLooping() {
    RenderWindow win(VideoMode(width, height), gameName);
    while (win.isOpen()) {
        win.clear();

        float delta = timerPtr->getDeltaTime();
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
