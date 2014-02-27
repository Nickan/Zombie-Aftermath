#include "GameSprite.h"

GameSprite::GameSprite(Texture& t, const int& x, const int& y) {
    texture = t;
    setPosition(x, y);
    initialize();
}

void GameSprite::initialize() {
    sprite.setTexture(texture);
    bounds = sprite.getTextureRect();
    sprite.setOrigin(bounds.width / 2, bounds.height / 2);
}

void GameSprite::draw(RenderWindow& win) {
    win.draw(sprite);
}

void GameSprite::draw(RenderWindow& win, const int& x, const int& y) {
    setPosition(x, y);
    win.draw(sprite);
}

GameSprite::GameSprite(const string& fileName) {
    texture.loadFromFile(fileName);
    sprite.setTexture(texture);
}

void GameSprite::loadFromFile(const string& filePath) {
    texture.loadFromFile(filePath);
    sprite.setTexture(texture);
}

void GameSprite::setTexture(Texture& t) {
    texture = t;
    initialize();
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

IntRect& GameSprite::getBounds() {
    return bounds;
}

GameSprite::~GameSprite() { }
