#include "MenuScreenInput.h"

MenuScreenInput::MenuScreenInput(MenuScreen* scrPtr) {
    screenPtr = scrPtr;

    selected = false;
    Settings::playMainBgm();
}

void MenuScreenInput::leftMousePressed(const int& mouseX, const int& mouseY) {
    playRect = screenPtr->getPlayRect();
    if (playRect.contains(mouseX, mouseY)) {
        screenPtr->getGamePtr()->setScreen(new GameScreen(screenPtr->getGamePtr()));
        Settings::stopMainBgm();
    }

    exitRect = screenPtr->getExitRect();
    if (exitRect.contains(mouseX, mouseY)) {
        screenPtr->getGamePtr()->exit();
    }

    ///< Toggles the sound on and off
    const IntRect& soundButtonRect = screenPtr->getSoundButtonRect();
    if (soundButtonRect.contains(mouseX, mouseY)) {
        Settings::soundEnable = !Settings::soundEnable;
        if (Settings::soundEnable) {
            Settings::playMainBgm();
        } else {
            Settings::stopMainBgm();
        }
        Settings::saveSettings();
    }
}

void MenuScreenInput::leftMouseReleased(const int& mouseX, const int& mouseY) {

}

void MenuScreenInput::rightMousePressed(const int& mouseX, const int& mouseY) {

}

void MenuScreenInput::rightMouseReleased(const int& mouseX, const int& mouseY) {

}

void MenuScreenInput::mouseMoved(const int& mouseX, const int& mouseY) {

}

void MenuScreenInput::mouseMotion(const int& mouseX, const int& mouseY) {
    if ( playRect.contains(mouseX, mouseY) ) {
        screenPtr->setCursorOnStart();

        if (selected) {
            Settings::playSelect();
        }
        selected = false;
    } else if ( exitRect.contains(mouseX, mouseY) ) {
        screenPtr->setCurosrOnExit();
        if (selected) {
            Settings::playSelect();
        }
        selected = false;
    } else {
        selected = true;
    }

    screenPtr->setDrawCursor(!selected);
}

void MenuScreenInput::keyPressed(const int& keyCode) {

}

void MenuScreenInput::keyReleased(const int& keyCode) {

}

MenuScreenInput::~MenuScreenInput() {
}
