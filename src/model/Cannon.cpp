#include "Cannon.h"

Vec2 Cannon::vec2;

Cannon::Cannon(FloatRect* boundPtr, int attackDamage, int range, float attackDelay,
                float rotation, float rotationSpeed)
: Entity(boundPtr, rotation), attackDamage(attackDamage), range(range),
attackDelay(attackDelay), rotationSpeed(rotationSpeed)
{
    stateMachinePtr = new StateMachine<Cannon>(this);
    stateMachinePtr->changeState(CannonIdleState::getInstance());
    targetId = -1;
    attackTimer = 0;

    // Three bullets for now
    bulletPtrs.push_back(new Bullet(new FloatRect(0, 0, 8, 5), 0));
    bulletPtrs.push_back(new Bullet(new FloatRect(0, 0, 8, 5), 0));
    bulletPtrs.push_back(new Bullet(new FloatRect(0, 0, 8, 5), 0));
}

void Cannon::update(const float& delta) {
    stateMachinePtr->update(delta);
}

void Cannon::fireBullet() {
    for (unsigned int index = 0; index < bulletPtrs.size(); ++index) {
        Bullet* bulletPtr = bulletPtrs.at(index);
        if (!bulletPtr->updating) {
            bulletPtr->updating = true;

            vec2.x = boundPtr->left + (boundPtr->width / 2) - (targetRectPtr->left + (targetRectPtr->width / 2));
            vec2.y = boundPtr->top + (boundPtr->height / 2) - (targetRectPtr->top + (targetRectPtr->height / 2));
            vec2.normalize();

            float distFromTurret = 10;
            bulletPtr->boundPtr->left = (boundPtr->left + (boundPtr-> width / 2) ) - (distFromTurret * vec2.x);
            bulletPtr->boundPtr->top = (boundPtr->top + (boundPtr->height / 2) ) - (distFromTurret * vec2.y);

            setUpBullet(bulletPtr);
            // Only one bullet will be fired at a time
            break;
        }
    }
}

void Cannon::setUpBullet(Bullet* bulletPtr) {
    // Nothings to do here
}

void Cannon::bulletUpdate(Bullet* bulPtr, const float& delta) {
    float targetX = targetRectPtr->left + (targetRectPtr->width / 2);
    float targetY = targetRectPtr->top + (targetRectPtr->height / 2);
    if (bulPtr->targetHit(targetX, targetY)) {
        bulPtr->updating = false;

        // If there is target Id set
        if (targetId != -1) {
            // Creates a new vector to pass as a damage done to the zombie, as I can't find way for the pointer
            // to convert back to its original value
            Vector2i* atkDmgPtr = new Vector2i(attackDamage, 0);
            MessageDispatcher::sendMessage(id, targetId, 0, MessageType::HIT_ZOMBIE, atkDmgPtr);
        }
    } else {
        bulPtr->trackTarget(targetX, targetY, delta);
    }
}


const bool Cannon::targetLocked(const float& delta) {
    // Put parentheses, as the code will compute it left to right
    // Get the not normalized vector to the target
    float distX = (targetRectPtr->left + 16) - (boundPtr->left + (boundPtr->width / 2));
    float distY = (targetRectPtr->top + 16) - (boundPtr->top + (boundPtr->height / 2));
    float targetRotation = RotationManager::getDegree(distX, distY);

    rotation = RotationManager::getSmoothRotation(rotation, targetRotation, rotationSpeed * delta);
    float rotationDifference = abs(targetRotation - rotation);

    return (rotationDifference < rotationSpeed * delta) ? true : false;
}


//----------------Setters---------------------
void Cannon::setTargetId(const int& targetId) {
    this->targetId = targetId;

    if (targetId != -1) {
        MessageDispatcher::sendMessage(this->id, targetId, 0, MessageType::TARGET_ZOMBIE, NULL);
    }
}


//----------------Getters---------------------
const int& Cannon::getTargetId() {
    return targetId;
}

const FloatRect* Cannon::getTargetRect() {
    return targetRectPtr;
}

const vector<Bullet*>& Cannon::getBullets() {
    return bulletPtrs;
}

const bool Cannon::handleMessage(Message* msgPtr) {
    switch (msgPtr->msgType) {
    case MessageType::TARGET_RESPONSE:
        stateMachinePtr->changeState(CannonAttackState::getInstance());
        targetRectPtr = (FloatRect*) msgPtr->extraInfo;
        return true;
    case MessageType::HIT_RESPONSE:
        // Still don't know why I am getting "jump to case label [-fpermissive]" and "crosses initialization"
        // whenever I remove the parentheses
        {
            Vector2i* lifePtr = (Vector2i*) msgPtr->extraInfo;
            // If zombie is dead
            if (lifePtr->x <= 0) {
                stateMachinePtr->changeState(CannonIdleState::getInstance());
            }
        }

        return true;
    default:
        return false;
    }
}

Cannon::~Cannon() {
    for (unsigned int index = 0; index < bulletPtrs.size(); ++index) {
        delete bulletPtrs.at(index);
    }
}
