#include "Entity.h"

Entity::Entity(FloatRect* boundPtr, float rotation)
: BaseEntity(), boundPtr(boundPtr), rotation(rotation)
{ }

Entity::~Entity() {
    delete boundPtr;
}
