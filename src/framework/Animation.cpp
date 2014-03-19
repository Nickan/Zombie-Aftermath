#include "Animation.h"

/** For animation settings */
const int Animation::NORMAL = 0;
const int Animation::LOOP = 1;

//Animation::Animation() {}

Animation::Animation(Texture& t, const int w, const int h, const int totalCol, const int totalF, const float duration, const int playMode) {
    texture = t;
    width = w;
    height = h;
    totalColumns = totalCol;
    totalFrames = totalF;
    this->duration = duration;
    this->playMode = playMode;
    init();
}

void Animation::init() {
    currentFrame = 0;

    drawRect = IntRect(0, 0, width, height);

    sprite.setOrigin(drawRect.width / 2, drawRect.height / 2);
    sprite.setTexture(texture);
    sprite.setTextureRect(drawRect);
}

void Animation::draw(RenderWindow& win, float& stateTime) {
    win.draw(sprite);
    updateSprite(stateTime);
}

void Animation::draw(RenderWindow& win, const float& x, const float& y, const float& rotation, const float& delta) {
    sprite.setPosition(x + drawRect.width / 2, y + drawRect.height / 2);
    sprite.setRotation(rotation);
    win.draw(sprite);
    updateSprite(delta);
}

void Animation::updateSprite(const float& stateTime) {
    // I just discovered the fmod() is existing, lately read it from the reference >_<
    float currentStateTime = abs(fmod(stateTime, duration));

    switch (playMode) {
    case NORMAL:
        currentFrame  = (stateTime < duration) ? ((int) (currentStateTime / duration)) : totalFrames - 1;
        break;
    case LOOP:
        float perFrameDuration = duration / totalFrames;
        currentFrame = (int) (currentStateTime / perFrameDuration);
        break;
    }

    frameX = currentFrame % totalColumns;
    frameY = currentFrame / totalColumns;

    drawRect.left = width * frameX;
    drawRect.top = height * frameY;
    sprite.setTextureRect(drawRect);
}

void Animation::setPosition(const float& x, const float& y) {
    sprite.setPosition(x + drawRect.width / 2, y + drawRect.height / 2);
    position.x = x;
    position.y = y;
}

void Animation::setRotation(const float& rotation) {
    sprite.setRotation(rotation);
}

void Animation::setScale(const float& width, const float& height) {
    sprite.setScale(width, height);
}


const int& Animation::getWidth() {
    return width;
}

const int& Animation::getHeight() {
    return height;
}

const Vector2f& Animation::getPosition() {
    return position;
}

Animation::~Animation() { }
