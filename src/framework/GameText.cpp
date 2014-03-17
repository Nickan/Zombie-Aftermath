#include "GameText.h"

GameText::GameText(const string& fontPath) {
    font.loadFromFile(fontPath);
    text.setFont(font);
}

void GameText::draw(RenderWindow& win, const string& str, const float& x, const float& y, const Color& color) {
    text.setPosition(x, y);
    text.setString(str);
    text.setColor(color);
    win.draw(text);
}

void GameText::setCharSize(const float& charSize) {
    text.setCharacterSize(charSize);
}

GameText::~GameText() {
    //dtor
}
