#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace sf;

// Handles the creationg of a new instance of Music or Sound and store it. Delete all of it when the dispose() is called

class GameAudio {
    public:
        GameAudio();
        static Music* newMusic(const string&);
        static Sound* newSound(const string&);
        static void dispose();
        virtual ~GameAudio();
    protected:
    private:
        static SoundBuffer buffer;
        static vector<Music*>* vecMusicPtr;
        static vector<Sound*>* vecSoundPtr;
};

#endif // GAMEAUDIO_H
