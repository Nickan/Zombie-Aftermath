#ifndef NODE_H
#define NODE_H

enum NodeType {
    AVAILABLE, UNWALKABLE
};

class Node {
    public:
        Node(const int& x, const int& y);
        virtual ~Node();

        const bool same(const Node* nodePtr);

        unsigned int x;
        unsigned int y;
        unsigned int f;
        unsigned int g;
        unsigned int h;
        NodeType type;
        Node* parentNodePtr;
    protected:
    private:
};

#endif // NODE_H
