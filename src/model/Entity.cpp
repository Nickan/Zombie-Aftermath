#include "Entity.h"

Entity::Entity(FloatRect* boundPtr, float rotation)
: BaseEntity(EntityManager::getAvailableId(this)), boundPtr(boundPtr), rotation(rotation)
{ }

Entity::~Entity() {
    delete boundPtr;
}
