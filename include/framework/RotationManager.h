#ifndef ROTATIONMANAGER_H
#define ROTATIONMANAGER_H

// A global class that handles simple rotation operations

#include <cmath>

using namespace std;

class RotationManager {
    public:
        // Returns a degree from the direction vector
        static const float getDegree(const float x, const float y);

        // Returns the nearest rotation turn to get to the target rotation, the rotSpeed will be added to get to the target rotation
        static const float getSmoothRotation(const float& curRot, const float& tarRot, const float& incRot);

        static const float MATH_PI;
        static const float DEG_TO_RAD;
        static const float RAD_TO_DEG;
        virtual ~RotationManager();
    protected:
    private:
        RotationManager();
};

#endif // ROTATIONMANAGER_H
