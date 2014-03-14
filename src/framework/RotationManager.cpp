#include "RotationManager.h"

const float RotationManager::MATH_PI = 3.14159f;
const float RotationManager::RAD_TO_DEG = 180 / MATH_PI;
const float RotationManager::DEG_TO_RAD = MATH_PI / 180;

RotationManager::RotationManager() { }

const float RotationManager::getDegree(const float& x, const float& y) {
    float compensationRotation = 0;

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

    return atanRotation + compensationRotation;
}

const float RotationManager::getSmoothRotation(const float& curRot, const float& tarRot, const float& incRot) {
    float currentRotation = curRot;
    if (curRot < 0)  {
        currentRotation = 360 + curRot;
    }

    float difRot = currentRotation - tarRot;
    if (abs(difRot) < incRot) {
        return tarRot;
    }

    // The current rotation is lower than the target rotation
    if (currentRotation < tarRot) {
        // The difference between is lower than 180
        if (abs(difRot) <= 180) {
            return currentRotation + incRot;
        } else {
            return currentRotation - incRot;
        }

    } else {
        // The current rotation is higher than the target rotation
        // The difference between is lower than 180
        if ( abs(difRot) <= 180) {
            return currentRotation - incRot;
        } else {
            // Higher
            return currentRotation + incRot;
        }
    }

}

RotationManager::~RotationManager() { }
