#ifndef TIMER_H
#define TIMER_H
#include "SFML/Graphics.hpp"

using namespace sf;

class Timer
{
    public:
        Timer();
        virtual ~Timer();
        float getDeltaTime();
    protected:
    private:
        Clock clock;
        Time time;
        float currentTime;
        float previousTime;
        float deltaTime;

        void update();
};

#endif // TIMER_H
