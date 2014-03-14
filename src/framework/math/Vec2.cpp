#include "Vec2.h"

Vec2::Vec2() {
    x = 0;
    y = 0;
}

Vec2::Vec2(const float& x, const float& y)
: x(x), y(y) { }

void Vec2::normalize() {
    float length = sqrt( getLengthSqr() );
    x = x / length;
    y = y / length;
}

const float Vec2::getLengthSqr() {
    return (x * x) + (y * y);
}

Vec2::~Vec2() {
    //dtor
}
