#include "Entity.h"

Entity::Entity(FloatRect* boundPtr, float rotation)
: boundPtr(boundPtr), rotation(rotation)
{
}

Entity::~Entity() {
    //dtor
}
