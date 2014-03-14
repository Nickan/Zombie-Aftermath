#ifndef ASTARPATHFINDER_H
#define ASTARPATHFINDER_H

#include <cmath>
#include <vector>

#include "Node.h"

// For detection
#include <iostream>
using namespace std;

// My attempt A* Pathfinder version in C++, though I know there is existing optimized version of this, I want to make my own
// as it will sharpen my C++ coding skills and will give me arcane C++ error to solve (is that beneficial?).

class AStarPathfinder {
    public:
        AStarPathfinder(const unsigned int& width, const unsigned int& height);
        virtual ~AStarPathfinder();

        // Returns the shortest path result, trying to make it only read only so that I don't have to make a new vector
        // Every path request
        vector<Node*> getPath(const unsigned int& startX, const unsigned int& startY,
                                const unsigned int& goalX, const unsigned int& goalY);

        // Set the type of the node, returns false if there is an error
        const bool setNodeType(const unsigned int& nodeX, const unsigned int& nodeY, const NodeType& nodeType);

        // Set the node pointers to be walkable
        void setAllNodesWalkable();

        bool diagonalMoveEnable;
    protected:
    private:
        // Initialize default values of 2D vector of Node pointers
        void initializeNodePtrs(const unsigned int& width, const unsigned int& height);

        void setAdjNextNodePtrs(vector<Node*>& nodePtrs, Node* currentNodePtr);

        void processAdjNodes(Node* currentNodePtr);

        void setFreeNode(Node* freeNodePtr, Node* currentNodePtr);
        void setOpenNode(Node* openNodePtr, Node* currentNodePtr);

        const bool isDiagonallyPlaced(Node* firstNodePtr, Node* secondNodePtr);

        // Returns whether the node is in the vector
        const bool isInList(vector<Node*>& nodePtrs, Node* nodePtr);

        void setHeuristics(Node* goalNodePtr);
        void setDefaultValues(Node* nodePtr);

        const int getManhattanDist(const int& tileX, const int& tileY, const int& goalX, const int& goalY);

        Node* getLowestHCostNode(vector<Node*>& nodePtrs);

        void traceBackNodePath(Node* goalNodePtr);

        vector<Node*> nodePathPtrs;
        vector<Node*> adjNextNodePtrs;
        vector<Node*> closedNodePtrs;
        vector<Node*> openNodePtrs;
        vector<vector<Node*> > nodePtrs2D;
};

#endif // ASTARPATHFINDER_H
