#ifndef GAMEAUDIO_H
#define GAMEAUDIO_H

#include <SFML/Audio/Music.hpp>
#include <iostream>
#include <vector>

#include "GameSound.h"

using namespace std;
using namespace sf;

// Handles the creationg of a new instance of Music or Sound and store it. Delete all of it when the dispose() is called

class GameAudio {
    public:
        GameAudio();
        static Music* newMusic(const string&);
        static GameSound* newSound(const string&);
        static void dispose();
        virtual ~GameAudio();
    protected:
    private:
        static vector<Music*>* vecMusicPtr;
        static vector<GameSound*>* vecSoundPtr;

        static vector<SoundBuffer> buffers;
};

#endif // GAMEAUDIO_H
