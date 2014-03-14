#include "Node.h"

Node::Node(const int& x, const int& y) {
    this->x = x;
    this->y = y;
    this->f = 0;
    this->g = 0;
    this->h = 0;
    this->type = NodeType::AVAILABLE;
    this->parentNodePtr = 0;
}

const bool Node::same(const Node* nodePtr) {
    return (this->x == nodePtr->x && this->y == nodePtr->y) ? true : false;
}

Node::~Node() { }
