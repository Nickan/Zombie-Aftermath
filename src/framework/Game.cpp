#include "Game.h"

float Game::width;
float Game::height;

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


        if (closed) {
            win.close();
        }

        win.display();
    }

}

void Game::setScreen(Screen* scrPtr) {
    delete this->scrPtr;
    this->scrPtr = scrPtr;
}

const float& Game::getWidth() {
    return width;
}

const float& Game::getHeight() {
    return height;
}

void Game::exit() {
    closed = true;
}

Game::~Game() {
}
