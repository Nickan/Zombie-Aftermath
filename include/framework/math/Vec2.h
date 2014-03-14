#ifndef VEC2_H
#define VEC2_H

// A simple vector that has some common vector operations
// Decided to make my own, as the Vector2 of SFML only have simple operations, add more functionality later
#include <cmath>

using namespace std;

class Vec2 {
    public:
        Vec2();
        Vec2(const float& x, const float& y);
        virtual ~Vec2();

        float x;
        float y;

        void normalize();
        const float getLengthSqr();
    protected:
    private:
};

#endif // VEC2_H
