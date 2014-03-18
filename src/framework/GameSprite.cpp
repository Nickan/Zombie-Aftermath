#include "GameSprite.h"

GameSprite::GameSprite() {
//    texture = NULL;
//    setPosition(0, 0);
}

GameSprite::GameSprite(const string& fileName) {
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
}

GameSprite::GameSprite(Texture& t, const int x, const int y) {
    texture = t;
    initialize();
    setPosition(x, y);
}

void GameSprite::loadFromFile(const string& filePath) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
}

void GameSprite::initialize() {
    sprite.setTexture(texture);
    bounds = sprite.getTextureRect();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void GameSprite::draw(RenderWindow& win) {
    win.draw(sprite);
}

void GameSprite::draw(RenderWindow& win, const int& x, const int& y, const float& rotation) {
    setPosition(x, y);
    sprite.setRotation(rotation);
    win.draw(sprite);
}

void GameSprite::setTexture(Texture& t) {
    texture = t;
    initialize();
}

void GameSprite::setColor(const Color& color) {
    sprite.setColor(color);
}

void GameSprite::setPosition(const int& x, const int& y) {
    sprite.setPosition(x + bounds.width / 2, y + bounds.height / 2);
}

void GameSprite::setScale(const float& factorX, const float& factorY) {
    sprite.setScale(factorX, factorY);
}

void GameSprite::setRotation(const float& rotation) {
    sprite.setRotation(rotation);
}

const Vector2f& GameSprite::getPosition() {
    return sprite.getPosition();
}

const IntRect& GameSprite::getBounds() {
    return sprite.getTextureRect();
}

GameSprite::~GameSprite() { }
