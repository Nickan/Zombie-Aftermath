#include "Cannon.h"

Vec2 Cannon::vec2;

Cannon::Cannon(FloatRect* boundPtr, const int& attackDamage, const int& range, const float& attackDelay,
                    const float& rotation, const float& rotationSpeed)
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

Bullet* Cannon::getAvailableBullet() {
    for (unsigned int index = 0; index < bulletPtrs.size(); ++index) {
        Bullet* bulletPtr = bulletPtrs.at(index);
        if (!bulletPtr->isFired()) {
            return bulletPtr;
            placeOnTurret(bulletPtr);
            setBulletTarget(bulletPtr);
            // Only one bullet will be fired at a time
            break;
        }
    }
    return NULL;
}

void Cannon::placeOnTurret(Bullet* bulletPtr) {
    // The center of the cannon
    float centerX = boundPtr->left + (boundPtr-> width / 2);
    float centerY = boundPtr->top + (boundPtr->height / 2);
    float targetCenterX = targetRectPtr->left + (targetRectPtr->width / 2);
    float targetCenterY = targetRectPtr->top + (targetRectPtr->height / 2);

    vec2.x = targetCenterX - centerX;
    vec2.y = targetCenterY - centerY;

    float distFromCenter = 10.0f;
    vec2.normalize();

    // Place the bullet on the turret
    bulletPtr->setAsCenter(centerX + (vec2.x * distFromCenter), centerY + (vec2.y * distFromCenter));
}

void Cannon::setBulletTarget(Bullet* bulletPtr) {
    // Passed the pointer of the target, a tracer bullet
    bulletPtr->setTarget(targetRectPtr);
    // Set the target Id
    bulletPtr->targetId = targetId;
}

void Cannon::bulletHit(Bullet* bulPtr) {
    // Attack damage container
    Vector2i* atkDmgContainer = new Vector2i(attackDamage, 0);
    MessageDispatcher::sendMessage(id, bulPtr->targetId, 0, MessageType::HIT_ZOMBIE, atkDmgContainer);
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

void Cannon::setIdle() {
    stateMachinePtr->changeState(CannonIdleState::getInstance());
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

const bool Cannon::zombieInRange() {
    vec2.x = (targetRectPtr->left + (targetRectPtr->width / 2)) - (boundPtr->left + (boundPtr->width / 2));
    vec2.y = (targetRectPtr->top + (targetRectPtr->height / 2)) - (boundPtr->top + (boundPtr->height / 2));

    return (vec2.getLengthSqr() < range * range) ? true : false;
}


const bool Cannon::handleMessage(Message* msgPtr) {
    switch (msgPtr->msgType) {
    case MessageType::TARGET_RESPONSE:
        stateMachinePtr->changeState(CannonAttackState::getInstance());
        targetRectPtr = (FloatRect*) msgPtr->extraInfo;
        return true;
    case MessageType::KILLED:
        stateMachinePtr->changeState(CannonIdleState::getInstance());
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
