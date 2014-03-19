#include "Zombie.h"

unsigned int Zombie::worldUnit = 32;

Zombie::Zombie(FloatRect* boundPtr, const int& life, const float& rotation, const float& speed)
: Entity(boundPtr, rotation) {
    this->life = life;
    this->speed = speed;

    rotationSpeed = 100.0f;
    fullLife = this->life;
    fullSpeed = this->speed;

    goalNodePtr = NULL;
    goalReached = false;
    frozen = false;

    slowEffectDuration = 5.0f; //-> Five seconds frozen
    slowEffectTimer = 0;
}

void Zombie::update(const float& delta) {
    stateTime += delta;

    boundPtr->left += velocity.x * speed * delta;
    boundPtr->top += velocity.y * speed * delta;

    // If already moved one unit through x
    if (abs(previousPos.x - boundPtr->left) >= worldUnit) {
        velocity.x = 0;

        boundPtr->left = round(boundPtr->left / worldUnit) * worldUnit;
    }

    // If already moved one unit through y
    if (abs(previousPos.y - boundPtr->top) >= worldUnit) {
        velocity.y = 0;
        boundPtr->top = round(boundPtr->top / worldUnit) * worldUnit;
    }

    // If not moving
    if ( (velocity.x == 0) && (velocity.y == 0)) {

        // Check if there is path given
        if (!pathPtrs.empty()) {
            setMovement();
        } else {

            // Detects if the zombie has reached its goal
            if (goalNodePtr != NULL) {
                if (goalNodePtr->x == (unsigned int) (boundPtr->left / worldUnit) &&
                    goalNodePtr->y == (unsigned int) (boundPtr->top / worldUnit) ) {
                    goalReached = true;
                }
            }
        }
    } else {
        // Moving, set the rotation
        float targetRotation = RotationManager::getDegree(velocity.x, velocity.y);
        rotation = RotationManager::getSmoothRotation(rotation, targetRotation, delta * rotationSpeed);
    }



    if (frozen) {
        updateSlowEffect(delta);
    }
}

void Zombie::setMovement() {
    previousPos.x = boundPtr->left;
    previousPos.y = boundPtr->top;

    Node* nextNodePtr = pathPtrs.back();
    // Remove the path from the path list
    pathPtrs.pop_back();

    // Determine the vector to go to the next node
    velocity.x = nextNodePtr->x - (int) (boundPtr->left / worldUnit);
    velocity.y = nextNodePtr->y - (int) (boundPtr->top / worldUnit);
}


void Zombie::updateSlowEffect(const float& delta) {
    slowEffectTimer += delta;

    if (slowEffectTimer >= slowEffectDuration) {
        slowEffectTimer = 0;
        frozen = false;
        speed = fullSpeed;
    }
}

const bool Zombie::handleMessage(Message* msgPtr) {
    switch (msgPtr->msgType) {
    case MessageType::TARGET_ZOMBIE:
        MessageDispatcher::sendMessage(id, msgPtr->senderId, 0, MessageType::TARGET_RESPONSE, boundPtr);
        return true;
    case MessageType::HIT_ZOMBIE:
        // Check if still alive
        if (life > 0) {
            // Container for the attack damage
            Vector2i* atkDmgPtr = (Vector2i*) msgPtr->extraInfo;
            life -= atkDmgPtr->x;

            // Delete the container
            delete atkDmgPtr;

            // If killed by the attack
            if (life <= 0) {
                // Add money and score based on the full life
                Settings::cash += (int) (fullLife / 50);
                Settings::score += (int) (fullLife / 20);
            }
        } else {
            MessageDispatcher::sendMessage(id, msgPtr->senderId, 0, MessageType::KILLED, NULL);
        }


        return true;
    case MessageType::FROZEN:
        // Check if still alive
        if (life > 0) {
            frozen = true;
            // Reset the slow timer if there is existing one in effect
            slowEffectTimer = 0;

            // Container for the attack damage
            Vector2i* atkDmgAndSlowPtr = (Vector2i*) msgPtr->extraInfo;
            life -= atkDmgAndSlowPtr->x;

            // Slow effect
            speed = fullSpeed * (atkDmgAndSlowPtr->y / 100.0f);

            // Delete the container
            delete atkDmgAndSlowPtr;

            // If killed by the attack
            if (life <= 0) {
                // Add money based on the full life
                Settings::cash += (int) (fullLife / 50);
                MessageDispatcher::sendMessage(id, msgPtr->senderId, 0, MessageType::KILLED, NULL);
            }
        }
        return true;
    default:
        return false;
    }
}

//------------------ Setters ---------------------
void Zombie::setPath(const vector<Node*>& pathPtrs) {
    this->pathPtrs = pathPtrs;
}

//------------------ Getters ---------------------
const float& Zombie::getLife() {
    return life;
}

const float& Zombie::getFullLife() {
    return fullLife;
}

const bool& Zombie::goalIsReached() {
    return goalReached;
}

const bool& Zombie::isFrozen() {
    return frozen;
}

Zombie::~Zombie() {
    //dtor
}
