#include "GameAudio.h"

vector<Music*>* GameAudio::vecMusicPtr = new vector<Music*>();
vector<GameSound*>* GameAudio::vecSoundPtr = new vector<GameSound*>();

GameAudio::GameAudio() { }

Music* GameAudio::newMusic(const string& file) {
    Music* music = new Music();
    if (!music->openFromFile(file)) {
        cout << "Error opening music file: " << file << endl;
        return NULL;
    }

    vecMusicPtr->push_back(music);
    return music;
}

GameSound* GameAudio::newSound(const string& filePath) {
    GameSound* sound = new GameSound();
    if (sound->loadFromFile(filePath)) {
        vecSoundPtr->push_back(sound);
        return sound;
    }
    return NULL;
}

void GameAudio::dispose() {
    for (unsigned int index = 0; index < vecMusicPtr->size(); ++index) {
        delete vecMusicPtr->at(index);
    }

    delete vecMusicPtr;

    for (unsigned int index = 0; index < vecSoundPtr->size(); ++index) {
        delete vecSoundPtr->at(index);
    }

    delete vecSoundPtr;
}

GameAudio::~GameAudio() {

}
