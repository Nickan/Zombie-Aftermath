#include "GameSound.h"

GameSound::GameSound() {}

const bool GameSound::loadFromFile(const string& filePath) {
    if (!buffer.loadFromFile(filePath)) {
        cout << "Error loading GameSound: " << filePath << endl;
        return false;
    }
    setBuffer(buffer);
    return true;
}

GameSound::~GameSound()
{
    //dtor
}
