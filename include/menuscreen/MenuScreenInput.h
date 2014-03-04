#ifndef MENUSCREENINPUT_H
#define MENUSCREENINPUT_H

#include "MenuScreen.h"
#include "GameScreen.h"
#include "framework/Input.h"
#include "Settings.h"


// For debugging
#include <iostream>
using namespace std;

class MenuScreen;

class MenuScreenInput : public Input {
    public:
        MenuScreenInput(MenuScreen*);
        void leftMousePressed(const int&, const int&);
        void leftMouseReleased(const int&, const int&);
        void rightMousePressed(const int&, const int&);
        void rightMouseReleased(const int&, const int&);

        void mouseMoved(const int&, const int&);
        void mouseMotion(const int&, const int&);

        void keyPressed(const int&);
        void keyReleased(const int&);
        virtual ~MenuScreenInput();
    protected:
    private:
        MenuScreen* screenPtr;
        IntRect playRect;
        IntRect exitRect;
        bool selected;
};

#endif // MENUSCREENINPUT_H
