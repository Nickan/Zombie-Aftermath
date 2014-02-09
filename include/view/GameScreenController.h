#ifndef GAMESCREENCONTROLLER_H
#define GAMESCREENCONTROLLER_H

#include "../framework/Input.h"

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
