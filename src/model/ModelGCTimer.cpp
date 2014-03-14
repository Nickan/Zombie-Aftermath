#include "ModelGCTimer.h"

ModelGCTimer::ModelGCTimer(const int& entityId, const float& duration) {
    this->entityId = entityId;
    this->duration = duration;
}

const int& ModelGCTimer::getEntityId() {
    return entityId;
}

ModelGCTimer::~ModelGCTimer() {
    //dtor
}
