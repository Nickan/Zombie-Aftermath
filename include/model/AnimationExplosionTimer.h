#ifndef ANIMATIONEXPLOSIONTIMER_H
#define ANIMATIONEXPLOSIONTIMER_H

//------------------------------------------------
//
//  Handles the state time for the explosion
//------------------------------------------------

enum ExplosionType {
    NORMAL, SPLASH, ICE,
};

class AnimationExplosionTimer {
    public:
        AnimationExplosionTimer(const float& x, const float& y, const float& stateTime, const ExplosionType& type);
        virtual ~AnimationExplosionTimer();

        float x;
        float y;
        float stateTime;
        ExplosionType type;
    protected:
    private:
};

#endif // ANIMATIONEXPLOSIONTIMER_H
