#ifndef BULLET_H
#define BULLET_H

#include "Entity.h"

class Bullet : public Entity {
    public:
        Bullet(FloatRect* boundPtr, float rotation);
        virtual ~Bullet();
    protected:
    private:
};

#endif // BULLET_H
