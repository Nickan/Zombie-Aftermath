#include "Screen.h"

Screen::Screen() {
    inputPtr = NULL;
}

///< Still figuring out what is the flexible type of getting input
void Screen::updateInputEvent(RenderWindow& win, Event& event) {

    if (inputPtr != NULL) {    // Ensures the setInput() is called first before doing anything

        if ( (event.type == Event::KeyPressed) ) {
            inputPtr->keyPressed(event.key.code);
        }

        if ( (event.type == Event::KeyReleased) ) {
            inputPtr->keyReleased(event.key.code);
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
            inputPtr->leftMousePressed(event.mouseButton.x, event.mouseButton.y);
        }

        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left) {
            inputPtr->leftMouseReleased(event.mouseButton.x, event.mouseButton.y);
        }

        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right) {
            inputPtr->rightMousePressed(event.mouseButton.x, event.mouseButton.y);
        }

        if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Right) {
            inputPtr->rightMouseReleased(event.mouseButton.x, event.mouseButton.y);
        }

        ///< The mouseButton.x and y doesn't function well with MouseMoved
        if (event.type == Event::MouseMoved) {
            mousePos = Mouse::getPosition(win);
            inputPtr->mouseMoved(mousePos.x, mousePos.y);
        }
    }

}

void Screen::updateMouseMotion(RenderWindow& win) {
    if (inputPtr == NULL)  // Ensures the setInput() is called first before doing anything
        return;

    mousePos = Mouse::getPosition(win);
    inputPtr->mouseMotion(mousePos.x, mousePos.y);
}


void Screen::setInput(Input* i) {
    delete inputPtr;
    inputPtr = i;
}


Screen::~Screen() {
    delete inputPtr;
}
