#include "BaseEntity.h"

BaseEntity::BaseEntity(const int& id) {
    this->id = id;
}

const int& BaseEntity::getId() {
    return id;
}

BaseEntity::~BaseEntity()
{
    //dtor
}
