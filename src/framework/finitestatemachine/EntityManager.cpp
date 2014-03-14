#include "EntityManager.h"

int EntityManager::idCounter = -1;

vector<BaseEntity*> EntityManager::entityList;

EntityManager::EntityManager() { }

const int EntityManager::getAvailableId(BaseEntity* entity) {
    entityList.push_back(entity);
    return ++idCounter;
}

BaseEntity* EntityManager::getEntity(const int& id) {
    for (unsigned int index = 0; index < entityList.size(); ++index) {
        if (entityList.at(index)->getId() == id) {
            return entityList.at(index);
        }
    }
    return 0;
}

void EntityManager::deleteEntity(const int& id) {
    for (unsigned int index = 0; index < entityList.size(); ++index) {
        if (entityList.at(index)->getId() == id) {
            delete entityList.at(index);
            entityList.erase(entityList.begin() + index);
            break;
        }
    }
}

EntityManager::~EntityManager()
{
    //dtor
}
