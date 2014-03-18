#ifndef GAMESCREENCONTROLLER_H
#define GAMESCREENCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>

#include "GameScreen.h"
#include "MenuScreen.h"

#include <cmath>

using namespace sf;

// For debugging
#include <iostream>
using namespace std;

class GameScreen;

class GameScreenController : public Input {
    public:
        GameScreenController(GameScreen* gameScreenPtr);

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
        void screenScrolling(const int& x, const int& y);

        // Cancels cannon planting, bring back the money from purchasing
        void cancelCannonPlanting();

        const bool panelButtonPressed(const int& x, const int& y);

        // Returns the tile number of the game
        const Vector2i& getTileNumber(const int& screenX, const int& screenY);

        GameScreen* gameScreenPtr;
        bool scrollScreen;
        Vector2i mousePrevPos;
        Vector2i tileNumber;
};

#endif // GAMESCREENCONTROLLER_H
