#ifndef GAME_H
#define GAME_H
#include <SFML/Graphics.hpp>

#include <sstream>


#include "Screen.h"
#include "framework/Timer.h"

using namespace sf;

///
#include <iostream>
using namespace std;

class Game {
    public:
        Game(const float width, const float height, const string gamename);

        void setScreen(Screen* scr);
        void startLooping();
        void exit();

        static const float& getWidth();
        static const float& getHeight();

        virtual ~Game();
    protected:
        static float width;
        static float height;

        // Variables to set the mouse update speed
        float updateTime;
        float cumulativeTime;

        Screen* scrPtr;
        Vector2i screenSize;

        string gameName;
        bool closed;

        // Newly created variables
        Timer* timerPtr;
    private:
};

#endif // GAME_H
