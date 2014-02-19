#ifndef GAMESCREENCONTROLLER_H
#define GAMESCREENCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "../framework/Input.h"


using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class GameScreenController : public Input
{
    public:
        GameScreenController();

        void leftMousePressed(const int& x, const int& y);
        void leftMouseReleased(const int& x, const int& y);
        void rightMousePressed(const int& x, const int& y);
        void rightMouseReleased(const int& x, const int& y);

        void mouseMoved(const int& x, const int& y);
        void mouseMotion(const int& x, const int& y);

        void keyPressed(const int& keycode);
        void keyReleased(const int& keycode);
        virtual ~GameScreenController();
    protected:
    private:
};

#endif // GAMESCREENCONTROLLER_H
