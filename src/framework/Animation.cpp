#include "Animation.h"

/** For animation settings */
const int Animation::NORMAL = 0;
const int Animation::LOOP = 1;

Animation::Animation() {}

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
//    timeDelay = (1000.0f / frameRate) / 1000.0f;

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

void Animation::draw(RenderWindow& win, const float& x, const float& y, const float& delta) {
    sprite.setPosition(x + drawRect.width / 2, y + drawRect.height / 2);
    win.draw(sprite);
    updateSprite(delta);
}

void Animation::updateSprite(const float& stateTime) {
    // Noninteger use of modulus is a big NONO.
    float currentStateTime = getModulus(stateTime, duration);

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

    //...
    cout << "Current frame: " << currentFrame << endl;
}

////////////////////////////////////////////////////////////////////
//    My attempt to simulate the modulus operation
//    Not accurate, I might change this to double for accuracy
////////////////////////////////////////////////////////////////////
const float& Animation::getModulus(const float& firstNum, const float& secondNum) {
    float mod = 0;
    float div = firstNum / secondNum;

    if (div >= 1.0f) {
        // If the first number has a greater value than the second number
        // Example 1: first num = 7.5, second num = 5, answer is 1.5
        // Exmaple 2: first num = 12.5, second num = 5, answer is 2.5
        // Get the decimal place by setting temporary the div to int
            // float excessNum =  div - ((int) div);
            // float mod = excessNum * secondNum;
        // Then get the difference
        float excessNum = div - ((int) div);
        mod = excessNum * secondNum;
    } else {
        mod = firstNum;
    }

    //...
//    cout << "Modulus: " << mod << endl;
    return mod;
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


int& Animation::getWidth() {
    return width;
}

int& Animation::getHeight() {
    return height;
}

Vector2f& Animation::getPosition() {
    return position;
}

Animation::~Animation() { }
