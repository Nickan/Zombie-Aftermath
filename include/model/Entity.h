#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics/Rect.hpp>
#include "RotationManager.h"
#include "BaseEntity.h"

using namespace sf;

class Entity: public BaseEntity {
    public:
        Entity(FloatRect* boundPtr, float rotation);

        virtual void update(const float& delta) = 0;
        virtual ~Entity();

        FloatRect* boundPtr;
        float rotation;
    protected:
    private:
};

#endif // ENTITY_H
