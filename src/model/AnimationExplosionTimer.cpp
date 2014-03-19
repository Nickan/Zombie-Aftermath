#include "AnimationExplosionTimer.h"

AnimationExplosionTimer::AnimationExplosionTimer(const float& x, const float& y, const float& stateTime, const ExplosionType& type) {
    this->x = x;
    this->y = y;
    this->stateTime = stateTime;
    this->type = type;
}

AnimationExplosionTimer::~AnimationExplosionTimer() {
    //dtor
}
