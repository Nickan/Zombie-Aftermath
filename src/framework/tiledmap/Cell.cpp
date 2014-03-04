#include "Cell.h"

Cell::Cell()
{
    //ctor
}

Cell::Cell(const float& left, const float& top, const float& width, const float& height, const float rotation) {
    this->left = left;
    this->top = top;
    this->width = width;
    this->height = height;
    this->rotation = rotation;
}

Cell::~Cell()
{
    //dtor
}
