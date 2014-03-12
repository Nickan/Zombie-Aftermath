#ifndef ZOMBIE_H
#define ZOMBIE_H

#include "Entity.h"

class Zombie : public Entity {
    public:
        Zombie(FloatRect* boundPtr, float rotation);

        void update(const float& delta);
        virtual ~Zombie();
    protected:
    private:
};

#endif // ZOMBIE_H
