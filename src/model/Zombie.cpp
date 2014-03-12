#include "Zombie.h"

Zombie::Zombie(FloatRect* boundPtr, float rotation)
: Entity(boundPtr, rotation) {
    //ctor
}

void Zombie::update(const float& delta) {

}

Zombie::~Zombie() {
    //dtor
}
