#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Rect.hpp>

using namespace sf;

class Entity {
    public:
        Entity(FloatRect* boundPtr, float rotation);

        FloatRect* boundPtr;
        float rotation;
        virtual ~Entity();
    protected:
    private:
};

#endif // ENTITY_H
