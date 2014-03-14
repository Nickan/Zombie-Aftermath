#include "BaseEntity.h"

BaseEntity::BaseEntity() {
    this->id = EntityManager::getAvailableId(this);
}

const int& BaseEntity::getId() {
    return id;
}

BaseEntity::~BaseEntity()
{
    //dtor
}
