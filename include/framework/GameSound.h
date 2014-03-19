#ifndef GAMESOUND_H
#define GAMESOUND_H

#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Audio/Sound.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//--------------------------------------------------------
//
//  A simple sound that has its own sound buffer (I thought before only one SoundBuffer would suffice)
//--------------------------------------------------------

class GameSound : public Sound
{
    public:
        GameSound();
        const bool loadFromFile(const string&);
        ~GameSound();
    protected:
    private:
        SoundBuffer buffer;
};

#endif // GAMESOUND_H
