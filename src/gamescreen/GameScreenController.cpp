#include "GameScreenController.h"

GameScreenController::GameScreenController(GameScreen* gameScreenPtr) {
    this->gameScreenPtr = gameScreenPtr;
}

void GameScreenController::keyPressed(const int& keycode) {

}

void GameScreenController::keyReleased(const int& keycode) {

}

void GameScreenController::leftMousePressed(const int& x, const int& y) {

}

void GameScreenController::leftMouseReleased(const int& x, const int& y) {

}

void GameScreenController::rightMousePressed(const int& x, const int& y) {
    mousePrevPos.x = x;
    mousePrevPos.y = y;
    scrollScreen = true;
}

void GameScreenController::rightMouseReleased(const int& x, const int& y) {
    scrollScreen = false;
}


void GameScreenController::mouseMoved(const int& x, const int& y) {
    screenScrolling(x, y);
}

void GameScreenController::screenScrolling(const int& x, const int& y) {
    int scrollAmountX = x - mousePrevPos.x;
    int scrollAmountY = y - mousePrevPos.y;
    mousePrevPos.x = x;
    mousePrevPos.y = y;

    if (scrollScreen) {
        GameScreenUpdate* updatePtr = gameScreenPtr->updatePtr;
        Vector2f& mapPos = updatePtr->mapPos;

        // Limiting the screen scrolling to prevent seeing blank background
        if (mapPos.x <= 0) {
            mapPos.x += scrollAmountX;
            if (mapPos.x > 0) {
                mapPos.x = 0;
            }

            float& scrWidth = gameScreenPtr->gamePtr->width;
            if (mapPos.x < -scrWidth) {
                mapPos.x = -scrWidth;
            }
        }

        if (mapPos.y <= 0) {
            mapPos.y += scrollAmountY;
            if (mapPos.y > 0) {
                mapPos.y = 0;
            }

            float& scrHeight = gameScreenPtr->gamePtr->height;
            if (mapPos.y < -scrHeight) {
                mapPos.y = -scrHeight;
            }
        }
    }
}

void GameScreenController::mouseMotion(const int& x, const int& y) {

}

GameScreenController::~GameScreenController() {

}
