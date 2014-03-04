#include "RotationManager.h"

const float RotationManager::MATH_PI = 3.14159f;
const float RotationManager::RAD_TO_DEG = 180 / MATH_PI;
const float RotationManager::DEG_TO_RAD = MATH_PI / 180;

RotationManager::RotationManager() { }

const float RotationManager::getDegree(const float x, const float y) {
    int compensationRotation = 0;

    float atanRotation = atan(y / x) * RAD_TO_DEG;

    // The coordinates is in the middle to the right
    if (x >= 0) {
        compensationRotation = 180;
    } else {
        // Left side
        // Bottom
        if (y > 0) {
            compensationRotation = 360;
        }
    }

    return (atanRotation + compensationRotation);
}

const float RotationManager::getSmoothRotation(const float& curRot, const float& tarRot, const float& incRot) {
    float difRot = tarRot - curRot;
    if (abs(difRot) < incRot) {
        return tarRot;
    }

    // The current rotation is lower than the target rotation
    if (curRot < tarRot) {

        // The difference between is lower than 180
        if (difRot <= 180) {
            return curRot + incRot;
        } else {
            // Higher
            return curRot - incRot;
        }

    } else {

        // The current rotation is higher than the target rotation
        // The difference between is lower than 180
        if ( abs(difRot) <= 180) {
            return curRot - incRot;
        } else {
            // Higher
            return curRot + incRot;
        }
    }

}

RotationManager::~RotationManager() { }
