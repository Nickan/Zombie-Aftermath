#include "Timer.h"

Timer::Timer() {
    time = clock.getElapsedTime();
    currentTime = time.asSeconds();
    previousTime = time.asSeconds();
}

void Timer::update() {
    time = clock.getElapsedTime();
    currentTime = time.asSeconds();
    deltaTime = currentTime - previousTime;
    previousTime = currentTime;
}

float Timer::getDeltaTime() {
    void update();

    ///< Ensures that delta time will always have a positive value
    if (deltaTime < 0) {
        return -deltaTime;
    }
    return deltaTime;
}

Timer::~Timer() { }
