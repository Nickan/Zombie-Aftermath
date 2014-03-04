#include "MenuScreen.h"

MenuScreen::MenuScreen(ZombieAftermath* gamePtr) {
    this->gamePtr = gamePtr;
    Image image;
    image.loadFromFile("assets/allmenuimages.png");
    Texture texture;
    texture.setSmooth(true);

    playSpriteX = 380;
    playSpriteY = 400;

    texture.loadFromImage(image, IntRect(0, 0, 800, 80));
    aniCursorPtr = new Animation(texture, 80, 80, 10, 10, 0.5f, Animation::LOOP);
    aniCursorPtr->setScale(1.1f, 0.65f);
    aniCursorPtr->setPosition(0, 0);

    tempStateTime = 0;

    playRect = IntRect(10, 80, 43, 13);
    texture.loadFromImage(image, playRect);

    playSpritePtr = new GameSprite(texture, playSpriteX, playSpriteY);
    playRect.left = playSpriteX;
    playRect.top = playSpriteY;

    exitRect = IntRect(60, 80, 43, 13);
    texture.loadFromImage(image, exitRect);
    exitSpritePtr = new GameSprite(texture, playSpriteX, playSpriteY + 40);
    exitRect.left = playSpriteX;
    exitRect.top = playSpriteY + 40;

    IntRect gameTitleRect = IntRect(0, 100, 385, 285);
    texture.loadFromImage(image, gameTitleRect);

    gameTitleSpritePtr = new GameSprite(texture, 210, 100);
    gameTitleSpritePtr->setPosition(210, 100);

    soundRect = IntRect(390, 100, 64, 64);
    texture.loadFromImage(image, soundRect);

    soundEnableSpritePtr = new GameSprite(texture, 50, 500);

    soundRect = IntRect(454, 100, 64, 64);
    texture.loadFromImage(image, soundRect);
    soundDisableSpritePtr = new GameSprite(texture, 50, 500);
    soundRect.left = 50;
    soundRect.top = 500;
    drawCursor = false;

    Settings::initialize();
    Settings::soundEnable = true;
    setInput(new MenuScreenInput(this));
}

void MenuScreen::render(RenderWindow& win, const float& delta) {
    tempStateTime += delta;

    gameTitleSpritePtr->draw(win);

    if (drawCursor)
        aniCursorPtr->draw(win, tempStateTime);
    playSpritePtr->draw(win);
    exitSpritePtr->draw(win);

    if (Settings::soundEnable) {
        soundEnableSpritePtr->draw(win);
    } else {
        soundDisableSpritePtr->draw(win);
    }
}

const int& MenuScreen::getPlaySpriteX() {
    return playSpriteX;
}

const int& MenuScreen::getPlaySpriteY() {
    return playSpriteY;
}

const IntRect& MenuScreen::getPlayRect() {
    return playRect;
}

const IntRect& MenuScreen::getExitRect() {
    return exitRect;
}

const IntRect& MenuScreen::getSoundButtonRect() {
    return soundRect;
}

void MenuScreen::setCursorOnStart() {
    aniCursorPtr->setPosition(playSpriteX - 20, playSpriteY - 32);
}

void MenuScreen::setCurosrOnExit() {
    aniCursorPtr->setPosition(playSpriteX - 20, playSpriteX + 26);
}

void MenuScreen::setDrawCursor(const bool& drawCursor) {
    this->drawCursor = drawCursor;
}

ZombieAftermath* MenuScreen::getGamePtr() {
    return gamePtr;
}

MenuScreen::~MenuScreen() {
    delete aniCursorPtr;
}
