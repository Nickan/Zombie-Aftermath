#include "GameAudio.h"

SoundBuffer GameAudio::buffer;
vector<Music*>* GameAudio::vecMusicPtr = new vector<Music*>();
vector<Sound*>* GameAudio::vecSoundPtr = new vector<Sound*>();

GameAudio::GameAudio() { }

Music* GameAudio::newMusic(const string& file) {
    Music* music = new Music();
    if (!music->openFromFile(file))
        cout << "Error opening music file: " << file << endl;

    vecMusicPtr->push_back(music);
    return music;
}

Sound* GameAudio::newSound(const string& file) {
    if (!buffer.loadFromFile(file))
        cout << "Error opening sound file: " << file << endl;

    Sound* sound = new Sound();
    sound->setBuffer(buffer);

    vecSoundPtr->push_back(sound);
    return sound;
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
