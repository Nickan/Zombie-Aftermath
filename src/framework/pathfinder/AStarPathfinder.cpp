#include "AStarPathfinder.h"

AStarPathfinder::AStarPathfinder(const unsigned int& width, const unsigned int& height) {
    initializeNodePtrs(width, height);
}

void AStarPathfinder::initializeNodePtrs(const unsigned int& width, const unsigned int& height) {
    for (unsigned int col = 0; col < height; ++col) {

        // Create a new vector for Node pointers
        vector<Node*> newRow;
        newRow.shrink_to_fit();
        for (unsigned int row = 0; row < width; ++row) {
            // Assigning default values
            newRow.push_back(new Node(row, col));
        }

        nodePtrs2D.push_back(newRow);
    }
    nodePtrs2D.shrink_to_fit();
}


vector<Node*> AStarPathfinder::getPath(const unsigned int& startX, const unsigned int& startY,
                                                const unsigned int& goalX, const unsigned int& goalY) {
    // Clear all the node pointer list
    openNodePtrs.clear();
    closedNodePtrs.clear();
    adjNextNodePtrs.clear();
    nodePathPtrs.clear();
    Node* currentNodePtr = nodePtrs2D.at(startY).at(startX);
    Node* goalNodePtr = nodePtrs2D.at(goalY).at(goalX);

    setHeuristics(goalNodePtr);

    // For detection, set a loop limit
    unsigned int loopCount = 0;
    unsigned int loopLimit = 200;

    // Non-terminated loop, will break when path is found or not
    while (true) {
        closedNodePtrs.push_back(currentNodePtr);
        setAdjNextNodePtrs(adjNextNodePtrs, currentNodePtr);

        processAdjNodes(currentNodePtr);
        Node* nextNode = getLowestHCostNode(adjNextNodePtrs);

        // No result from the adjacent nodes
        if (nextNode == 0) {
            // Try searching in open list
            nextNode = getLowestHCostNode(openNodePtrs);

            // If there is still no node, break operation
            if (nextNode == 0) {
                cout << "Goal node not found, might be unwalkable, breaking operation" << endl;
                break;
            }
        }

        // Check if the next node is the same as the goal node, then break the operation
        if (nextNode->same(goalNodePtr)) {
            cout << "Found" << goalNodePtr->x << ": " << goalNodePtr->y << endl;

            // Add the goal node
            nodePathPtrs.push_back(goalNodePtr);
            break;
        }
        // Else set it as the current node and loop again
        currentNodePtr = nextNode;

        // Loop limiter
        ++loopCount;
        if (loopCount >= loopLimit) {
            cout << "Loop count reached" << endl;
            break;
        }
    }

    cout << "Loop count: " << loopCount << endl;
    traceBackNodePath(goalNodePtr);

    return nodePathPtrs;
}

void AStarPathfinder::setHeuristics(Node* goalNodePtr) {
    for (unsigned int y = 0; y < nodePtrs2D.size(); ++y) {
        for (unsigned int x = 0; x < nodePtrs2D.at(y).size(); ++x) {
            Node* nodePtr = nodePtrs2D.at(y).at(x);
            setDefaultValues(nodePtr);
            nodePtr->h = getManhattanDist(x, y, goalNodePtr->x, goalNodePtr->y);
        }
    }
}

void AStarPathfinder::setDefaultValues(Node* nodePtr) {
    nodePtr->parentNodePtr = 0;
    nodePtr->g = 0;
    nodePtr->h = 0;
    nodePtr->f = 0;
}

const int AStarPathfinder::getManhattanDist(const int& tileX, const int& tileY, const int& goalX, const int& goalY) {
    return (abs(tileX - goalX) + abs(tileY - goalY));
}

void AStarPathfinder::setAdjNextNodePtrs(vector<Node*>& nodePtrs, Node* currentNodePtr) {
    nodePtrs.clear();

    // Start the index reading minus one from the current node
    int startX = currentNodePtr->x - 1;
    int startY = currentNodePtr->y - 1;

    // Loop until the plus one index from the current node
    for (unsigned int x = 0; x < 3; ++x) {
        for (unsigned int y = 0; y < 3; ++y) {

            // The current node, ignore and carry on
            if (x == 1 && y == 1) {
                continue;
            }

            // Ignore the non existing index too
            if (startX + x  >= 0 && startX + x < nodePtrs2D.at(0).size()) {
                if (startY + y >= 0 && startY + y < nodePtrs2D.size()) {
                    Node* tempNodePtr = nodePtrs2D.at(startY + y).at(startX + x);

                    // Ignore the node if it is belong in the closed nodes and Unwalkable node
                    // Only node that is available and belong in open list are valid to be in the adjacent nodes
                    if (isInList(closedNodePtrs, tempNodePtr) || tempNodePtr->type == NodeType::UNWALKABLE) {
                        continue;
                    }

                    // If the diagonal movement is disabled
                    if (!diagonalMoveEnable) {
                        if (isDiagonallyPlaced(tempNodePtr, currentNodePtr)) {
                            continue;
                        }
                    }
                    nodePtrs.push_back(tempNodePtr);
                }
            }

        }
    }
}

void AStarPathfinder::processAdjNodes(Node* currentNodePtr) {
    for (unsigned int index = 0; index < adjNextNodePtrs.size(); ++index) {
        Node* adjNodePtr = adjNextNodePtrs.at(index);

        if (isInList(openNodePtrs, adjNodePtr)) {
            setOpenNode(adjNodePtr, currentNodePtr);
        } else {
            setFreeNode(adjNodePtr, currentNodePtr);
        }
    }
}

void AStarPathfinder::setFreeNode(Node* freeNodePtr, Node* currentNodePtr) {
    // Set it as its parent node
    freeNodePtr->parentNodePtr = currentNodePtr;

    // If diagonally placed, set g cost to 14, otherwise set it to 10
    int g = (isDiagonallyPlaced(freeNodePtr, currentNodePtr)) ? 14: 10;

    freeNodePtr->g = g + currentNodePtr->g;
    freeNodePtr->f = freeNodePtr->g + freeNodePtr->h;

    // Add it to the open list
    openNodePtrs.push_back(freeNodePtr);
}

void AStarPathfinder::setOpenNode(Node* openNodePtr, Node* currentNodePtr) {
    // If diagonally placed, set g cost to 14, otherwise set it to 10
    int g = (isDiagonallyPlaced(openNodePtr, currentNodePtr)) ? 14: 10;

    // If the current node and g cost to move to the adjacent open node is lower than the adjacent current g cost, set the parent of the
    // adjacent open node as the current node
    if (currentNodePtr->g + g < openNodePtr->g) {

        // Set it as the parent and recalculate its g cost
        openNodePtr->parentNodePtr = currentNodePtr;
        openNodePtr->g = g + currentNodePtr->g;

        // Recalculate its f cost too
        openNodePtr->f = openNodePtr->g + openNodePtr->h;
    }
}

const bool AStarPathfinder::isDiagonallyPlaced(Node* firstNodePtr, Node* secondNodePtr) {
    return ( (firstNodePtr->x != secondNodePtr->x) && (firstNodePtr->y != secondNodePtr->y) ) ? true : false;
}

const bool AStarPathfinder::isInList(vector<Node*>& nodePtrs, Node* nodePtr) {
    for (unsigned int index = 0; index < nodePtrs.size(); ++index) {
        if (nodePtrs.at(index)->same(nodePtr)) {
            return true;
        }
    }
    return false;
}

Node* AStarPathfinder::getLowestHCostNode(vector<Node*>& nodePtrs) {
    unsigned int h = 99999;
    Node* lowestHCostNodePtr = 0;
    unsigned int indexNum = 0;

    // Loop through all the nodes to find the node that has the lowest f cost
    for (unsigned int index = 0; index < nodePtrs.size(); ++index) {
        Node* tempNodePtr = nodePtrs.at(index);

        if (tempNodePtr->h < h) {
            lowestHCostNodePtr = tempNodePtr;
            h = lowestHCostNodePtr->h;
            indexNum = index;
        }
    }

    // Remove it in the list
    if (lowestHCostNodePtr != 0 && !nodePtrs.empty()) {
        nodePtrs.erase(nodePtrs.begin() + indexNum);
    }

    return lowestHCostNodePtr;
}


void AStarPathfinder::traceBackNodePath(Node* goalNodePtr) {
    Node* lastNodePtr = 0;

    // Trying to get result from the closed list's last node
    if (!closedNodePtrs.empty()) {
        nodePathPtrs.push_back(closedNodePtrs.back());
        lastNodePtr = closedNodePtrs.back();
    } else {
        cout << "No path list in the closed list" << endl;
        return;
    }

    // Loop until the starting node is found
    while (true) {
        Node* parentNodePtr = lastNodePtr->parentNodePtr;

        // If the parent node is equal to 0, that means that it is the starting node
        if (parentNodePtr != 0) {
            nodePathPtrs.push_back(parentNodePtr);

            // Set the last node to be the parent node, then the loop goes one until the parent node pointer will be equal to 0
            lastNodePtr = parentNodePtr;
        } else {
            // remove the starting node
            nodePathPtrs.pop_back();
            break;
        }
    }
}


void AStarPathfinder::setAllNodesWalkable() {
    for (unsigned int col = 0; col < nodePtrs2D.size(); ++col) {
        for (unsigned int row = 0; row < nodePtrs2D.at(col).size(); ++row) {
            nodePtrs2D.at(col).at(row)->type = NodeType::AVAILABLE;
        }
    }
}

const bool AStarPathfinder::setNodeType(const unsigned int& nodeX, const unsigned int& nodeY, const NodeType& nodeType) {
    // Checking the range value of the given indices
    // Never ever compare an unsigned int to a negative value
    if ( (nodeX >= 0 && nodeX < nodePtrs2D.at(0).size()) &&
        (nodeY >= 0 && nodeY < nodePtrs2D.size()) ) {
            nodePtrs2D.at(nodeY).at(nodeX)->type = nodeType;
        return true;
    }
    return false;
}

AStarPathfinder::~AStarPathfinder() {
    for (unsigned int col = 0; col < nodePtrs2D.size(); ++col) {
        for (unsigned int row = 0; row < nodePtrs2D.at(col).size(); ++row) {
            delete nodePtrs2D.at(col).at(row);
        }
    }
}
